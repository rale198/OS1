/*
 * PCB.cpp
 *
 *  Created on: May 9, 2019
 *      Author: OS1
 */

#include "PCB.h"
#include "ListPCB.h"
#include "Lock.h"
#include "Kernelse.h"

volatile int zahtevana_promena_konteksta = 0;
volatile int contextSwitchDelayed = 0; //ako sam stigao do 0 ali je zakljucano, kada lock==0 menjas kontekst
volatile unsigned counter = defaultTimeSlice; //treba da bude usaglasen sa main
ListPCB* allPCB = new ListPCB(); // MOZDA VOLATILE
volatile PCB* PCB::running = 0;
volatile Idle* PCB::idle = new Idle();

void tick();
volatile unsigned tss = 0, tsp = 0, tbp = 0;
void interrupt timer(...)
{

	if (zahtevana_promena_konteksta == 0) {
		asm int 60h;
		tick();
		sleepList.timerUpdate();
		if (counter > 0) {
			counter--;

			if (counter == 0 && lock) {
				contextSwitchDelayed = 1;
			}
		}

	}

	if ((counter == 0 && (!lock) && (PCB::running->timeSliceFlag == 1))
			|| (zahtevana_promena_konteksta == 1)) {

#ifndef BCC_BLOCK_IGNORE
		asm {

			mov tss,ss
			mov tsp,sp
			mov tbp,bp;
		}
#endif

		PCB::running->sp = tsp;
		PCB::running->ss = tss;
		PCB::running->bp = tbp;
		if (PCB::running->state != PCB::finished
				&& PCB::running->state != PCB::blocked
				&& (PCB*)PCB::running != PCB::idlePCB) {
			PCB::running->state = PCB::ready;
			Scheduler::put((PCB*) (PCB::running));
		}

		PCB::running = Scheduler::get();

		if (PCB::running == 0) {
			PCB::running = PCB::idlePCB;
		}
		PCB::running->state = PCB::run;

		counter = PCB::running->quant;
		tsp = PCB::running->sp;
		tbp = PCB::running->bp;
		tss = PCB::running->ss;

#ifndef BCC_BLOCK_IGNORE
		asm {
			mov sp,tsp
			mov ss,tss
			mov bp,tbp
		}
#endif

		zahtevana_promena_konteksta = 0; //vise nije zahtevan zavrsio si

	}

}

PCB::PCB(StackSize sizestack, Time slicetime, Thread* const myThr) {

	myThread = myThr;
	if (sizestack > 65535)
		sizestack = 65535;

	this->retVal=0;
	this->ss = this->sp = 0;
	this->state = notStarted;

	this->stackSize = sizestack / sizeof(unsigned);

	stack = new unsigned[stackSize];
	this->quant = slicetime;

#ifndef BCC_BLOCK_IGNORE
	stack[stackSize-1]=FP_SEG(myThread);
	stack[stackSize-2]=FP_OFF(myThread);
#endif

	stack[stackSize - 5] = 0x200;

#ifndef BCC_BLOCK_IGNORE
	stack[stackSize-6]=FP_SEG(Thread::wrapper);
	stack[stackSize-7]=FP_OFF(Thread::wrapper);

	ss=FP_SEG(stack+stackSize-16);
	sp=FP_OFF(stack+stackSize-16);
#endif
	bp = sp;

	blockedPCBs = new ListPCB();

	if (this->quant == 0)
		timeSliceFlag = 0;
	else
		timeSliceFlag = 1;

}

PCB::PCB() //PCB konstruktor za main thread
{

	this->retVal=0;
	stackSize = defaultStackSize; //inicijalizacija cisto zbog warninga
	ss = sp = 0; // isto

	timeSliceFlag = 1;
	stack = new unsigned[defaultStackSize / sizeof(unsigned)];
#ifndef BCC_BLOCK_IGNORE
	ss=FP_SEG(stack+defaultStackSize);
	sp=FP_OFF(stack+defaultStackSize);
#endif

	bp = sp;
	this->quant = defaultTimeSlice;
	myThread = 0;
	state = PCB::run;

	blockedPCBs = new ListPCB();

	allPCB->insertEnd(this);
}
PCB::~PCB() {
	LOCK
	delete[] stack;
	stack = 0;
	delete blockedPCBs;
	blockedPCBs=0;
	UNLOCK
}
;
ID getRunningID() {
	return PCB::running->myThread->getId();
}
void PCB::write() {
	LOCK
	if (this == PCB::idle->myPCB)
		cout << "Idle thread" << endl;
	else
		cout << "Thread with quant: " << this->quant << endl;
	UNLOCK
}

void PCB::waitToComplete() {
	if (PCB::running != PCB::idle->myPCB
			&& PCB::running->state != PCB::notStarted
			&& PCB::running->state != PCB::finished
			&& this->state != PCB::finished && this->state != PCB::notStarted
			/*&& this->state != PCB::blocked*/) {
		PCB::running->state = PCB::blocked;

		this->blockedPCBs->insertBegin((PCB*) PCB::running);

		dispatch();

	};
}

void PCB::exThread() {
	PCB* tmp = 0;

	while (1) {
		tmp = this->blockedPCBs->removeBegin();
		if (tmp == 0)
			break;
		tmp->state = PCB::ready;

		Scheduler::put(tmp);
	}
	tmp = 0;
}

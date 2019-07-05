/*
 * PCB.cpp
 *
 *  Created on: May 9, 2019
 *      Author: OS1
 */

#include "PCB.h"
#include "ListPCB.h"
#include "Lock.h"
#include "ListSig.h"
#include "Kernelse.h"

volatile int zahtevana_promena_konteksta = 0;
volatile int contextSwitchDelayed = 0; //ako sam stigao do 0 ali je zakljucano, kada lock==0 menjas kontekst
volatile unsigned counter = defaultTimeSlice; //treba da bude usaglasen sa main
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
				&& (PCB*) PCB::running != PCB::idlePCB) {
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

		zahtevana_promena_konteksta = 0;

		((PCB*)PCB::running)->checkSignals();

		if(PCB::running->killFlag==1)
		{
			PCB::running->state = PCB::finished;
			allPCB->notifyChilds((PCB*) PCB::running);
			((PCB*)PCB::running)->exThread();

			if(((PCB*)PCB::running)->parentPCB!=0){
				((PCB*)PCB::running)->parentPCB->signal(1);
			}
			((PCB*)PCB::running)->signal(2);

			PCB* oldRunning = (PCB*) PCB::running;
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


			delete[] oldRunning->stack;
			oldRunning->stack = 0;
			delete oldRunning->blockedPCBs;
			oldRunning->blockedPCBs = 0;
			delete oldRunning->queue;
			oldRunning->queue=0;
		/*	for (int i = 0; i < 16; i++) {
				delete oldRunning->allSignals[i];
				oldRunning->allSignals[i] = 0;
			}
		*/
			oldRunning->myThread=0;
			oldRunning->parentPCB=0;


		}
	}

}

PCB::PCB(StackSize sizestack, Time slicetime, Thread* const myThr) {

	//30 PTS init
		for (int i = 0; i < 16; i++) {
			allSignals[i] = new SigHandlerLst();
			if(PCB::running!=0){
				allSignals[i]->inheritSignals(PCB::running->allSignals[i]);
				this->blockedThis[i] = PCB::running->blockedThis[i];
			}
		}

	myThread = myThr;
	parentPCB = (PCB*)PCB::running;

	if (sizestack > 65535)
		sizestack = 65535;

	this->retVal = 0;
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

	this->queue = new Queue();
	this->killFlag=0;
}

PCB::PCB(Thread* myThr) //PCB konstruktor za main thread
{

	//30 PTS init
	for (int i = 0; i < 16; i++) {
		allSignals[i] = new SigHandlerLst();
		this->blockedThis[i] = 0;
	}
	this->retVal = 0;
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
	myThread = myThr; //potencijalni uzrok runtime error-a
	parentPCB = 0;
	state = PCB::run;

	blockedPCBs = new ListPCB();
	this->queue = new Queue();
	this->killFlag=0;

	mainPCB=this;
	PCB::running=this;

	Timer::init_handlers();
}
PCB::~PCB() {
	LOCK
	delete[] stack;
	stack = 0;
	delete blockedPCBs;
	blockedPCBs = 0;
	delete queue;
	for (int i = 0; i < 16; i++) {
		delete allSignals[i];
		allSignals[i] = 0;
	}
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

volatile short PCB::blockedGlobal[16] = { 0 };

void PCB::signal(SignalId signal) {
	if (signal > 15)
		return;

	queue->insertQ(signal);

}
void PCB::registerHandler(SignalId signal, SignalHandler handler) {
	if (signal > 15 || handler == 0)
		return;

	this->allSignals[signal]->addSignalHandler(handler);

}
void PCB::unregisterAllHandlers(SignalId id) {
	if (id > 15)
		return;

	this->allSignals[id]->removeAllHandlers();

}
void PCB::swap(SignalId id, SignalHandler hand1, SignalHandler hand2) {
	if (id > 15 || hand1 == 0 || hand2 == 0)
		return;

	this->allSignals[id]->swap(hand1, hand2);
}
void PCB::blockSignal(SignalId signal) {
	if (signal > 15)
		return;
	this->blockedThis[signal] = 1;
}
void PCB::blockSignalGlobally(SignalId signal) {
	if (signal > 15)
		return;

	PCB::blockedGlobal[signal] = 1;

}
void PCB::unblockSignal(SignalId signal) {
	if (signal > 15)
		return;
	this->blockedThis[signal] = 0;
}
void PCB::unblockSignalGlobally(SignalId signal) {
	if (signal > 15)
		return;
	PCB::blockedGlobal[signal] = 0;
}

void PCB::checkSignals() {

	LOCK
	Queue * blockedNow=new Queue();

	while(1)
	{
		SignalId ID=queue->removeQ();

		if(ID==16)
			break;

		if(PCB::blockedGlobal[ID]==0&&this->blockedThis[ID]==0){
			this->allSignals[ID]->callFunctions();
		}
		else
		{
			blockedNow->insertQ(ID);
		}
	}

	Queue* tmp=queue;
	queue=blockedNow;
	blockedNow=0;
	delete tmp;

	UNLOCK
}

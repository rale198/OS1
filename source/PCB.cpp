/*
 * PCB.cpp
 *
 *  Created on: May 9, 2019
 *      Author: OS1
 */

#include "PCB.h"
// Zabranjuje prekide
#define lock asm cli

// Dozvoljava prekide
#define unlock asm sti

volatile int lockFlag=1;
volatile int zahtevana_promena_konteksta=0;
volatile unsigned counter=defaultTimeSlice;


volatile unsigned tss=0,tsp=0,tbp=0;
void interrupt timer(...)
{

	if(zahtevana_promena_konteksta==0) counter--;

	if(counter==0||zahtevana_promena_konteksta==1)
	{

		if(lockFlag==1)
		{
			asm {

				mov tss,ss
				mov tsp,sp
				mov tbp,bp;
			}

			PCB::running->sp=tsp;
			PCB::running->ss=tss;
			PCB::running->bp=tbp;

			if(PCB::running->state!=PCB::finished/*dodati za idle nit*/)
			{
				PCB::running->state=PCB::ready;
				Scheduler::put((PCB*)(PCB::running));
			}

			PCB::running=Scheduler::get();
			PCB::running->state=PCB::run;

			tsp=PCB::running->sp;
			tbp=PCB::running->bp;
			tss=PCB::running->ss;

			counter=PCB::running->quant;

			asm{
				mov sp,tsp
				mov ss,tss
				mov bp,tbp
			}

		}
		else zahtevana_promena_konteksta=1;
	}


	if(zahtevana_promena_konteksta==0) asm int 60h;
}

PCB::PCB(StackSize sizestack,Time slicetime,Thread* const myThr)
{

	myThread=myThr;
	if(sizestack>65535) sizestack=65535;//gornja granica steka moze da bude 64KB

	this->ss=this->sp=0;
	this->state=notStarted;

	this->stackSize=sizestack/sizeof(unsigned);

	stack=new unsigned[stackSize];
	this->quant=slicetime;


    #ifndef BCC_BLOCK_IGNORE
	stack[stackSize-1]=FP_SEG(myThread);
	stack[stackSize-2]=FP_OFF(myThread);
    #endif

	stack[stackSize-5]=0x200;

#ifndef BCC_BLOCK_IGNORE
	stack[stackSize-6]=FP_SEG(Thread::wrapper);
	stack[stackSize-7]=FP_OFF(Thread::wrapper);

	ss=FP_SEG(stack+stackSize-16);
	sp=FP_OFF(stack+stackSize-16);
#endif
	bp=sp;
}

PCB::PCB()
{

	stack=new unsigned[defaultStackSize/sizeof(unsigned)];
#ifndef BCC_BLOCK_IGNORE
	ss=FP_SEG(stack+defaultStackSize);
	sp=FP_OFF(stack+defaultStackSize);
#endif

	bp=sp;
	this->quant=100;
	myThread=0;
	state=PCB::run;



}

volatile PCB* PCB::running=0;


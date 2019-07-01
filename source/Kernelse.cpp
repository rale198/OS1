/*
 * Kernelse.cpp
 *
 *  Created on: Jun 30, 2019
 *      Author: OS1
 */
#include "Kernelse.h"
#include "ListSEM.h"
#include "Lock.h"
ListSem* allSems=new ListSem();

KernelSem::KernelSem(int init, Semaphore* sem) {
	valSem = init;
	mySem = sem;
	(allSems)->insertBegin(this);
	blocked=new ListPCB();
}

KernelSem::~KernelSem() {
	mySem = 0;
	delete blocked;
}

int KernelSem::wait(Time maxTimeToWait) {
	LOCK
	this->valSem=this->valSem-1;

	if(this->valSem<0)
		block(maxTimeToWait);

	UNLOCK
	return 0;

}

int KernelSem::signal(int n) {

	if(n<0)
		return n;
	LOCK
	int ret=0;

	if(n==0)
	{
		if(this->valSem++<0)
		{
			ret=1;
			deblock();
		}
	}
	else
	{
		int val2=-valSem;
		ret=(val2<n)?val2:n; //number of unblocked threads

		if(ret<0)
			ret=0;

		for(int i=0;i<ret;i++)
		{
			deblock();
		}
		valSem+=n;

	}
	UNLOCK
	return ret;
}

int KernelSem::val() const {
	return this->valSem;
}

void KernelSem::deblock()
{
	PCB* pcb=blocked->removeEnd();
	pcb->state=PCB::ready;
	Scheduler::put(pcb);
}

void KernelSem::block(Time maxTimeToWait)
{
	PCB::running->state=PCB::blocked;
	blocked->insertBegin((PCB*)PCB::running);
	dispatch();
}

/*
 * Kernelse.cpp
 *
 *  Created on: Jun 30, 2019
 *      Author: OS1
 */
#include "Kernelse.h"
#include "Lock.h"
#include "SleepLst.h"
SleepList sleepList;

KernelSem::KernelSem(int init, Semaphore* sem) {
	LOCK
	valSem = init;
	mySem = sem;
	blocked=new ListPCB();
	UNLOCK
}

KernelSem::~KernelSem() {
	LOCK
	mySem = 0;
	delete blocked;
	UNLOCK
}

int KernelSem::wait(Time maxTimeToWait) {
	int passed=0;
	LOCK
	this->valSem=this->valSem-1;

	if(this->valSem<0){
		block(maxTimeToWait);
		passed=1;
	}

	UNLOCK
	if(passed)
		return PCB::running->retVal;
	return 1;

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
		ret=(val2<n)?val2:n;

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
	pcb->retVal=1;
	sleepList.updateSleepList(pcb);
}

void KernelSem::block(Time maxTimeToWait)
{
	PCB::running->state=PCB::blocked;
	blocked->insertBegin((PCB*)PCB::running);
	if(maxTimeToWait>0)
		sleepList.insert(maxTimeToWait,(PCB*)PCB::running,this);
	dispatch();
}

void KernelSem::updateList(PCB* pcb)
{
	LOCK
	this->blocked->updateList(pcb);
	UNLOCK
}

/*
 * KernelEv.cpp
 *
 *  Created on: Jul 2, 2019
 *      Author: OS1
 */

#include "KernelEv.h"
#include "Lock.h"

KernelEv::KernelEv(IVTNo ivtNo)
{
	LOCK

	this->ownerPCB=(PCB*)PCB::running;
	this->no=ivtNo;
	val=0;

	IVT[this->no]->myEvent=this;

	UNLOCK

}

KernelEv::~KernelEv()
{
	LOCK

	this->ownerPCB=0;

	UNLOCK

}

void KernelEv::wait()
{
	LOCK
	if(PCB::running->myThread->getId()==this->ownerPCB->myThread->getId())
	{
		if(val==0)
		{
			val=-1;
			PCB::running->state=PCB::blocked;
			dispatch();
		}
		else if(val==1)
			val=0;

	}
	UNLOCK
}

void KernelEv::signal()
{
	LOCK

	if(val==-1)
	{
		val=0;
		this->ownerPCB->state=PCB::ready;
		Scheduler::put(this->ownerPCB);
	}
	else
		val=1;
	UNLOCK
}




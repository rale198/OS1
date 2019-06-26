/*
 * Thread.cpp
 *
 *  Created on: May 9, 2019
 *      Author: OS1
 */

#include "Thread.h"
#include "ListPCB.h"
#include "PCB.h"
#include "Lock.h"
ID Thread::idgThread=0;
int Thread::test=0;
Thread::Thread (StackSize stackSize, Time timeSlice)
{
	id=++idgThread;

	myPCB=new PCB(stackSize,timeSlice,this);

	allPCB->insertEnd(myPCB);

};

void Thread::start()
{
	if(myPCB->state==PCB::notStarted)
	{
		myPCB->state=PCB::ready;
		Scheduler::put(this->myPCB);
	}

}
void Thread::waitToComplete(){

	LOCK

	myPCB->waitToComplete();

	UNLOCK


}

Thread::~Thread(){
	LOCK

	 delete [] myPCB;
	 myPCB=0;

	 UNLOCK
 }

ID Thread::getId(){return this->id;}

void dispatch()
{


#ifndef BCC_BLOCK_IGNORE
	asm cli;
#endif
	int before = lock;
	lock = 0;
	zahtevana_promena_konteksta=1;
	timer();
	lock = before;
#ifndef BCC_BLOCK_IGNORE
	asm sti;
#endif
}

void Thread::exitThread()
{

	LOCK
	Thread::test++; //test only
	this->myPCB->state=PCB::finished;
	dispatch();
	UNLOCK
}

void Thread::run()
{
	for(int i=0;i<10;i++)
	{
		LOCK
		cout<<"Thread: "<<this->getId()<<" Time slice: "<<this->myPCB->quant<<endl;
		UNLOCK

		if(this->getId()%2==0)
			Thread::getThreadById(3)->waitToComplete();
		else
			Thread::getThreadById(2)->waitToComplete();
		for(int k=0;k<30000;k++)
			for(int j=0;j<30000;j++);
	}
	LOCK
	cout<<"Thread finished"<<this->getId()<<endl;
	UNLOCK
}

ID Thread::getRunningId()
{

	return getRunningID();

}

Thread* Thread::getThreadById(ID id)
{
	LOCK

	Thread* ret=allPCB->getThreadById(id);

	UNLOCK
	return ret;
}

void Thread::wrapper(Thread* thread){
	 thread->run();

	 LOCK
	 thread->myPCB->exThread(); //pobrisati listu sa BLOCKPCBS i vratiti u scheduler
	 thread->exitThread();
	 UNLOCK
}

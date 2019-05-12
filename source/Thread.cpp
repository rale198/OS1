/*
 * Thread.cpp
 *
 *  Created on: May 9, 2019
 *      Author: OS1
 */

//#include "Thread.h"
#include  "Thread.h"
#include "PCB.h"

ID Thread::idgThread=0;

Thread::Thread (StackSize stackSize, Time timeSlice)
{
	id=++idgThread;

	//printf("%d\n",id);
	myPCB=new PCB(stackSize,timeSlice,this);

	//treba ubaciti u listu
};

void Thread::start()
{
	if(myPCB->state==PCB::notStarted)
	{
		myPCB->state=PCB::ready;
		Scheduler::put(this->myPCB);
	}

}
void Thread::waitToComplete(){} //TEK TREBA IMPLEMENTIRATI

 Thread::~Thread(){
	 delete [] myPCB;
	 myPCB=0;
 }

ID Thread::getId(){return this->id;}

void dispatch()
{

	asm cli;

	zahtevana_promena_konteksta=1;
	timer();

	asm sti;
}

void Thread::exitThread()
{

	this->myPCB->state=PCB::finished;
	dispatch();
}

void Thread::run()
{
	for(int i=0;i<30;i++)
	{
		lockFlag=0;
		cout<<"Thread: "<<this->getId()<<endl;
		lockFlag=1;

		for(int k=0;k<30000;k++)
			for(int j=0;j<30000;j++);
	}

	this->exitThread();
}

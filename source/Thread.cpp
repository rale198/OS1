/*
 * Thread.cpp
 *
 *  Created on: May 9, 2019
 *      Author: OS1
 */

//#include "Thread.h"
#include  "PCB.H"
ID Thread::idgThread=0;


Thread::Thread (StackSize stackSize, Time timeSlice)
{
	id=++idgThread;

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
void Thread::waitToComplete(){

}
 Thread::~Thread(){
	 delete [] myPCB;
	 myPCB=0;

 }

ID Thread::getId(){

	return this->id;//vratiti id
}



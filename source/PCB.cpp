/*
 * PCB.cpp
 *
 *  Created on: May 9, 2019
 *      Author: OS1
 */

#include "PCB.h"


PCB::PCB(StackSize sizestack,Time slicetime,Thread* const myThread)
{

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



/*
 * PCB.h
 *
 *  Created on: May 9, 2019
 *      Author: OS1
 */

#ifndef HEADERS_PCB_H_
#define HEADERS_PCB_H_

#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include "Thread.h"
#include "SCHEDULE.H"

class Thread;

class PCB{

public:
enum State {ready=0,blocked,running,finished,notStarted}; //ovim znamo u kom stanju je trenutna nit
 //proveriti da li treba da bude javno

friend class Thread;

unsigned * stack;
unsigned ss;
unsigned sp;
unsigned bp;
unsigned stackSize;
int quant; //timeSlice umnozak;
State state;
//treba ubaciti listu ready PCB-ova;

~PCB(){};

//PCB();
PCB(StackSize sizestack,Time slicetime,Thread* const myThread);



};
#endif /* HEADERS_PCB_H_ */

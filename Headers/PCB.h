/*
 * PCB.h
 *
 *  Created on: May 9, 2019
 *      Author: OS1
 */

#ifndef HEADERS_PCB_H_
#define HEADERS_PCB_H_

#include <iostream.h>
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include "Idle.h"
#include "SCHEDULE.H"
#include "ListPCB.h"

extern volatile unsigned counter;
extern volatile int zahtevana_promena_konteksta;
extern volatile int contextSwitchDelayed;
void interrupt timer(...);

class Thread;
class Timer;

extern ListPCB* allPCB;
ID getRunningID();

class PCB {

public:
	enum State {
		ready = 0, blocked, run, finished, notStarted
	};

	friend class Thread;
	friend class ListPCB;
	friend class Idle;
	friend class SleepList;

	static volatile PCB* running;
	static volatile PCB* idlePCB;
	static volatile Idle* idle;
	ListPCB* blockedPCBs;

	unsigned *stack;
	unsigned ss;
	unsigned sp;
	unsigned bp;
	unsigned stackSize;
	int quant; //timeSlice umnozak;
	State state;
	Thread* myThread;

	int timeSliceFlag;
//treba ubaciti listu ready PCB-ova;

	~PCB();
	PCB(StackSize sizestack, Time slicetime, Thread* const myThread);
	PCB();

	void waitToComplete();
	void exThread();
	void write();
	unsigned retVal;
	// test only
};
#endif /* HEADERS_PCB_H_ */

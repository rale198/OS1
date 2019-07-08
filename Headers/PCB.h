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
#include "ListSig.h"
#include "Queue.h"
extern volatile unsigned counter;
extern volatile int zahtevana_promena_konteksta;
extern volatile int contextSwitchDelayed;
void interrupt timer(...);

class Thread;
class Timer;
class Queue;
class SigHandlerLst;
class Idle;

extern ListPCB* allPCB;
ID getRunningID();

class PCB {

public:
	enum State {
		ready = 0, blocked, run, finished, notStarted
	};

	static volatile PCB* running;
	static volatile PCB* idlePCB;
	static volatile Idle* idle;
	static volatile short blockedGlobal[16];

	Thread* myThread;
	PCB* parentPCB;

	short blockedThis[16];
	SigHandlerLst* allSignals[16];
	ListPCB* blockedPCBs;
	Queue* queue;

	unsigned retVal;

	unsigned *stack;
	unsigned stackSize;
	unsigned ss;
	unsigned sp;
	unsigned bp;

	int quant;
	State state;


	int timeSliceFlag;
	int killFlag;

	~PCB();
	PCB(StackSize sizestack, Time slicetime, Thread* const myThread);
	PCB(Thread* myThr);

	void waitToComplete();
	void exThread();

	void signal(SignalId signal);
	void registerHandler(SignalId signal, SignalHandler handler);
	void unregisterAllHandlers(SignalId id);
	void swap(SignalId id, SignalHandler hand1, SignalHandler hand2);
	void blockSignal(SignalId signal);
	static void blockSignalGlobally(SignalId signal);
	void unblockSignal(SignalId signal);
	static void unblockSignalGlobally(SignalId signal);

	void checkSignals();
};
#endif /* HEADERS_PCB_H_ */

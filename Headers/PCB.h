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
	friend class SigHandlerLst;
	friend class Timer;

	static volatile PCB* running;
	static volatile PCB* idlePCB;
	static volatile Idle* idle;

	//30pts deo
	//POTREBNA INICIJALIZACIJA
	static volatile short blockedGlobal[16];
	short blockedThis[16];
	SigHandlerLst* allSignals[16];
	ListPCB* blockedPCBs;
	Queue* queue;
	int killFlag;

	unsigned *stack;
	unsigned ss;
	unsigned sp;
	unsigned bp;
	unsigned stackSize;
	int quant; //timeSlice umnozak;
	State state;
	Thread* myThread;
	PCB* parentPCB;

	int timeSliceFlag;
//treba ubaciti listu ready PCB-ova;

	~PCB();
	PCB(StackSize sizestack, Time slicetime, Thread* const myThread);
	PCB(Thread* myThr);

	void waitToComplete();
	void exThread();
	void write();
	unsigned retVal;


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

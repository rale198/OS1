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
#include "Thread.h"
#include "SCHEDULE.H"

extern volatile int lockFlag;
extern volatile unsigned counter;
extern volatile int zahtevana_promena_konteksta;
void interrupt timer(...); //mozda ne treba imati 3 tacke

class Thread;
class Timer;

ID getRunningID();

class PCB{

public:
enum State {ready=0,blocked,run,finished,notStarted}; //ovim znamo u kom stanju je trenutna nit
 //proveriti da li treba da bude javno

friend class Thread;

static volatile PCB* running;


unsigned * stack;
unsigned ss;
unsigned sp;
unsigned bp;
unsigned stackSize;
int quant; //timeSlice umnozak;
State state;
Thread* myThread;

//treba ubaciti listu ready PCB-ova;

~PCB(){ delete [] stack; stack=0;};

//PCB();
PCB(StackSize sizestack,Time slicetime,Thread* const myThread);
PCB();


void write(); // test only
};
#endif /* HEADERS_PCB_H_ */

/*
 * main.cpp
 *
 *  Created on: May 11, 2019
 *      Author: OS1
 */
#include "PCB.h"
#include "Timer.h"
#include "Thread.h"
#include "ListPCB.h"
#include "Lock.h"
#include "Kernelse.h"
#include <math.h>

int userMain(int,char**);
ListPCB* allPCB = new ListPCB();
volatile PCB* mainPCB=0;
volatile Thread* mainThread=new Thread(1);
int main(int argc, char* argv[]) {

	Timer::init_timer();

	int i = userMain(argc, argv);

	Timer::restore_timer();
	Timer::restore_system();
	cout << "Program finished" << endl;
	return i;
}

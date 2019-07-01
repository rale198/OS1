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
volatile PCB* mainPCB = new PCB();

int main(int argc, char* argv[]) {

	PCB::running = mainPCB;

	Timer::init_timer();

	int i = userMain(argc, argv);

	Timer::restore_timer();
	delete allPCB;
	cout << "Program finished" << endl;
	return i;
}

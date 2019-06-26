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
#include <math.h>

volatile PCB* mainPCB = new PCB();
int userMain(int argc, char* argv[]) {

#ifndef BCC_BLOCK_IGNORE
	HARD_LOCK
#endif
	//poseban konstruktor za main thread
	Thread* t1 = new Thread(defaultStackSize, 5);
	Thread* t2 = new Thread(defaultStackSize, 10);
	Thread* t3 = new Thread(defaultStackSize, 0);
	Thread* t4 = new Thread(defaultStackSize, 2);
	Thread* t5 = new Thread(defaultStackSize, 6);
	Thread* t6 = new Thread(defaultStackSize, 7);
	Thread* t7 = new Thread(defaultStackSize, 8);
	Thread* t8 = new Thread(defaultStackSize, 9);
	Thread* t9 = new Thread(defaultStackSize, 10);
	Thread* t10 = new Thread(defaultStackSize, 11);
	Thread* t11 = new Thread(defaultStackSize, 12);

	t1->start();
	t2->start();
	t3->start();
	t4->start();
	t5->start();
	t6->start();
	t7->start();
	t8->start();
	t9->start();
	t10->start();
	t11->start();
#ifndef BCC_BLOCK_IGNORE
	HARD_UNLOCK
#endif

	for (int i = 0; i < 10; i++) {

		LOCK
		cout << "Main: " << i << endl;
		UNLOCK
		for (int ik = 0; ik < 30000; ik++)
			for (int j = 0; j < 30000; j++)
				;
	}

	t1->waitToComplete();
	t2->waitToComplete();
	t4->waitToComplete();

	return 0;
}
int main(int argc, char* argv[]) {

	PCB::running = mainPCB;

	Timer::init_timer();

	int i = userMain(argc, argv);

	Timer::restore_timer();

	cout << "Program finished" << endl;
	return i;
}

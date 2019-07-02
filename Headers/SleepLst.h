/*
 * SleepLst.h
 *
 *  Created on: Jul 1, 2019
 *      Author: OS1
 */

#ifndef HEADERS_SLEEPLST_H_
#define HEADERS_SLEEPLST_H_
#include "PCB.h"
#include "Kernelse.h"
#include "Lock.h"

class SleepList
{
	struct Nodes
	{
		Time quant;
		KernelSem* mySem;
		PCB* pcb;
		Nodes* next;

		Nodes(Time q,KernelSem*k,PCB* p)
		{
			pcb=p;
			quant=q;
			mySem=k;
			next=0;
		}
	};

	Nodes* head;

public:

	SleepList();
	~SleepList();
	void updateSleepList(PCB*);
	void insert(Time,PCB*,KernelSem*);
	void timerUpdate();
	void ispis();
};




#endif /* HEADERS_SLEEPLST_H_ */

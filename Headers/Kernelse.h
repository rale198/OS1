/*
 * Kernelse.h
 *
 *  Created on: Jun 30, 2019
 *      Author: OS1
 */
#ifndef HEADERS_KERNELSE_H_
#define HEADERS_KERNELSE_H_
#include "Semaphor.h"
#include "PCB.h"

class ListSem;
class Semaphore;
class SleepList;

extern ListSem* allSems;
extern SleepList sleepList;
class KernelSem {

	friend class Semaphore;
	friend class ListSem;
	friend class SleepList;
private:

	int valSem;
	Semaphore* mySem;
	ListPCB* blocked;

public:

	KernelSem(int init,Semaphore* sem);
	virtual ~KernelSem();

	int wait(Time maxTimeToWait);
	int signal(int n);
	int val() const;

private:

	void updateList(PCB*);
	void block(Time);
	void deblock();

};

#endif /* HEADERS_KERNELSE_H_ */

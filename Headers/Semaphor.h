/*
 * Semaphor.h
 *
 *  Created on: Jun 30, 2019
 *      Author: OS1
 */
#ifndef HEADERS_SEMAPHOR_H_
#define HEADERS_SEMAPHOR_H_

#include <iostream.h>
typedef unsigned int Time;

class KernelSem;
class ListSem;

class Semaphore {
public:
	Semaphore(int init = 1);
	virtual ~Semaphore();
	virtual int wait(Time maxTimeToWait);
	virtual int signal(int n = 0);
	int val() const; // Returns the current value of the semaphore
	friend class ListSem;
	friend class KernelSem;
	//KernelSem* myImpl;
private:
	KernelSem* myImpl;
};

#endif /* HEADERS_SEMAPHOR_H_ */

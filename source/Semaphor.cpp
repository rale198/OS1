/*
 * Semaphor.cpp
 *
 *  Created on: Jun 30, 2019
 *      Author: OS1
 */

#include "Kernelse.h"
#include "Semaphor.h"
#include "Lock.h"
#include "PCB.h"
Semaphore::Semaphore(int init)
{
	this->myImpl=new KernelSem(init,this);
}

Semaphore::~Semaphore(){
	delete this->myImpl;
};

int Semaphore::wait(Time maxTimeToWait)
{
	return this->myImpl->wait(maxTimeToWait);
}

int Semaphore::signal(int n)
{
	return this->myImpl->signal(n);
}

int Semaphore::val() const
{
	return this->myImpl->val();
}

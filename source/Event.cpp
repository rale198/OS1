/*
 * Event.cpp
 *
 *  Created on: Jul 2, 2019
 *      Author: OS1
 */
#include "Event.h"
#include "KernelEv.h"
#include "Lock.h"
Event::Event(IVTNo ivtNo)
{
	this->myImpl=new KernelEv(ivtNo);
}

Event::~Event()
{
	LOCK
	delete this->myImpl;
	UNLOCK
}

void Event::wait()
{
	this->myImpl->wait();
}

void Event::signal()
{
	this->myImpl->signal();
}





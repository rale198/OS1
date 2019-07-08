/*
 * Thread.cpp
 *
 *  Created on: May 9, 2019
 *      Author: OS1
 */

#include "Thread.h"
#include "ListPCB.h"
#include "PCB.h"
#include "Lock.h"
ID Thread::idgThread = 0;
int Thread::test = 0;
volatile PCB* PCB::idlePCB = 0;
Thread::Thread(StackSize stackSize, Time timeSlice) {
	LOCK
	id = ++idgThread;
	myPCB = new PCB(stackSize, timeSlice, this);
	if (id == 1)
		PCB::idlePCB = myPCB;
	allPCB->insertBegin(myPCB);
	UNLOCK

}
;

Thread::Thread(int a) {
	LOCK
	a++;
	this->id = 0;
	myPCB = new PCB(this);

	allPCB->insertBegin(myPCB);
	UNLOCK

}

void Thread::start() {
	LOCK
	if (myPCB->state == PCB::notStarted) {
		myPCB->state = PCB::ready;
		Scheduler::put(this->myPCB);
	}
	UNLOCK

}
void Thread::waitToComplete() {

	LOCK

	myPCB->waitToComplete();

	UNLOCK

}

Thread::~Thread() {
	LOCK

	delete myPCB;
	myPCB = 0;

	UNLOCK
}

ID Thread::getId() {
	return this->id;
}

void dispatch() {
#ifndef BCC_BLOCK_IGNORE
	LOCK_TIMER
#endif
	int before = lock;
	lock = 0;
	zahtevana_promena_konteksta = 1;
	timer();
	lock = before;
#ifndef BCC_BLOCK_IGNORE
	UNLOCK_TIMER
#endif
}

void Thread::exitThread() {

	LOCK
	this->myPCB->state = PCB::finished;
	dispatch();
	UNLOCK
}

ID Thread::getRunningId() {

	return getRunningID();

}

Thread* Thread::getThreadById(ID id) {
	LOCK

	Thread* ret = allPCB->getThreadById(id);

	UNLOCK
	return ret;
}

void Thread::wrapper(Thread* thread) {
	thread->run();

	LOCK
	thread->myPCB->exThread();
	if (thread->myPCB->parentPCB != 0)
		thread->myPCB->parentPCB->signal(1);
	if (thread->myPCB != 0)
		thread->myPCB->signal(2);
	thread->exitThread();
	UNLOCK
}

void Thread::signal(SignalId signal) {
	LOCK
	this->myPCB->signal(signal);
	UNLOCK
}
void Thread::registerHandler(SignalId signal, SignalHandler handler) {
	LOCK
	this->myPCB->registerHandler(signal, handler);
	UNLOCK
}
void Thread::unregisterAllHandlers(SignalId id) {
	LOCK
	this->myPCB->unregisterAllHandlers(id);
	UNLOCK
}
void Thread::swap(SignalId id, SignalHandler hand1, SignalHandler hand2) {
	LOCK
	this->myPCB->swap(id, hand1, hand2);
	UNLOCK
}
void Thread::blockSignal(SignalId signal) {
	LOCK
	this->myPCB->blockSignal(signal);
	UNLOCK
}
void Thread::blockSignalGlobally(SignalId signal) {
	LOCK
	PCB::blockSignalGlobally(signal);
	UNLOCK
}
void Thread::unblockSignal(SignalId signal) {
	LOCK
	this->myPCB->unblockSignal(signal);
	UNLOCK
}
void Thread::unblockSignalGlobally(SignalId signal) {
	LOCK
	PCB::unblockSignalGlobally(signal);
	UNLOCK
}

void Thread::notifyMyThread() {
	this->myPCB = 0;
}


/*
 * Thread.h
 *
 *  Created on: May 9, 2019
 *      Author: OS1
 */

#ifndef HEADERS_THREAD_H_
#define HEADERS_THREAD_H_

#include<iostream.h>
typedef unsigned long StackSize;
const StackSize defaultStackSize = 4096;
typedef unsigned int Time; // time, x 55ms
const Time defaultTimeSlice = 2; // default = 2*55ms
typedef int ID;

typedef void (*SignalHandler)();
typedef unsigned SignalId;

class PCB; // Kernel's implementation of a user's thread
class ListPCB;

class Thread {
public:

 static int test; //test for waitToComplete only
 void start();
 void waitToComplete();
 virtual ~Thread();
 ID getId();
 static ID getRunningId();
 static Thread * getThreadById(ID id);

Thread(int);

protected:

 friend class ListPCB;
 friend class PCB;
 Thread (StackSize stackSize = defaultStackSize, Time timeSlice =
defaultTimeSlice);

virtual void run(){};
static void wrapper(Thread* thread);

private:
 ID id;
 static ID idgThread;
 PCB* myPCB;

 void exitThread();

public:
 void signal(SignalId signal);
 void registerHandler(SignalId signal, SignalHandler handler);
 void unregisterAllHandlers(SignalId id);
 void swap(SignalId id, SignalHandler hand1, SignalHandler hand2);
 void blockSignal(SignalId signal);
 static void blockSignalGlobally(SignalId signal);
 void unblockSignal(SignalId signal);
 static void unblockSignalGlobally(SignalId signal);
 void notifyMyThread();
};
void dispatch ();



#endif /* HEADERS_THREAD_H_ */

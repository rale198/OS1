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



class PCB; // Kernel's implementation of a user's thread

class Thread {
public:

 void start();
 void waitToComplete();
 virtual ~Thread();
 ID getId();
 static ID getRunningId();
 static Thread * getThreadById(ID id); //napraviti funkciju

 Thread (StackSize stackSize = defaultStackSize, Time timeSlice =
 defaultTimeSlice);
 PCB* myPCB;

protected:

 friend class PCB;
/* Thread (StackSize stackSize = defaultStackSize, Time timeSlice =
defaultTimeSlice);
*/
 virtual void run();

private:
 ID id;
 static ID idgThread;
// PCB* myPCB;

 static void wrapper(Thread* thread){
	 thread->run();
 } //treaba dopuniti
 void exitThread();
};
void dispatch ();



#endif /* HEADERS_THREAD_H_ */

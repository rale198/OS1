/*
 * Timer.h
 *
 *  Created on: May 12, 2019
 *      Author: OS1
 */

#ifndef HEADERS_TIMER_H_
#define HEADERS_TIMER_H_

class PCB;
class Thread;
extern unsigned oldTimerOFF;
extern unsigned oldTimerSEG;
extern void killThread();
extern void callParent();
extern void callMySelf();
extern volatile PCB* mainPCB;
extern volatile Thread* mainThread;
void tick();
class Timer{

public:
	static void restore_timer();
	static void init_timer();
	static void init_handlers();

};


#endif /* HEADERS_TIMER_H_ */

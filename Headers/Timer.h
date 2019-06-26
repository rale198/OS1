/*
 * Timer.h
 *
 *  Created on: May 12, 2019
 *      Author: OS1
 */

#ifndef HEADERS_TIMER_H_
#define HEADERS_TIMER_H_

extern unsigned oldTimerOFF;
extern unsigned oldTimerSEG;

void tick();
class Timer{

public:
	static void restore_timer();
	static void init_timer();

};


#endif /* HEADERS_TIMER_H_ */

/*
 * Tick.h
 *
 *  Created on: Jun 1, 2019
 *      Author: OS1
 */

#ifndef HEADERS_LOCK_H_
#define HEADERS_LOCK_H_
#include "PCB.h"

void dispatch();
extern unsigned volatile lock;

#define LOCK_TIMER asm cli;
#define UNLOCK_TIMER asm sti;

#define HARD_LOCK asm { pushf; cli; }
#define HARD_UNLOCK asm popf;

#define LOCKED (lock>0)
#define LOCK lock=lock+1;
#define UNLOCK lock=lock-1;\
	if(lock==0&&contextSwitchDelayed==1){\
		dispatch();\
	}

#endif /* HEADERS_LOCK_H_ */

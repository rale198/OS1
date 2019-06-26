/*
 * Tick.h
 *
 *  Created on: Jun 1, 2019
 *      Author: OS1
 */

#ifndef HEADERS_LOCK_H_
#define HEADERS_LOCK_H_
#include "PCB.h"

extern unsigned volatile lock;
void dispatch();

#define HARD_LOCK asm { pushf; cli; }
#define HARD_UNLOCK asm popf;

#define LOCK ++lock;
#define UNLOCK if(--lock==0&&contextSwitchDelayed==1/*&&(--lock==0)*/){dispatch();}

#endif /* HEADERS_LOCK_H_ */

/*
 * Idle.h
 *
 *  Created on: May 13, 2019
 *      Author: OS1
 */

#ifndef HEADERS_IDLE_H_
#define HEADERS_IDLE_H_

#include "Thread.h"
#include "Lock.h"
#include "Kernel.h"
class Idle: public Thread {
public:

	Idle() :
			Thread() {
	}
	;

	void run();

};

#endif /* HEADERS_IDLE_H_ */

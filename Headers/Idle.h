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

class Idle: public Thread {
public:

	Idle() :
			Thread(defaultStackSize, 1) {
	}
	;

	void run();

};

#endif /* HEADERS_IDLE_H_ */

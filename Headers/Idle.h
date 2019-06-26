/*
 * Idle.h
 *
 *  Created on: May 13, 2019
 *      Author: OS1
 */

#ifndef HEADERS_IDLE_H_
#define HEADERS_IDLE_H_

#include "Thread.h"

class Idle: public Thread {
public:

	Idle() :
			Thread() {
	}
	;

	void run() {

		while (1)
			;
	}
	;
};

#endif /* HEADERS_IDLE_H_ */

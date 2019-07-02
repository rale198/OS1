/*
 * Kernel.h
 *
 *  Created on: Jun 26, 2019
 *      Author: OS1
 */

#ifndef HEADERS_KERNEL_H_
#define HEADERS_KERNEL_H_

#include "PCB.h"
#include "Timer.h"
#include "Thread.h"
#include "ListPCB.h"
#include "Lock.h"
#include "Kernelse.h"
#include "ListSEM.h"
#include "SleepLst.h"
#include <math.h>

int syncPrintf(const char *format, ...);

#endif /* HEADERS_KERNEL_H_ */

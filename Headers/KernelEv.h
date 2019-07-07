/*
 * KernelEv.h
 *
 *  Created on: Jul 2, 2019
 *      Author: OS1
 */

#ifndef HEADERS_KERNELEV_H_
#define HEADERS_KERNELEV_H_
#include "Event.h"
#include "PCB.h"
class KernelEv {
	friend class Event;
	friend class IVTEntry;
public:
	KernelEv(IVTNo ivtNo);
	~KernelEv();

private:
	void wait();
	void signal();

	PCB* ownerPCB;
	IVTNo no;
	int val;
};

#endif /* HEADERS_KERNELEV_H_ */

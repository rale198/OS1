/*
 * IVTEntry.h
 *
 *  Created on: Jul 3, 2019
 *      Author: OS1
 */

#ifndef HEADERS_IVTENTRY_H_
#define HEADERS_IVTENTRY_H_

#include "KernelEv.h"
#include <DOS.H>
typedef void interrupt(*pRoutine)(...);
class IVTEntry;

extern IVTEntry* IVT[256];
class IVTEntry{

	friend class KernelEv;
public:

	IVTEntry(IVTNo no,pRoutine new_routine);
	virtual ~IVTEntry();

	void signal();
	void callOldRoutine();

protected:
	KernelEv* myEvent;
	IVTNo no;
	pRoutine old_routine;

};



#endif /* HEADERS_IVTENTRY_H_ */

/*
 * IVTentry.cpp
 *
 *  Created on: Jul 3, 2019
 *      Author: OS1
 */
#include "IVTEntry.h"

IVTEntry* IVT[256]={0};
IVTEntry::IVTEntry(IVTNo no,pRoutine new_routine)
{
	this->no=no;
	myEvent=0;
	old_routine=0;
	IVT[no]=this;

#ifndef BCC_BLOCK_IGNORE
	old_routine=getvect(no);
	setvect(no,new_routine);
#endif
}

IVTEntry::~IVTEntry()
{
	this->myEvent=0;
	IVT[no]=0;

#ifndef BCC_BLOCK_IGNORE
	setvect(no,old_routine);
#endif
}

void IVTEntry::signal()
{
	this->myEvent->signal();
}

void IVTEntry::callOldRoutine()
{
	old_routine();
}

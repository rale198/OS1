/*
 * ListSEM.h
 *
 *  Created on: Jun 30, 2019
 *      Author: OS1
 */

#ifndef HEADERS_LISTSEM_H_
#define HEADERS_LISTSEM_H_

#include "Kernelse.h"
#include "Lock.h"


class ListSem{

public:
	struct NodeSem{
		NodeSem* next;
		KernelSem* sem;

		NodeSem(KernelSem* sm)
		{
			sem=sm;
			next=0;
		}
	};

	ListSem();
	~ListSem();
	void insertBegin(KernelSem*);
	KernelSem* removeBegin();

private:
	NodeSem* head,*prev;
};


#endif /* HEADERS_LISTSEM_H_ */

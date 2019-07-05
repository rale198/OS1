/*
 * Queue.h
 *
 *  Created on: Jul 4, 2019
 *      Author: OS1
 */

#ifndef HEADERS_QUEUE_H_
#define HEADERS_QUEUE_H_
#include "Thread.h"
#include "PCB.h"
class Queue
{
	struct NodeQue
	{
		SignalId id;
		NodeQue* next;

		NodeQue(SignalId idd)
		{
			this->id=idd;
			next=0;
		}
	};


private:
	NodeQue* head,*prev;

public:

	Queue();
	~Queue();

	void ispis();
	void insertQ(SignalId ID);
	SignalId removeQ();
};



#endif /* HEADERS_QUEUE_H_ */

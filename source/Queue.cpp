#/*
 * Queue.cpp
 *
 *  Created on: Jul 4, 2019
 *      Author: OS1
 */
#include "Queue.h"

Queue::Queue() {
	head = prev = 0;
}

Queue::~Queue() {
	NodeQue* tmp = 0;

	while (head != 0) {
		tmp = head;
		head = head->next;
		delete tmp;
	}

	head = prev = tmp = 0;
}

void Queue::insertQ(SignalId ID) {

	NodeQue* novi = new NodeQue(ID);
	if (head == 0)
		head = novi;
	else
		prev->next = novi;
	prev = novi;
}

SignalId Queue::removeQ() {
	NodeQue* tmp = head;
	SignalId ret = 16;

	if (tmp != 0) {
		head = head->next;
		ret = tmp->id;
	}

	if (head == 0) {
		prev = 0;
	}

	if (tmp != 0)
		delete tmp;
	return ret;
}

void Queue::ispis()
{
	for(NodeQue *tmp=head;tmp!=0;tmp=tmp->next)
	{
		LOCK
		cout<<tmp->id<<endl;
		UNLOCK
	}
}

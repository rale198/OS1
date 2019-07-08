/*
 * ListPCB.h
 *
 *  Created on: May 13, 2019
 *      Author: OS1
 */

#ifndef HEADERS_LISTPCB_H_
#define HEADERS_LISTPCB_H_
#include "PCB.h"
#include "Lock.h"

class ListPCB {

public:

	struct Node {
		PCB* pcb;
		Node* next;

		Node(PCB*p) {
			pcb = p;
			next = 0;
		}
		;
	};

	ListPCB();
	virtual ~ListPCB();

	void insertBegin(PCB*);
	PCB* removeBegin();
	void insertEnd(PCB*);
	PCB* removeEnd();

	Thread* getThreadById(ID);

	void updateList(PCB*);
	void notifyChilds(PCB*);
private:
	Node *head, *prev;
};

#endif /* HEADERS_LISTPCB_H_ */

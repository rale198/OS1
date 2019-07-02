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

	ListPCB() {
		head = prev = 0;
		size = 0;
	}
	;
	~ListPCB();
	void insertBegin(PCB*);
	void insertEnd(PCB*);
	PCB* removeEnd();
	PCB* removeBegin();
	Thread* getThreadById(ID);

	int getSize() {
		return size;
	}
	;
	void write();
	void updateList(PCB*);
private:

	int size;
	Node *head, *prev;
};

#endif /* HEADERS_LISTPCB_H_ */

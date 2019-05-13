/*
 * ListPCB.cpp
 *
 *  Created on: May 13, 2019
 *      Author: OS1
 */


#include "ListPCB.h"


ListPCB::~ListPCB()
{
	Node* tmp=0;

	while(head!=0)
	{
		tmp=head;
		head=head->next;
		delete tmp;
	}

	head=prev=tmp=0;
}

void ListPCB::insertBegin(PCB* p)
{

	Node * novi=new Node(p);
	if(head==0)
	{
		head=novi;
		prev=novi;
	}
	else
	{
		novi->next=head;
		head=novi;
	}

}

void ListPCB::insertEnd(PCB *p)
{
	Node* novi=new Node(p);
		if(head==0) head=novi;
		else prev->next=novi;
		prev=novi;
}
void ListPCB::write()
{

	for(Node* tmp=head;tmp!=0;tmp=tmp->next) tmp->pcb->write();
}

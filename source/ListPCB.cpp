/*
 * ListPCB.cpp
 *
 *  Created on: May 13, 2019
 *      Author: OS1
 */


#include "ListPCB.h"


ListPCB::~ListPCB(){

	Node* tmp=0;

	while(head!=0)
	{
		tmp=head;
		head=head->next;
		delete tmp;
	}

	head=prev=tmp=0;
}

void ListPCB::insertBegin(PCB* p){


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

	size++;
}

void ListPCB::insertEnd(PCB *p){

	Node* novi=new Node(p);
		if(head==0) head=novi;
		else prev->next=novi;
		prev=novi;

	size++;
}
void ListPCB::write()
{

	for(Node* tmp=head;tmp!=0;tmp=tmp->next) tmp->pcb->write();
}

PCB* ListPCB::removeEnd(){

	Node* pret=0;
	Node*tmp=head;
	PCB* pcb=0;

	if(tmp!=0)
	{

		while(tmp->next!=0)
		{
			pret=tmp;
			tmp=tmp->next;
		}

		pcb=tmp->pcb;

		delete tmp;

		if(pret!=0)
		{
			pret->next=0;
			prev=pret;
		}
		else {
			head=0;
		}

	}
	return pcb;
}

PCB* ListPCB::removeBegin(){
	Node* tmp=head;
	PCB* pcb=0;

	if(tmp!=0){
		head=head->next;
		pcb=tmp->pcb;
	}

	if(head==0){
		prev=0;
	}

	if(tmp!=0) delete tmp;
	return pcb;
}

Thread* ListPCB::getThreadById(ID id)
{

	Thread *ret=0;

	Node* tmp=0;
	for(tmp=head;tmp!=0;tmp=tmp->next){

		if(tmp->pcb->myThread->getId()==id){

			ret=tmp->pcb->myThread;
			tmp=0;
			return ret;
		}
	}
	return ret;
}

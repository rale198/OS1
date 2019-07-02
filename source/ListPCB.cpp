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

		pcb=tmp->pcb; //mozda ovde ima bug

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

void ListPCB::updateList(PCB*pcb)
{

	if(head==0)
		return;

	Node*prv=0,*tmp=head,*nxt=head->next;

	while(tmp!=0&&tmp->pcb!=pcb)
	{
		prv=tmp;
		tmp=nxt;
		nxt=nxt->next;
	}

	if(tmp==0)
		return;

	if(prv!=0&&nxt!=0)
	{
		prv->next=nxt;
		tmp->next=0;
		delete tmp;
	}
	else if(nxt==0&&prv==0)
	{
		delete tmp;
		head=0;
		prev=0;
	}
	else if(nxt==0)
	{
		prv->next=0;
		prev=prv;
		tmp->next=0;
		delete tmp;
	}
	else if(prv==0)
	{
		if(nxt!=0)
		{
			head=nxt;
		}
		else head=0;
		tmp->next=0;
		delete tmp;
	}
}

/*
 * ListSEM.cpp
 *
 *  Created on: Jun 30, 2019
 *      Author: OS1
 */
#include "ListSEM.h"


ListSem::ListSem()
{
	head=prev=0;
}

ListSem::~ListSem()
{
	NodeSem* tmp=0;

	while(head!=0)
	{
		tmp=head;
		head=head->next;
		delete tmp;
	}

	head=prev=tmp=0;
}

void ListSem::insertBegin(KernelSem* s)
{
	NodeSem * novi=new NodeSem(s);
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

KernelSem* ListSem::removeBegin()
{
	NodeSem* tmp=head;
	KernelSem* kernelsem=0;

	if(tmp!=0){
		head=head->next;
		kernelsem=tmp->sem;
	}

	if(head==0){
		prev=0;
	}

	if(tmp!=0) delete tmp;
	return kernelsem;

}

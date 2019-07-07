/*
 * SleepLst.cpp
 *
 *  Created on: Jul 1, 2019
 *      Author: OS1
 */

#include "SleepLst.h"

SleepList::SleepList()
{
	head=0;
}

SleepList::~SleepList()
{
	Nodes* tmp=0;

	while(head!=0)
	{
		tmp=head;
		head=head->next;
		delete tmp;
	}

	head=tmp=0;
}

void SleepList::timerUpdate()
{

	if(head==0)
		return;

	head->quant--;

	while(head!=0&&head->quant==0)
	{
		Nodes*tmp=head;
		head=head->next;

		PCB* pcb=tmp->pcb;
		pcb->state=PCB::ready;
		Scheduler::put(pcb);
		tmp->mySem->valSem++;
		tmp->mySem->updateList(pcb);

		pcb->retVal=0;

		delete tmp;
	}
}

void SleepList::insert(Time q,PCB* p,KernelSem*k)
{
	Nodes* novi=new Nodes(q,k,p);

	if(head==0)
		head=novi;
	else{
		Nodes*tmp=head,*prv=0;

		while(tmp!=0&&tmp->quant<novi->quant)
		{
			novi->quant-=tmp->quant;
			prv=tmp;
			tmp=tmp->next;
		}

		if(prv==0)
		{
			novi->next=head;
			head->quant-=novi->quant;
			head=novi;
		}
		else if(tmp==0)
		{
			prv->next=novi;
		}
		else{
			Nodes* sled=prv->next;
			sled->quant-=novi->quant;

			novi->next=sled;
			prv->next=novi;
		}
	}

}

void SleepList::updateSleepList(PCB* p)
{
	if(head==0)
		return;

	Nodes*prv=0,*tmp=head,*nxt=head->next;

	while(tmp!=0&&tmp->pcb!=p)
	{
		prv=tmp;
		tmp=nxt;
		nxt=nxt->next;
	}

	if(tmp==0)
		return;

	if(prv!=0&&nxt!=0)
	{
		nxt->quant+=tmp->quant;
		prv->next=nxt;
		tmp->next=0;
		delete tmp;
	}
	else if(nxt==0&&prv==0)
	{
		delete tmp;
		head=0;
	}
	else if(nxt==0)
	{
		prv->next=0;
		tmp->next=0;
		delete tmp;
	}
	else if(prv==0)
	{
		if(nxt!=0)
		{
			nxt->quant+=tmp->quant;
			head=nxt;
		}
		else head=0;
		tmp->next=0;
		delete tmp;
	}


}

void SleepList::ispis()
{
	for(Nodes*tmp=head;tmp!=0;tmp=tmp->next)
	{
		LOCK
		cout<<tmp->quant<<endl;
		UNLOCK
	}
}

#/*
 * ListSig.cpp
 *
 *  Created on: Jul 4, 2019
 *      Author: OS1
 */

#include "ListSig.h"

SigHandlerLst::SigHandlerLst() {
	head = prev = 0;
}
void SigHandlerLst::removeAllHandlers() {
	NodeHandler* tmp = 0;

	while (head != 0) {
		tmp = head;
		head = head->next;
		delete tmp;
	}

	head = prev = tmp = 0;
}

void SigHandlerLst::addSignalHandler(SignalHandler sh) {
	NodeHandler* novi = new NodeHandler(sh);
	if (head == 0)
		head = novi;
	else
		prev->next = novi;
	prev = novi;

}

SigHandlerLst::~SigHandlerLst() {
	removeAllHandlers();
}

void SigHandlerLst::callFunctions()
{
	SignalHandler fun=0;
	for(NodeHandler* tmp=head;tmp!=0;tmp=tmp->next)
	{
		fun=tmp->function;
		fun();
	}
	fun=0;
}

void SigHandlerLst::swap(SignalHandler h1,SignalHandler h2)
{
	NodeHandler* handle1=0,*handle2=0;

	if(h1==h2)
		return;
	for(NodeHandler* tmp=head;tmp!=0;tmp=tmp->next)
	{
		if(tmp->function==h1)
			handle1=tmp;
		else if(tmp->function==h2)
			handle2=tmp;
		if(handle1!=0&&handle2!=0)
			break;
	}

	if(handle1==0||handle2==0)
		return;

	handle1->function=h2;
	handle2->function=h1;
}

void SigHandlerLst::inheritSignals(SigHandlerLst* fatherThread)
{
	for(NodeHandler* tmp=fatherThread->head;tmp!=0;tmp=tmp->next)
	{
		this->addSignalHandler(tmp->function);
	}
}

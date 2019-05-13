/*
 * main.cpp
 *
 *  Created on: May 11, 2019
 *      Author: OS1
 */
#include "PCB.h"
#include "Timer.h"
#include "Thread.h"
#include "ListPCB.h"
#define lock asm cli

// Dozvoljava prekide
#define unlock asm sti

int userMain(int argc,char* argv[])
{

	Thread* threads[15];

	int i;
	for(i=0;i<15;i++)
		threads[i]=new Thread(512,i);

	ListPCB* lista=new ListPCB();

	for(i=0;i<15;i++)
		lista->insertBegin(threads[i]->myPCB);

	lista->write();

	return 0;
}
int main(int argc,char* argv[])
{


	//Timer::init_timer();


	int i= userMain(argc,argv);


	//Timer::restore_timer();

	cout<<"Program finished"<<endl;
	return i;
}

/*
 * main.cpp
 *
 *  Created on: May 11, 2019
 *      Author: OS1
 */
#include "PCB.h"
#include "Timer.h"
#include "Thread.h"

#define lock asm cli

// Dozvoljava prekide
#define unlock asm sti

int userMain(int argc,char* argv[])
{

	lock;
	Thread *t1=new Thread(defaultStackSize,3);
	Thread *t2=new Thread(defaultStackSize,5);
	Thread*t3=new Thread(defaultStackSize,10);
	Thread* t4=new Thread(defaultStackSize,9);
	Thread* t5=new Thread(defaultStackSize,1);
	Thread* t6=new Thread();
	Thread* t7=new Thread();
	Thread* t8=new Thread();
	Thread* t9=new Thread();
	t1->start();
	t2->start();
	t3->start();
	t4->start();
	t5->start();
	t6->start();
	t7->start();
	t8->start();
	t9->start();

	volatile PCB* mainPCB=new PCB();
	PCB::running=mainPCB;

	unlock;

	for(int i=0;i<30;i++)
	{
		lockFlag=0;
		cout<<"Main: "<<i<<endl;
		lockFlag=1;
		for(int ik=0;ik<30000;ik++)
			for(int j=0;j<30000;j++);
	}
	return 0;
}
int main(int argc,char* argv[])
{


	Timer::init_timer();


	//printf("SEG:%d, OFF:%d",oldTimerSEG,oldTimerOFF);
	int i= userMain(argc,argv);


	Timer::restore_timer();

	cout<<"Program finished"<<endl;
	return i;
}

#include "kernel.h"
#include <iostream.h>
#include <stdlib.h>
#include <time.h>
/*
 	 Test: Semafori sa spavanjem 4
*/

int t=-1;

const int n=128;

Semaphore s[10];

class TestThread : public Thread
{
private:
	Time waitTime;

public:

	TestThread(Time WT): Thread(), waitTime(WT){}
	~TestThread()
	{
		waitToComplete();
	}
protected:

	void run();

};

void TestThread::run()
{



		for(int i=0;i<10;i++)
			for(int j=0;j<30000;j++)
				for(int kk=0;kk<30000;kk++);

		int idx=(rand()%10);
		int times=(rand()%36)+1; //are going to sleep from 0,055s - 3,00s

		LOCK
		cout<<"Thread: "<<this->getId()<<" Waiting: "<<times<<" on Semaphore: "<<idx<<endl;
		UNLOCK
		int a=s[idx].wait(times);

		if(!a){
			LOCK
			cout<<"Unlocked by timer"<<endl;
			UNLOCK
		}
		else
		{
			LOCK
			cout<<"Unlocked by helpThread"<<endl;
			UNLOCK
		}


}

class HelpThread:public Thread{

public:
	HelpThread():Thread(){};
	~HelpThread(){this->waitToComplete();}

protected:
	void run();
};

int canStop=0;
void HelpThread::run()
{
	while(!canStop)
	{
		for(int i=0;i<10;i++)
		{
			for(int k=0;k<30000;k++)
				for(int e=0;e<30000;e++);
		}

		int idx=(rand()%10);
		int howMany=(rand()%100)+1;


		LOCK
		cout<<"Unlocker will unlock up to: "<<howMany<<" Threads on semaphore: "<<idx<<endl;
		UNLOCK
		s[idx].signal(howMany);
	}

}
void tick()
{
	t++;
}

int userMain(int argc, char** argv)
{
	srand(time(0));

	syncPrintf("Test starts.\n");
	TestThread* t[n];
	HelpThread thr;
	int i;
	LOCK
	for(i=0;i<n;i++)
	{
		t[i] = new TestThread(5*(i+1));
		t[i]->start();
	}
	thr.start();
	UNLOCK
	for(i=0;i<n;i++)
	{
		t[i]->waitToComplete();
		delete t[i];
	}
	canStop=1;
	delete t;

	syncPrintf("Test ends.\n");
	return 0;
}



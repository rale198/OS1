#include "kernel.h"

/*
	Test: Niti maxStack velicine
*/

const int n = 2;
class TestThread : public Thread
{
public:

	TestThread(): Thread(32768,2) {};
	~TestThread()
	{
		waitToComplete();
	}
protected:

	void run();

};

void TestThread::run()
{

	int buffer=2;

	for(int i=0;i<32000;i++)
	{
		buffer = 4096/2048;
		for (int j = 0; j < 1024; j++)
		{
			buffer = buffer*2;
			if(buffer%2)
				buffer = 2;

			if(buffer)
			{
				LOCK
				cout<<buffer<<endl;
				UNLOCK
			}
		}
	}

}





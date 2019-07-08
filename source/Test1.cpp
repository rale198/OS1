#include "kernel.h"

/*
 Test: cekanje niti
 */

#define PREPAREFUNC(NUM) void fun##NUM(){printf("function: %d called by Thread: %d\n\n",NUM,PCB::running->myThread->getId());}

class TestThread: public Thread {
public:

	TestThread() :
			Thread() {
	}
	;
	~TestThread() {
		waitToComplete();
	}
protected:

	void run();

};

int flag = 0;
void TestThread::run() {

	while(!flag){
		LOCK
		cout << "Thread " << this->getId() << endl;
		UNLOCK

			for (int j = 0; j < 10000; j++)
				for (int k = 0; k < 30000; k++)
					;
	}
}


int cnt = 0;
Semaphore s(0);
int flagPass = 0;
class WaitThread: public Thread {
private:
	TestThread *t1_, *t2_, *t3_;

public:
	WaitThread(TestThread *t1, TestThread *t2, TestThread* t3) :
			Thread() {
		t1_ = t1;
		t2_ = t2;
		t3_ = t3;
		this->stop = 0;
	}
	;

	~WaitThread() {
		waitToComplete();
	}

protected:

	int stop;
	void run() {

		/*
		 LOCK
		 for(int im=0;im<10;im++)
		 threads[im].start();
		 UNLOCK
		 for(int i=0;i<10;i++)
		 {
		 s.wait(0);

		 LOCK
		 cout<<"Killing thread: "<<i+1<<endl;
		 threads[i].signal(0);
		 UNLOCK
		 }*/

		LOCK
		cout << "Let's kill some thread" << endl;
		UNLOCK
		s.wait(0);

		t1_->signal(0);

		LOCK
		cout << "Thread1 kill yourself" << endl;
		UNLOCK

		s.wait(0);

		t2_->signal(0);
		LOCK
		cout << "Thread2 kill yourself" << endl;
		UNLOCK

		s.wait(0);

		t3_->signal(0);

		LOCK
		cout << "Thread3 kill yourself" << endl;
		UNLOCK


		LOCK
		cout << "All threads have been killed" <<flush<< endl;
		UNLOCK
	}
};
/*
void tick() {
	LOCK
	cnt++;
	if (cnt % 45 == 0)
		s.signal();

	UNLOCK
}

int userMain(int argc, char** argv) {

	syncPrintf("User main starts\n");
	LOCK
	TestThread t1, t2, t3;
	WaitThread w(&t1, &t2, &t3);
	w.start();
	t1.start();
	t2.start();
	t3.start();
	UNLOCK


	syncPrintf("User main ends\n");
	return 0;
}
*/

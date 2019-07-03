/*
 * Event.h
 *
 *  Created on: Jul 2, 2019
 *      Author: OS1
 */

#ifndef HEADERS_EVENT_H_
#define HEADERS_EVENT_H_

typedef unsigned char IVTNo;
class KernelEv;

#define PREPAREENTRY(No,flag)\
void interrupt intr##No(...);\
IVTEntry ivte##No(No,intr##No);\
void interrupt intr##No(...){\
	ivte##No.signal();\
	if(flag==1){\
		ivte##No.callOldRoutine();\
	}\
}


class Event {
public:
	Event(IVTNo ivtNo);
	~Event();
	void wait();
protected:
	friend class KernelEv;
	void signal(); // can call KernelEv
private:
	KernelEv* myImpl;
};

#endif /* HEADERS_EVENT_H_ */

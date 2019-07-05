/*
 * ListSig.h
 *
 *  Created on: Jul 4, 2019
 *      Author: OS1
 */

#ifndef HEADERS_LISTSIG_H_
#define HEADERS_LISTSIG_H_
#include "PCB.h"
class SigHandlerLst{

public:

	struct NodeHandler{
		SignalHandler function;
		NodeHandler* next;

		NodeHandler(SignalHandler hndl)
		{
			next=0;
			function=hndl;
		}
	};

	SigHandlerLst();
	~SigHandlerLst();
	void addSignalHandler(SignalHandler sh);
	void removeAllHandlers();
	void callFunctions();
	void swap(SignalHandler handl1,SignalHandler handl2);
	void inheritSignals(SigHandlerLst*);
private:
	NodeHandler* head,*prev;
};



#endif /* HEADERS_LISTSIG_H_ */

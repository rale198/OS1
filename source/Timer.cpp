/*
 * Timer.cpp
 *
 *  Created on: May 12, 2019
 *      Author: OS1
 */
#include "Timer.h"
#include "PCB.h"

unsigned oldTimerOFF = 0;
unsigned oldTimerSEG = 0;

void killThread() {
	PCB::running->killFlag=1;
}
void callParent() {}
void callMySelf() {LOCK cout<<"You've called yourself"<<endl;UNLOCK}
void Timer::init_timer() {
#ifndef BCC_BLOCK_IGNORE
	asm {
		cli
		push es
		push ax

		mov ax,0   //  ; inicijalizuje rutinu za tajmer
		mov es,ax

		mov ax, word ptr es:0022h//; pamti staru rutinu
		mov word ptr oldTimerSEG, ax
		mov ax, word ptr es:0020h
		mov word ptr oldTimerOFF, ax

		mov word ptr es:0022h, seg timer//postavlja
		mov word ptr es:0020h, offset timer//novu rutinu

		mov ax, oldTimerSEG//	postavlja staru rutinu
		mov word ptr es:0182h, ax//; na int 60h
		mov ax, oldTimerOFF
		mov word ptr es:0180h, ax

		pop ax
		pop es
		sti
	}
#endif

}
;

void Timer::restore_timer() {
#ifndef BCC_BLOCK_IGNORE
	asm {
		cli
		push es
		push ax

		mov ax,0
		mov es,ax

		mov ax, word ptr oldTimerSEG
		mov word ptr es:0022h, ax
		mov ax, word ptr oldTimerOFF
		mov word ptr es:0020h, ax

		pop ax
		pop es
		sti
	}
#endif
}

void Timer::init_handlers() {
	LOCK
	((PCB*) PCB::running)->allSignals[0]->addSignalHandler(killThread);
	((PCB*) PCB::running)->allSignals[1]->addSignalHandler(callParent);
	((PCB*) PCB::running)->allSignals[2]->addSignalHandler(callMySelf);
	UNLOCK
}

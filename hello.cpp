#include <iostream.h>
#include <dos.h>
#include <stdio.h>
typedef void interrupt (*pInterrupt)(...);

volatile int cntr=0;
pInterrupt oldISR,keyboardISR;

void inic()
{
	asm cli;
	oldISR=getvect(9);
	setvect(9,keyboardISR);
	asm sti;
}

void restore()
{
	asm cli;
	setvect(9,oldISR);
	asm sti;
}

void doSomething()
{
	for(int i=0;i<10;i++) {

		printf("main %d\n",i);

		for(int j=0;j<30000;++j)
			for(int k=0;k<30000;k++);
	}

	printf("Tastatura je generisala dogadjaj!\n",cntr);
}
int main(){

	inic();

	doSomething();

	restore();

	return 0;
}



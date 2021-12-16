#include "dos.h"
#include "conio.h"

void interrupt(*oldInt)(...);

void interrupt myInt(...) {
	union REGS reg;
	reg.h.ah = 0;

	oldInt();   //call the old interruption handler to read key and save it's code

	switch (int86(0x16, &reg, &reg)) {    //call another interruption to check saved keycode
	case 0x3B00: //F1 (two-byte code everywhere)
		putch('A');
		break;
	case 0x3C00: //F2
		putch(0xE08);  //backspace
		putch(' ');
		putch(0xE08);  //backspace	
	}


}


int main()
{
	oldInt = getvect(0x09); //save the address of original keyboard interruption handler
	setvect(0x09, myInt);   //assign our function to keyboard interruption handler

	while (1);

	return 0;
}
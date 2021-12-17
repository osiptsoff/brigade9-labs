#include "dos.h"
#include "conio.h"

void interrupt(*oldInt)(...);

const leftX = 10;
const upY = 10;
const rightX = 70;
const downY = 20;

int keyCode = 0;

void interrupt myInt(...) {

	keyCode = inportb(0x60); //check key
	switch (keyCode) {
	case 59: //F1 down
		putch('A');
		break;
	case 60: //F2 down
		if (wherex() != 1) {
			putch('\b');
			putch(' ');
			putch('\b');
		}
		else if (wherey() != 1) {
			gotoxy(rightX - leftX + 1, wherey() - 1);
			putch(' ');
			gotoxy(rightX - leftX + 1, wherey() - 1);
		}

	}

	oldInt();   //call the old interruption handler
}


int main()
{
	oldInt = getvect(0x09); //save the address of original keyboard interruption handler
	setvect(0x09, myInt);   //assign our function to keyboard interruption handler

	window(leftX, upY, rightX, downY);
	textattr(0x70);
	clrscr();

	while (keyCode != 1); // while ESC is not pressed

	return 0;
}
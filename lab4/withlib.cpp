#include "dos.h"
#include "conio.h"

int main()
{
	const leftX = 10;
	const upY = 10;
	const rightX = 70;
	const downY = 20;

	window(leftX, upY, rightX, downY);
	textattr(0x70);
	clrscr();

	int x = 1, y = (downY - upY) / 2, symbol = 0;
	int left = 0;

	do
	{
		clrscr();
		if (left == 1)
			x = (x < 2) ? rightX - leftX : x - 1;
		if (left == 0)
			x = (x > rightX - leftX) ? 1 : x + 1;

		gotoxy(x, y);
		putch('*');
		delay(100);

		if (kbhit())
			do
				symbol = getch();
			while (kbhit());

		switch (symbol)
		{
		case 75: //left
			left = 1;
			break;
		case 77: //right
			left = 0;
			break;
		}

	} while (symbol != 27);

	return 0;
}
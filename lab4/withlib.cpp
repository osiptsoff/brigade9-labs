#include "dos.h"
#include "conio.h"


int main()
{
	const leftX = 10;
	const upY = 10;
	const rightX = 70;
	const downY = 20;

	window(leftX, upY, rightX, downY);
	clrscr();

	int x = 1, y = 1, symbol = 0;
	int left = 0;

	do
	{
		clrscr();
		if (left == 1)
			if (x < 2) {
				if (y > 1) {
					x = rightX - leftX;
					y -= 1;
				}
			}
			else
				x -= 1;

		if (left == 0)
			if (x > rightX - leftX) {
				if (y < downY - upY) {
					x = 1;
					y += 1;
				}
			}
			else
				x += 1;

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

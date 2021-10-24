#include <conio.h>
#include <dos.h>

void scroll(int direction, int step, int l_row, int l_col, int r_row, int r_col, int attr)
{
	union REGS r;
	r.h.ah = 6 + direction;
	r.h.al = step;
	r.h.ch = l_row; r.h.cl = l_col; r.h.dh = r_row; r.h.dl = r_col;
	r.h.bh = attr;
	int86(0x10, &r, &r);
}


int main()
{
	const int upLeftX = 10;
	const int upLeftY = 10;
	const int downRightX = 70;
	const int downRightY = 20;
	const int stringStep = 3;
	const int maxPhraseLen = 21;
	const int timeStep = 1300;
	const char* colNames[] = { "BLACK", "BLUE", "GREEN", "CYAN", "RED", "MAGENTA", "BROWN", "LIGHTGRAY", "DARKGRAY", "LIGHTBLUE", "LIGHTGREEN", "LIGHTCYAN", "LIGHTRED", "LIGHTMAGENTA", "YELLOW", "WHITE" };
	enum DIRECTIONS { DOWN, UP };

	char* phrase = (char*)&maxPhraseLen;
	cprintf("Enter the output string(max %d symbols): ", maxPhraseLen - 1);
	cgets(phrase);
	phrase = phrase + 2;

	window(upLeftX, upLeftY, downRightX, downRightY);
	textattr(0x70);
	clrscr();

	gotoxy(1, downRightY - upLeftY + 1);
	for (int bgColor = BLACK; bgColor <= LIGHTGRAY; bgColor++)
		for (int txtColor = BLACK; txtColor <= WHITE; txtColor++)
		{
			textcolor(txtColor);
			textbackground(bgColor);
			cprintf(phrase);

			textcolor(BLACK);
			textbackground(LIGHTGRAY);
			cprintf("   Background: %-12s Text: %2d", colNames[bgColor], txtColor);
			delay(timeStep);

			gotoxy(1, wherey());
			if (wherey() < stringStep)
				scroll(UP, stringStep, upLeftY - 1, upLeftX - 1, downRightY - 1, downRightX - 1, 0x70);
			gotoxy(1, wherey() - stringStep);
		}
	getch();
	return 0;
}
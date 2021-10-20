#include <conio.h>
#include <dos.h>

void scrool(int step) {
	for (int i = wherey() - 1; i < step + 1; i++) insline();
	gotoxy(1, wherey());
}

int main()
{
	const int upLeftX = 10;
	const int upLeftY = 10;
	const int downRightX = 70;
	const int downRightY = 20;
	const int stringStep = 3;
	const int maxPhraseLen = 26;
	const float timeStep = 1.3;
	const char* colNames[] = { "BLACK", "BLUE", "GREEN", "CYAN", "RED", "MAGENTA", "BROWN", "LIGHTGRAY", "DARKGRAY", "LIGHTBLUE", "LIGHTGREEN", "LIGHTCYAN", "LIGHTRED", "LIGHTMAGENTA", "YELLOW", "WHITE" };

	char* phrase = (char*)&maxPhraseLen;
	cprintf("Enter the output string(max %d symbols): ", maxPhraseLen - 1);
	cgets(phrase);
	phrase = phrase + 2;

	window(upLeftX, upLeftY, downRightX, downRightY);
	textattr(0x70);
	clrscr();

	gotoxy(1, downRightY - upLeftY + 1);
	for (int txtColor = BLACK; txtColor <= WHITE; txtColor++)
		for (int bgColor = BLACK; bgColor <= WHITE; bgColor++)
		{
			textcolor(txtColor);
			textbackground(bgColor);
			cprintf(phrase);

			textcolor(BLACK);
			textbackground(LIGHTGRAY);
			cprintf("    %s    %d", colNames[bgColor], txtColor);
			delay((int)(1000 * timeStep));
			gotoxy(1, wherey());

			scrool(stringStep);

			gotoxy(1, wherey() - stringStep);
			//delay((int)(1000 * timeStep));
		}

	return 0;
}
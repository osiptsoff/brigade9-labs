#include <conio.h>

int main()
{
	const int upLeftX = 10;
	const int upLeftY = 10;
	const int downRightX = 70;
	const int downRightY = 20;
	const int stringStep = 3;
	const float timeStep = 1.4;


	window(upLeftX, upLeftY, downRightX, downRightY);
	for (int i = 0; i < 5 * stringStep; i += stringStep)
	{
		gotoxy(10 - i, 10 - i);
		cprintf("%d", wherex());
	}

	return 0;
}
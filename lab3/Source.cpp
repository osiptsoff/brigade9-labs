#include <dos.h>
#include <graphics.h>

int main()
{
	int driver, mode, errorCode;
	char path[] = "C:\\TURBOC3\\BGI";

	driver = DETECT;
	detectgraph(&driver, &mode);
	initgraph(&driver, &mode, path);

	errorCode = graphresult();
	if (errorCode != grOk)
		return 255;

	moveto(0, 0);
	lineto(50, 50);
	delay(5000);
	closegraph();
	return 0;
}

#include <dos.h>
#include <graphics.h>
#include <math.h>
#include <string.h>

void Axes(int distanceX, int distanceY) {
	line(0, getmaxy() / 2, getmaxx(), getmaxy() / 2);
	line(distanceX, 0, distanceX, getmaxy());

	for (int i = distanceX * 2, j = 1; i < getmaxx() - distanceX; i += distanceX, j++) {
		line(i, getmaxy() / 2 + 3, i, getmaxy() / 2 - 3);
		if (j % 2 == 0) {
			char s[] = " pi";
			s[0] = '0' + j / 2;
			outtextxy(i - 10, getmaxy() / 2 + 15, s);
		}
		else {
			char s[] = " pi/2";
			s[0] = '0' + j;
			outtextxy(i - 15, getmaxy() / 2 + 15, s);
		}

	}

	line(distanceX - 3, getmaxy() / 2 + distanceY, distanceX + 3, getmaxy() / 2 + distanceY);
	line(distanceX - 3, getmaxy() / 2 - distanceY, distanceX + 3, getmaxy() / 2 - distanceY);

	char s[] = "-1";
	outtextxy(distanceX - 20, getmaxy() / 2 + distanceY, s);

	s[0] = ' ';
	outtextxy(distanceX - 20, getmaxy() / 2 - distanceY, s);

	s[1] = '0';
	outtextxy(distanceX - 20, getmaxy() / 2 + 15, s);
}

void Plot(int start, int finish, double& max) {
	setcolor(4);

	double k = double(start) / (3.14 / 2);
	double valueX = start * 2 / k;
	double valueY = pow(sin(valueX), 2) + pow(cos(valueX), 3);
	int positionY = valueY * k;
	moveto(start * 2, getmaxy() / 2 + positionY);

	for (int i = start * 2 + 1; i <= finish + start; i++) {
		if (valueY > max) {
			max = valueY;
		}

		valueX = i / k;
		valueY = pow(sin(valueX), 2) + pow(cos(valueX), 3);
		positionY = valueY * k;
		lineto(i, getmaxy() / 2 + positionY);
	}

	if (valueY > max) {
		max = valueY;
	}

	setcolor(15);
}

void Print(int x, int y, double max) {
	moveto(x, y);
	char s[] = "y = sin^2(x) + cos^3(x), x: (pi/2; 5pi). Max y =  ";
	s[strlen(s) - 1] = '0' + int(max + 0.5);
	outtext(s);
}


int main()
{
	int driver, mode, errorCode;
	char path[] = "C:\\TURBOC3\\BGI";

	driver = DETECT;
	detectgraph(&driver, &mode);

	initgraph(&driver, &mode, "C:\\TURBOC3\\BGI");
	errorCode = graphresult();
	if (errorCode != grOk)
		return 255;

	const int halfPi = getmaxx() / 12;
	const int one = halfPi / (3.14 / 2);

	Axes(halfPi, one);

	double max = -1000000;
	Plot(halfPi, (halfPi * 2) * 5, max);

	Print(halfPi * 2, getmaxy() / 2 - one - 30, max);

	delay(5000);
	closegraph();
	return 0;
}

#include <conio.h>
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
	line(distanceX - 3, getmaxy() / 2 + distanceY / 2, distanceX + 3, getmaxy() / 2 + distanceY / 2);
	line(distanceX - 3, getmaxy() / 2 - distanceY / 2, distanceX + 3, getmaxy() / 2 - distanceY / 2);
	line(distanceX - 3, getmaxy() / 2 - distanceY, distanceX + 3, getmaxy() / 2 - distanceY);

	char s[5] = "-1";
	outtextxy(distanceX - 35, getmaxy() / 2 + distanceY, s);

	strcpy(s, "-0.5");
	outtextxy(distanceX - 35, getmaxy() / 2 + distanceY / 2, s);

	strcpy(s, "0.5");
	outtextxy(distanceX - 27, getmaxy() / 2 - distanceY / 2, s);

	strcpy(s, "1");
	outtextxy(distanceX - 27, getmaxy() / 2 - distanceY, s);
}

void Plot(int start, int finish, double& max) {
	setcolor(4);

	double k = double(start) / (M_PI / 2);
	double valueX = start / k;
	double valueY = pow(sin(valueX), 2) + pow(cos(valueX), 3);
	int positionY = valueY * k;
	moveto(start * 2, getmaxy() / 2 - positionY);

	for (int i = start + 1; i <= finish; i++) {
		if (valueY > max) {
			max = valueY;
		}

		valueX = i / k;
		valueY = pow(sin(valueX), 2) + pow(cos(valueX), 3);
		positionY = valueY * k;
		lineto(i + start, getmaxy() / 2 - positionY);
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
	int driver = DETECT, mode, errorCode;

	initgraph(&driver, &mode, "C:\\TURBOC3\\BGI");
	errorCode = graphresult();
	if (errorCode != grOk)
		return 255;

	const int halfPi = getmaxx() / 12;
	const int one = halfPi / (M_PI / 2);

	Axes(halfPi, one);

	double max = -1000000;
	Plot(halfPi, (halfPi * 2) * 5, max);

	Print(halfPi * 2, getmaxy() / 2 - one - 30, max);

	getch();
	closegraph();
	return 0;
}

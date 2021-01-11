#include "Circle.h"

Circle::Circle(const int& x, const int& y, const int& r): xValue{x}, yValue{y}, radius{r}
{
	if (r == 0) throw std::runtime_error{ "Circle(), radius entered is 0, this is not a circle" };
}

bool Circle::checkValid() const
{
	if(xValue > wide || xValue < 0) return false;
	else if(yValue > high || yValue < 0) return false;
	else if(xValue + radius > wide || xValue - radius < 0) return false;
	else if (yValue + radius > high || yValue - radius < 0) return false;
	return true;
}

void Circle::draw(Frame* frame) const
{
	int d{ 3 - (2 * radius) };
	int x{ 0 };
	int y{ radius };

	drawPoints(x, y, frame); // draw innitial points

	while (x <= y)
	{
		x++;

		if (d <= 0) { d += (4 * x) + (6 * radius); }
		else {
			y--;
			d += 4 * (x - y) + 10;
		}
		
		drawPoints(x, y, frame);
	}




}

void Circle::drawPoints(int x, int y, Frame* frame) const
{
	frame->put_point(yValue + y, xValue + x); 
	frame->put_point(yValue + y, xValue - x);
	frame->put_point(yValue - y, xValue + x);
	frame->put_point(yValue - y, xValue -x);

	frame->put_point(yValue + x, xValue + y);
	frame->put_point(yValue + x, xValue - y);
	frame->put_point(yValue - x, xValue + y);
	frame->put_point(yValue - x, xValue - y);
}

void Circle::move(int h, int v)
{
	xValue += v;
	yValue += h;
}

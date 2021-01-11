#include "Line.h"
#include "Frame.h"
#include <iostream>


// Skizze Konstuktordefinition
Line::Line(const int& startX, const int& startY, const int& endX, const int& endY) : start_x{ startX }, start_y{ startY }, end_x{ endX }, end_y{ endY }
{ 
	if (!checkValid()) throw std::runtime_error{ "Line not within frame borders at Line::checkValid()" };
}

void Line::set(const int& startX, const int& startY, const int& endX, const int& endY)
{
	start_x = startX;
	start_y = startY;
	end_x = endX;
	end_y = endY;
}

bool Line::checkValid() const
{
	if (start_x > wide || end_x > wide || start_x < 0 || end_x < 0) return false;
	else if (start_y > high || end_y > high || start_y < 0 || end_y < 0) return false;
	return true;
}

void Line::move(int h, int v)
{ // Def. der line::move() Methode
	start_x += h;
	start_y += v;
	end_x += h;
	end_y += v;
}


void Line::draw(Frame* frame) const
{ // rein virtuelles shape::draw() ueberschreiben

	if (start_x >= wide || end_x >= wide ||	start_y >= high || end_y >= high)
	{
		throw std::runtime_error{ "cannot draw line at Shape::Line::draw() because the limits of the line are outside of the frame boundaries." };
	}

	frame->put_point(start_y, start_x); //place start and end points
	frame->put_point(end_y, end_x);

	int distance_x{ abs(end_x - start_x) };
	int distance_y{ abs(end_y - start_y) };
	
	int longestDistance{};				//save longest distance and shortest distance
	int shortestDistance{};
	if (distance_x > distance_y) {
		longestDistance = distance_x; 
		shortestDistance = distance_y;
	}
	else {
		longestDistance = distance_y;
		shortestDistance = distance_x;
	}

	bool xIsLongest{};					//save which distance (x or y-axis distance) is longest
	if (distance_x == longestDistance) xIsLongest = true;
	else xIsLongest = false;

	bool xDirectionPositive{false};		//true if points are in sorted ascending order
	if ((end_x - start_x) >= 0) xDirectionPositive = true;

	bool yDirectionPositive{false};
	if ((end_y - start_y) >= 0) yDirectionPositive = true;

	if (longestDistance == 0) return; //method ends because the line is a dot.

	double error{ longestDistance / 2.0 };
	int x{ start_x }, y{ start_y };

	while (x < end_x || y < end_y)
	{
		if (xIsLongest && xDirectionPositive) x += 1;
		else if (xIsLongest && !xDirectionPositive) x -= 1;
		else if (!xIsLongest && yDirectionPositive) y += 1;
		else if (!xIsLongest && !yDirectionPositive) y -= 1;

		error -= shortestDistance;

		if (error < 0 && xIsLongest && yDirectionPositive) y += 1;
		else if (error < 0 && xIsLongest && !yDirectionPositive) y -= 1;
		else if (error < 0 && !xIsLongest && xDirectionPositive) x += 1;
		else if (error < 0 && !xIsLongest && !xDirectionPositive) x -= 1;

		if (error < 0) error += longestDistance;

		frame->put_point(y, x);

	}

}



void lineTests()
{
	//test #1
	Frame frameActual{};
	Frame* frameActualPointer{ &frameActual };
	Line line{ 0,0,5,5 };
	line.draw(frameActualPointer);

	Frame frameExpected{};
	Frame* frameExpectedPointer{ &frameExpected };
	frameExpected.put_point(0, 0);
	frameExpected.put_point(1, 1);
	frameExpected.put_point(2, 2);
	frameExpected.put_point(3, 3);
	frameExpected.put_point(4, 4);
	frameExpected.put_point(5, 5);

	line.assertFrame(1, frameActualPointer, frameExpectedPointer);

	//test #2
	Frame frameActual2{};
	Frame* frameActualPointer2{ &frameActual2 };
	Line line2{ 0,0,13,10 };
	line2.draw(frameActualPointer2);

	Frame frameExpected2{};
	Frame* frameExpectedPointer2{ &frameExpected2 };
	frameExpected2.put_point(0, 0);
	frameExpected2.put_point(1, 1);
	frameExpected2.put_point(2, 2);
	frameExpected2.put_point(2, 3);
	frameExpected2.put_point(3, 4);
	frameExpected2.put_point(4, 5);
	frameExpected2.put_point(5, 6);
	frameExpected2.put_point(5, 7);
	frameExpected2.put_point(6, 8);
	frameExpected2.put_point(7, 9);
	frameExpected2.put_point(8, 10);
	frameExpected2.put_point(8, 11);
	frameExpected2.put_point(9, 12);
	frameExpected2.put_point(10, 13);

	line2.assertFrame(2, frameActualPointer2, frameExpectedPointer2);


	//test #3
	Frame frameActual3{};
	Frame* frameActualPointer3{ &frameActual3 };
	Line line3{ 0,0,0,0 };
	line3.draw(frameActualPointer3);

	Frame frameExpected3{};
	Frame* frameExpectedPointer3{ &frameExpected3 };
	frameExpected3.put_point(0, 0);

	line3.assertFrame(3, frameActualPointer3, frameExpectedPointer3);
}

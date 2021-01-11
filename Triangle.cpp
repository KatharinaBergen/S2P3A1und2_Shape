#include "Triangle.h"
#include "Line.h"
#include <iostream>
#include <vector>

Triangle::Triangle(const int& xValueA, const int& yValueA, const int& xValueB, const int& yValueB, const int& xValueC, const int& yValueC)
	: xValue_A{ xValueA }, yValue_A{ yValueA }, xValue_B{ xValueB }, yValue_B{ yValueB }, xValue_C{ xValueC }, yValue_C{ yValueC }
{
	if (!checkValid()) throw std::runtime_error{ "Triangle not within frame borders at Triangle::checkValid()" };
}

Triangle::Triangle(const int& xValueA, const int& yValueA, const int& len1, const int& len2, const int& len3)
	: xValue_A{ xValueA }, yValue_A{ yValueA }, xValue_B{ }, yValue_B{ }, xValue_C{ }, yValue_C{ }
{
	std::vector<int> lengthSorted{ Triangle::sortByLength(len1, len2, len3) };
	setClassVariables(lengthSorted);
	
	if (!checkValid()) throw std::runtime_error{ "Triangle not within frame borders at Triangle::checkValid()" };
}

std::vector<int> Triangle::sortByLength(const int& len1, const int& len2, const int& len3)
{
	std::vector<int> lengthSorted{ len1, len2, len3 };
	int i{};
	while (!(lengthSorted.at(0) <= lengthSorted.at(1) && lengthSorted.at(1) <= lengthSorted.at(2))) {
		if (lengthSorted[i + 1] < lengthSorted[i]) {
			int interim{ lengthSorted[i] };
			lengthSorted[i] = lengthSorted[i + 1];
			lengthSorted[i + 1] = interim;
		}
		i++;

		if (i > 1) i = 0;
	}
	return lengthSorted;
}

void Triangle::setClassVariables(const std::vector<int>& lengthSorted)
{
	int xDistanceToFrameBorder{ abs(wide - xValue_A) };
	int i{ 2 };
	while (lengthSorted.at(i) > xDistanceToFrameBorder) i--;

	if (xValue_A + lengthSorted.at(i) < wide) xValue_B = xValue_A + lengthSorted.at(i);
	else if (xValue_A + lengthSorted.at(i) > wide) xValue_B = xValue_A - lengthSorted.at(i);

	yValue_B = yValue_A;

	setPointZ(lengthSorted);
}

void Triangle::setPointZ(const std::vector<int>& lengthSorted)
{
	int lengthZ{ (squared(lengthSorted.at(2)) - squared(lengthSorted.at(1)) + squared(lengthSorted.at(0))) / (2 * lengthSorted.at(2)) };
	double height{ sqrt(squared(lengthSorted.at(2) - squared(lengthZ))) };

	xValue_C = xValue_A + lengthZ;
	yValue_C = yValue_A + height;
}

bool Triangle::checkValid() const
{
	if (xValue_A > wide || xValue_B > wide || xValue_C > wide) return false;
	else if (xValue_A < 0 || xValue_B < 0 || xValue_C < 0) return false;
	else if (yValue_A > high || yValue_B > high || yValue_C > high) return false;
	else if (yValue_A < 0 || yValue_B < 0 || yValue_C < 0) return false;
	return true;
}

void Triangle::draw(Frame* frame) const
{
	if (xValue_A >= wide || xValue_B >= wide || xValue_C >= wide || yValue_A >= high || yValue_B >= high || yValue_C >= high)
	{
		throw std::runtime_error{ "cannot draw triangle at Shape::Triangle::draw() because the limits of the triangle are outside of the frame boundaries." };
	}

	Line a_to_b{ xValue_A, yValue_A, xValue_B, yValue_B };
	Line a_to_c{ xValue_A, yValue_A, xValue_C, yValue_C };
	Line b_to_c{ xValue_B, yValue_B, xValue_C, yValue_C };

	frame->put_point(yValue_A, xValue_A);
	frame->put_point(yValue_B, xValue_B);
	frame->put_point(yValue_C, xValue_C);

	a_to_b.draw(frame);
	a_to_c.draw(frame);
	b_to_c.draw(frame);
}

void Triangle::move(int h, int v)
{
	xValue_A += h;
	yValue_A += v;
	xValue_B += h;
	yValue_B += v;
	xValue_C += h;
	yValue_C += v;
}


int squared(int length)
{
	return length * length;
}

void triangleTests()
{
	//test #1
	Frame frameActual{};
	Frame* frameActualPointer{ &frameActual };
	Triangle triangle{ 2,2,10,12,18,5 };
	triangle.draw(frameActualPointer);

	Frame frameExpected{};
	Frame* frameExpectedPointer{ &frameExpected };

	frameExpected.put_point(2, 2);
	frameExpected.put_point(12, 10);
	frameExpected.put_point(5, 18);

	Line LineA{ 2,2,10,12 };
	Line LineB{ 2,2,18,5 };
	Line LineC{ 10,12,18,5 };

	LineA.draw(frameExpectedPointer);
	LineB.draw(frameExpectedPointer);
	LineC.draw(frameExpectedPointer);

	triangle.assertFrame(1, frameExpectedPointer, frameActualPointer);

	//test #2
	Frame frameActual2{};
	Frame* frameActualPointer2{ &frameActual2 };
	Triangle triangle2{ 2,2,8,15,20 };
	triangle2.draw(frameActualPointer2);

	Frame frameExpected2{};
	Frame* frameExpectedPointer2{ &frameExpected2 };

	frameExpected2.put_point(2, 2);
	frameExpected2.put_point(2,22);
	frameExpected2.put_point(7, 7);

	Line LineA2{ 2,2,22,2 };
	Line LineB2{ 2,2,7,7 };
	Line LineC2{ 22,2,7,7 };

	LineA2.draw(frameExpectedPointer2);
	LineB2.draw(frameExpectedPointer2);
	LineC2.draw(frameExpectedPointer2);

	triangle2.assertFrame(2, frameExpectedPointer2, frameActualPointer2);

	// Triangle triangle3{ 2,2,10,12,50,50 }; //wirfst wie erwartet und gewünscht einen Fehler.
	
}
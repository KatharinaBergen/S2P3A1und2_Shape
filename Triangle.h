#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <vector>

#include "Shape.h"

class Triangle : public Shape {
public:
	Triangle() = delete; // keine Standardlinie
	Triangle(const int&, const int&, const int&, const int&, const int&, const int&); // ein Konstruktor
	Triangle(const int& , const int& yValueA, const int& len1, const int& len2, const int& len3);
	std::vector<int> sortByLength(const int& len1, const int& len2, const int& len3);
	void setClassVariables(const std::vector<int>&);
	void setPointZ(const std::vector<int>& lengthSorted);
	bool checkValid() const;
	void draw(Frame*) const; // rein virtuelles shape::draw() ueberschreiben
	void move(int h, int v); // rein virtuelles shape::move() ueberschreiben


private:
	int xValue_A, yValue_A, xValue_B, yValue_B, xValue_C, yValue_C;
};

int squared(int length);
void triangleTests();

#endif // !TRIANGLE_H

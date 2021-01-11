#ifndef CIRCLE_H
#define CIRCLE_H


#include "Shape.h"

class Circle : public Shape {
public:
	Circle() = delete; // keine Standardlinie
	Circle(const int&, const int&, const int&); // ein Konstruktor
	bool checkValid() const;
	void draw(Frame*) const; // rein virtuelles shape::draw() ueberschreiben
	void drawPoints(int x, int y, Frame* frame) const;
	void move(int h, int v); // rein virtuelles shape::move() ueberschreiben

private:
	int xValue, yValue, radius;
};


#endif // !CIRCLE_H

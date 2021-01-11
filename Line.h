#ifndef LINE_H
#define LINE_H

#include "Shape.h"

class Line : public Shape {
public:
	Line() = delete; // keine Standardlinie
	Line(const int&, const int&, const int&, const int&); // ein Konstruktor
	void set(const int&, const int&, const int&, const int&);
	bool checkValid() const;
	void draw(Frame*) const; // rein virtuelles shape::draw() ueberschreiben
	void move(int h, int v); // rein virtuelles shape::move() ueberschreiben

private:
	int start_x, start_y, end_x, end_y;
};

void lineTests();

#endif // !LINE_H

#ifndef SHAPE_H
#define SHAPE_H

#include "Frame.h"

class Shape {
public:
	Shape() : prev{ last } { last = this; } // Skizze Standardkonstruktor
	virtual bool checkValid() const = 0; // rein virtuelle Methode
	virtual void draw(Frame* ptarget) const = 0; // rein virtuelle Methode
	virtual void move(int hor, int ver) = 0; // rein virtuelle Methode

	void assertFrame(int testnumber, Frame* expected, Frame* actual); //ADDED METHOD TESTING PURPOSES
	void assertBool(const int& testnumber, const bool& expected, const bool& actual);
	
private:
	 static Shape* last; // Zeiger auf die zuletzt erzeugte Figur (d.h. Listenanfang)
	 Shape* prev; // Zeiger auf die zuvor erzeugte Figur
};

void show_all_shapes(Frame* frame);


#endif // !SHAPE_H


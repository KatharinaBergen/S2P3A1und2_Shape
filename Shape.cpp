#include "Shape.h"
#include <iostream>

Shape* Shape::last{ nullptr }; // initialisiert den static Member mit dem Nullzeiger
void show_all_shapes(Frame*); // gibt alle Shape Objekte auf Frame* aus
void Shape::assertFrame(int testnumber, Frame* expected, Frame* actual)
{
	std::cout << "\nTest number " << testnumber << " has ";
	if (expected->test(actual)) std::cout << "passed. ";
	else std::cout << "failed. ";

	if (!(expected->test(actual)))
	{
		for (int i{ high - 1 }; i >= 0; --i)
		{
			for (int j{}; j < wide; ++j)
			{
				if (expected->on_frame(i, j) != actual->on_frame(i, j))
					std::cout << std::endl << i << ", " << j << " is not both on expected and on actual frame.";
			}
		}
	}
}

void Shape::assertBool(const int& testnumber, const bool& expected, const bool& actual)
{
	std::cout << "\nTest number " << testnumber << " has ";
	if (expected == actual) std::cout << "passed. ";
	else std::cout << "failed. ";
}

void show_all_shapes(Frame* frame)
{
	frame->show();
}

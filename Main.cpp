#include <exception>
#include <iostream>
#include "Line.h"
#include "Triangle.h"
#include "Circle.h"

int main() try
{
	std::cout << "\n-------------Line Tests--------------------\n";

	lineTests();

	std::cout << "\n\n\n-----------Triangle Tests----------------------\n";

	triangleTests();

	std::cout << "\n\n-----------End Tests----------------------\n";


	std::cout << "\n\n\n-----------Circle----------------------\n";

	Frame frame{};
	Frame* frameP{ &frame };
	Circle mycircle{ 10, 10, 5 };
	mycircle.draw(frameP);
	frameP->show();

	return 0;
}
catch (const std::exception& e)
{
	std::cerr << e.what();
	return -1;
}
catch (...)
{
	std::cerr << "unknown error";
	return -2;
}
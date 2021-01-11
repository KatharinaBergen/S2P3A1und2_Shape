#include "Frame.h"
#include <iostream>


Frame::Frame(): frame{}
{
	for (int i{high-1}; i >= 0; --i)
	{
		for (int j{}; j < wide; ++j)
		{
			frame[i][j] = Frame::color(black);
		}
	}
}

void Frame::put_point(int aHigh, int bWide)
{
	if (aHigh >= high || bWide >= wide) { throw std::runtime_error{ "Error at Frame::put_point(): point to plot is not on chart." }; }
	frame[aHigh][bWide] = Frame::color(white);
}

void Frame::reset()
{
	for (int i{ high - 1 }; i >= 0; --i)
	{
		for (int j{}; j < wide; ++j)
		{
			frame[i][j] = Frame::color(black);
		}
	}
}

void Frame::show() const
{
	for (int i{ high - 1 }; i >= 0; --i)
	{
		for (int j{}; j < wide; ++j)
		{
			std::cout << frame.at(i).at(j);
		}
		std::cout << std::endl;
	}
}

bool Frame::on_frame(int aHigh, int bWide) const
{
	if (aHigh >= high || bWide >= wide) { return false; }
	else if (frame.at(aHigh).at(bWide) == Frame::color(white)) { return true; }
	return false;
}

bool Frame::test(Frame* actual)
{
	for (int i{ high - 1 }; i >= 0; --i)
	{
		for (int j{}; j < wide; ++j)
		{
			if ((*actual).on_frame(i, j) != (*this).on_frame(i, j) ) return false;
		}
	}

	return true;
}

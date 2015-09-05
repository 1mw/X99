#include "barlib.h"
#include "../../kernel/xlib.h"

namespace _barlib
{
	void printWelcomeMessageForBar()
	{
		xlib::video::writeString("Welcome to Bar!");
		xlib::video::newLine();
		xlib::video::newLine();
		xlib::video::writeString("Welcome again to Bar!");
	}
}
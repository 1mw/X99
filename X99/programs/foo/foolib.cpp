#include "foolib.h"
#include "../../kernel/xlib.h"

namespace _foolib
{
	void printWelcomeMessage()
	{
		xlib::video::writeString("Welcome to Foo!");
		xlib::video::newLine();
		xlib::video::newLine();
		xlib::video::writeString("Welcome again!");
	}
}
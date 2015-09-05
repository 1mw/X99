#include "x99program_bar.h"
#include "../../kernel/xlib.h"
#include "bar.h"

X99Program_bar::X99Program_bar()
{
	aliases[0] = "bar";
	aliases[1] = "Bar";
	aliases[2] = "BAR";
}
	
bool X99Program_bar::start()
{
	_Bar::startBar();
	return false;
}
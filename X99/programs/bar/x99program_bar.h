#ifndef ___x99program_bar_
#define ___x99program_bar_

#include "../../kernel/xlib.h"

class X99Program_bar : public xlib::program::X99Program
{
public:
	const char* aliases[3];
	X99Program_bar();
	bool start() override;
};

#endif
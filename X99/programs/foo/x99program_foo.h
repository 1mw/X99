#ifndef ___x99program_foo_
#define ___x99program_foo_

#include "../../kernel/xlib.h"

class X99Program_foo : public xlib::program::X99Program
{
public:
	char* aliases[3];
	X99Program_foo();
	bool start() override;
};

#endif
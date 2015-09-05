// x99program_foo.h
//
// Foo is an example program for X99.
//
// Copyright (c) 2015, Mark Aldrich, All rights reserved.

#ifndef ___x99program_foo_
#define ___x99program_foo_

#include "../../kernel/xlib.h"

class X99Program_foo : public xlib::program::X99Program
{
public:
	const char* aliases[3];
	X99Program_foo();
	bool start() override;
};

#endif
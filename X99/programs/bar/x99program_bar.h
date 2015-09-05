// x99program_bar.h
//
// Bar is an example program for X99.
//
// Copyright (c) 2015, Mark Aldrich, All rights reserved.

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
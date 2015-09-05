// x99program_bar.cpp
//
// Bar is an example program for X99.
//
// Copyright (c) 2015, Mark Aldrich, All rights reserved.

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
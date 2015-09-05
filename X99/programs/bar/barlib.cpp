// barlib.cpp
//
// Bar is an example program for X99.
//
// Copyright (c) 2015, Mark Aldrich, All rights reserved.

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
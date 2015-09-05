// kernel.h
//
// This is the main kernel header file.
//
// Copyright (c) 2015, Mark Aldrich, All rights reserved.

#ifndef ___kernel_
#define ___kernel_

#include "xlib.h"
#include "../programs/foo/x99program_foo.h"
#include "../programs/bar/x99program_bar.h"

//xlib::program::X99Program programs[2] = {
//	X99Program_bar(),
//	X99Program_foo()
//};

X99Program_bar p;
X99Program_foo f;

extern "C"
void kernel_main();

#endif
// foo.cpp
//
// Foo is an example program for X99.
//
// Copyright (c) 2015, Mark Aldrich, All rights reserved.

#include "foo.h"
#include "foolib.h"

namespace _Foo
{
	void startFoo()
	{
		_foolib::printWelcomeMessage();
		
		// Keep control of the CPU in the hands of the program,
		// rather than the kernel or the bootstrapper.
		for(;;) {}
	}
}
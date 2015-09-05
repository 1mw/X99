#include "x99program_foo.h"
#include "../../kernel/xlib.h"
#include "foo.h"

X99Program_foo::X99Program_foo()
{
	aliases[0] = "foo";
	aliases[1] = "Foo";
	aliases[2] = "FOO";
}
	
bool X99Program_foo::start()
{
	_Foo::startFoo();
	return false;
}
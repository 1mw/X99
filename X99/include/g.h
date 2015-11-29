#ifndef g_h
#define g_h

int g_inputAndExec();

/*
G is a programming language for the X99 operating system.

"$" is used for variables.

"#" is used for registers.

"@" is used for operators. Ex:
	- @+ (num1) :: (num2) :: (result)
	- @- (num1) :: (num2) :: (result)
	- @* (num1) :: (num2) :: (result)
	- @/ (num1) :: (num2) :: (result)
	- @init (var)
	- @store (var) :: (value)
	- @yield (value)
	- @jump (line)
	- @jumpz (var) :: (line)
	- @jumpp (var) :: (line)
	- @jumpn (var) :: (line)
	- @equal (var) :: (literal) :: (result)
	- @push (value)
	- @pop (var)
	- @printv (value)
	- @printc (value)
	- @compare (var1) :: (var2)
";" is for comments.
*/

#endif
#ifndef g_h
#define g_h

int g_inputAndExec();

/*
G is a programming language for the X99 operating system.

"@" is used for operators. Ex:
	- @+ (num1) :: (num2) :: (result)
	- @- (num1) :: (num2) :: (result)
	- @* (num1) :: (num2) :: (result)
	- @/ (num1) :: (num2) :: (result)
	!- @init (var)
	- @storel (var) :: (literal)
	- @storev (var1) :: (var2)
	- @storer (var1) :: (register)
	- @yieldl (literal)
	- @yieldv (var)
	- @jumpl (line)
	- @jumpv (var)
	- @jumpzl (var) :: (line)
	- @jumpzv (var) :: (var)
	- @jumppl (var) :: (line)
	- @jumppv (var) :: (var)
	- @jumpnl (var) :: (line)
	- @jumpnv (var) :: (var)
	- @jumpeqv (var)
	- @equall (var) :: (literal) :: (result)
	- @equalv (var) :: (var) :: (result)
	- @pushv (var)
	- @pushl (literal)
	- @pop (var)
	- @printv (var)
	- @printl (literal)
	- @printcv (var)
	- @printcl (literal)
	- @compare (var1) :: (var2)
";" is for comments.
*/

#endif
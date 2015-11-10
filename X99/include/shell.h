// X99 Shell

#ifndef shell_h
#define shell_h

char* shell_command;

void shell_start(void);
void shell_init(void);

// The commands in the shell should call this when they are going to exit the
// shell for some reason. This prevents memory leaks.
void shell_deinit(void);

#endif
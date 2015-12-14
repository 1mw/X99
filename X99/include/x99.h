///
/// x99.h
/// X99 kernel specification.
///

#ifndef x99_h
#define x99_h

#include <memory/multiboot.h>

///
/// Kernel entry.
///
void kernel_main(multiboot_info_t* mbt, unsigned int magic);

#endif

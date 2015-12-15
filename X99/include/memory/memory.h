///
/// memory.h
/// Memory management specifications to be provided to other files to use.
///

#ifndef memory_h
#define memory_h

#include <types.h>

///
/// A function to check a certain bit of the GRUB flags.
///
#define multiboot_checkFlag(flags, bit)	((flags) & (1 << (bit)))

///
/// xlib_memory memory map variables.
///
extern unsigned int xlib_memory_mmapStarts[100];
extern unsigned int xlib_memory_mmapEnds[100];
extern unsigned int xlib_memory_mmapType[100];
extern unsigned int xlib_memory_mmapLength[100];
extern unsigned int xlib_memory_numberOfEntries;
extern unsigned int xlib_memory_mmapLastIndex;
extern unsigned int xlib_memory_mmapLastAddress;
extern bool xlib_memory_didInit;

#endif

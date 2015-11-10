#ifndef memory_h
#define memory_h

#include <types.h>

#define multiboot_checkFlag(flags, bit)	((flags) & (1 << (bit)))
/*

*/

extern unsigned int xlib_memory_mmapStarts[100];
extern unsigned int xlib_memory_mmapEnds[100];
extern unsigned int xlib_memory_mmapType[100];
extern unsigned int xlib_memory_mmapLength[100];
extern unsigned int xlib_memory_numberOfEntries;
extern unsigned int xlib_memory_mmapLastIndex;
extern unsigned int xlib_memory_mmapLastAddress;
extern bool xlib_memory_didInit;

#endif

# Makefile
#
# This is the makefile for the X99 operating system.
#
# It requires that a GCC cross-compiler for the 1686-elf target be located
# at $HOME/opt/cross/bin/i686-elf-{GCC, G++, AS}.
#
# Makefile targets:
#	none: Compiles the X99 operating system and generates an ISO file.
#	run: Compiles the X99 operating system (if necessary) and runs it in QEMU.
#	clean: Removes any compiled file (including any generated ISOs).
#
# Copyright (c) 2015, Mark Aldrich, All rights reserved.

export PREFIX="$HOME/opt/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:/usr/bin/:$PATH"

CPP_SOURCES := $(wildcard kernel/*.cpp)
CPP_OBJECTS := $(CPP_SOURCES:.cpp=.o)
CPP_OBJECTS := $(CPP_OBJECTS:kernel/%=compiled/%)

all: X99.iso

X99.iso: iso/boot/X99.bin
	/bin/cp compiled/X99.bin iso/boot/X99.bin
	/usr/bin/grub-mkrescue -o X99.iso iso

iso/boot/X99.bin: compiled/boot.o $(CPP_OBJECTS)
	${HOME}/opt/cross/bin/${TARGET}-gcc -T misc/linker.ld -o compiled/X99.bin -ffreestanding -O2 -nostdlib $^ -lgcc

compiled/boot.o: misc/boot.asm
	${HOME}/opt/cross/bin/${TARGET}-as misc/boot.asm -o compiled/boot.o

compiled/%.o: kernel/%.cpp
	${HOME}/opt/cross/bin/${TARGET}-g++ -c $^ -o $@ -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti

clean:
	/bin/rm compiled/*.o compiled/*.bin iso/boot/X99.bin X99.iso

run: X99.iso
	/usr/bin/qemu-system-i386 -cdrom X99.iso
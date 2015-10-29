# Makefile
#
# Running this makefile requires that an i686-elf bare-bones (ld and bare gcc)
# toolchain be in the current path.

export TARGET=i686-elf

C_SOURCES := $(wildcard kernel/*.c)
C_OBJECTS := $(C_SOURCES:.c=.o)
C_OBJECTS := $(C_OBJECTS:kernel/%=compiled/%)
COMPILED_DIR := compiled/
INCLUDE_DIR := include/

all: X99.iso

X99.iso: iso/boot/X99.bin
	/bin/cp compiled/X99.bin iso/boot/X99.bin
	/usr/bin/grub2-mkrescue -o X99.iso iso

iso/boot/X99.bin: compiled/boot.o $(C_OBJECTS)
	${TARGET}-gcc -T misc/linker.ld -o compiled/X99.bin -ffreestanding -O2 -nostdlib $^ -lgcc

compiled/boot.o: misc/boot.asm
	@echo $(PROGRAM_OBJECTS)
	${TARGET}-as misc/boot.asm -o compiled/boot.o

compiled/%.o: kernel/%.c
	${TARGET}-gcc -I$(INCLUDE_DIR) -c $^ -o $@ -ffreestanding -O2 -Wall -Wextra -fno-exceptions -std='c99'

clean:
	/bin/rm compiled/*.o compiled/*.bin iso/boot/X99.bin X99.iso

run: X99.iso
	/usr/bin/qemu-system-i386 -cdrom X99.iso

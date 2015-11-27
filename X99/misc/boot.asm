# Constants for multiboot
.set ALIGN,    1<<0             # align loaded modules on page boundaries
.set MEMINFO,  1<<1             # provide memory map
.set FLAGS,    ALIGN | MEMINFO  # this is the Multiboot 'flag' field
.set MAGIC,    0x1BADB002       # 'magic number' lets bootloader find the header
.set CHECKSUM, -(MAGIC + FLAGS) # checksum of above, to prove we are multiboot

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

# Allocate room for X99's own stack
.section .bootstrap_stack, "aw", @nobits
stack_bottom:
.skip 65536 # 16 KiB
stack_top:

.section .text
.global _start
.type _start, @function
_start:
	# Apply X99's new stack
	movl $stack_top, %esp

	# Push the given multiboot structure from GRUB to the kernel using the
	# C parameter pushing style. The eax register is the magic number, and the
	# ebx register is the pointer to the actual table.
	pushl %eax
	pushl %ebx

	# Call kernel
	call kernel_main

	# Prevent interrupts and hang just in case the X99 kernel exits
	cli
	hlt
.Lhang:
	jmp .Lhang

# Calculate size of OS
.size _start, . - _start

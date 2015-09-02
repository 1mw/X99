echo "~~~Cleaning previously compiled files...~~~"
cd compiled
rm *.o *.bin
cd ../iso/boot
rm X99.bin
cd ../../
echo "~~~Done cleaning previously compiled files.~~~"

echo "~~~Setting build variables...~~~"
export PREFIX="$HOME/opt/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"
echo "~~~Done setting build variables.~~~"

echo "~~~Compiling bootstrapper...~~~"
i686-elf-as boot.asm -o compiled/boot.o
echo "~~~Done compiling bootstrapper.~~~"

echo "~~~Compiling kernel...~~~"
i686-elf-g++ -c kernel.cpp -o compiled/kernel.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti
echo "~~~Done compiling kernel.~~~"

cd compiled

echo "~~~Linking the kernel...~~~"
i686-elf-gcc -T ../linker.ld -o X99.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc
echo "~~~Done linking the kernel~~~"

echo "~~~Creating ISO...~~~"
cp X99.bin ../iso/boot/X99.bin
cd ../
grub-mkrescue -o X99.iso iso
echo "~~~Done creating ISO.~~~"

echo "~~~Starting QEMU...~~~"
qemu-system-i386 -cdrom X99.iso
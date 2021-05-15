kernel.elf: stivale2.elf entry.elf boot.elf
	ld -T linker.ld ../../../main.elf stivale2.elf entry.elf boot.elf -o kernel.elf

stivale2.elf: stivale2.c
	clang -target x86_64-pc-none-elf -fno-builtin -ffreestanding -nostdlib -c stivale2.c -o stivale2.elf

entry.elf: entry.c
	clang -target x86_64-pc-none-elf -fno-builtin -ffreestanding -nostdlib -I../../../include -c entry.c -o entry.elf

boot.elf: boot.asm
	nasm -f elf64 -o boot.elf boot.asm
CFLAGS:=-I../../../include -fno-pic -mgeneral-regs-only -mno-red-zone -fno-stack-protector -fpie -target x86_64-pc-none-elf -fno-builtin -ffreestanding -nostdlib -c
kernel.elf: stivale2.elf entry.elf boot.elf
	ld -T linker.ld ../../../total.elf stivale2.elf entry.elf boot.elf -o kernel.elf

stivale2.elf: stivale2.c
	clang $(CFLAGS) stivale2.c -o stivale2.elf

entry.elf: entry.c
	clang $(CFLAGS) entry.c -o entry.elf

boot.elf: boot.asm
	nasm -f elf64 -o boot.elf boot.asm
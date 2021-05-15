.PHONY: clean iso x86

iso: x86
	mkdir iso
	cp arch/x86/boot/kernel.elf iso/kernel.elf
	cp arch/x86/boot/limine.cfg iso/limine.cfg
	cp limine/limine-cd.bin iso/limine-cd.bin
	cp limine/limine-eltorito-efi.bin iso/limine-eltorito-efi.bin
	cp limine/limine.sys iso/limine.sys
	xorriso -as mkisofs -b limine-cd.bin -no-emul-boot -boot-load-size 4 \
		-boot-info-table -part_like_isohybrid -eltorito-alt-boot \
		-e limine-eltorito-efi.bin -no-emul-boot iso/ -isohybrid-gpt-basdat \
		-o x86.iso
	limine/limine-install-linux-x86_64 x86.iso

clean:
	rm -rf iso
	rm -rf x86.iso

	rm -rf arch/x86/boot/*.elf

x86: main.elf
	cd arch/x86/boot && make

main.elf: main.c
	clang -target x86_64-pc-none-elf -fno-builtin -ffreestanding -nostdlib -Iinclude/ -c main.c -o main.elf
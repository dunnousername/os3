.PHONY: clean iso x86 modules

LDFLAGS:=-fno-pic -mgeneral-regs-only -mno-red-zone -fno-stack-protector -fpie -target x86_64-pc-none-elf -fno-builtin -ffreestanding -nostdlib
CFLAGS:=$(LDFLAGS) -I$(PWD)/include/ -c

export CFLAGS
export LDFLAGS

OBJECTS=main.elf memfuncs.elf modules.elf bootstrap.elf endian.elf elf.elf panic.elf _debug.elf

iso: x86
	mkdir iso
	cp arch/x86/boot/kernel.elf iso/kernel.elf
	cp arch/x86/boot/limine.cfg iso/limine.cfg
	cp limine/limine-cd.bin iso/limine-cd.bin
	cp limine/limine-eltorito-efi.bin iso/limine-eltorito-efi.bin
	cp limine/limine.sys iso/limine.sys
	cd modules && $(MAKE) iso_install && cd ..
	xorriso -as mkisofs -b limine-cd.bin -no-emul-boot -boot-load-size 4 \
		-boot-info-table -part_like_isohybrid -eltorito-alt-boot \
		-e limine-eltorito-efi.bin -no-emul-boot iso/ -isohybrid-gpt-basdat \
		-o x86.iso
	limine/limine-install-linux-x86_64 x86.iso

clean:
	rm -rf iso
	rm -rf x86.iso
	rm -rf *.elf

	rm -rf arch/x86/boot/*.elf
	rm -rf arch/x86/mmu/*.elf
	rm -rf arch/x86/serial/*.elf

	cd modules && $(MAKE) clean && cd ..

modules:
	cd modules && $(MAKE) all && cd ..

x86: total.elf
#	cd arch/x86/mmu && make && cd ../../..
#	cd arch/x86/serial && make && cd ../../..
	cd arch/x86/boot && make && cd ../../..

total.elf: $(OBJECTS)
	ld -i -o total.elf $(OBJECTS)

$(OBJECTS): %.elf : %.c
	clang $(CFLAGS) -o $@ $<

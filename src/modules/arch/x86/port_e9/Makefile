module.elf: port_e9.elf
	clang $(LDFLAGS) -Wl,-no-dynamic-linker -T ../../../common_linker.ld -o module.elf port_e9.elf

port_e9.elf: port_e9.c
	clang $(CFLAGS) -o port_e9.elf port_e9.c
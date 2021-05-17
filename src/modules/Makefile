MODULES_X86=arch/x86/port_e9
MODULES=$(MODULES_X86)
ISO_INSTALL_MODULES=$(addprefix iso_install-,$(MODULES))

.PHONY: all clean iso_install iso_mkdir $(MODULES) $(ISO_INSTALL_MODULES)

export CFLAGS

all: $(MODULES)

clean:
	rm -rf *.elf
	rm -rf */*.elf
	rm -rf arch/*/*/*.elf

iso_mkdir:
	mkdir ../iso/modules

iso_install: iso_mkdir $(ISO_INSTALL_MODULES)

$(ISO_INSTALL_MODULES): iso_install-%: %
	cp $</module.elf ../iso/modules/$(subst /,-,$<).elf
	printf "MODULE_PATH=boot:///modules/$(subst /,-,$<).elf\nMODULE_STRING=.\n" >> ../iso/limine.cfg

$(MODULES):
	pushd $@ && $(MAKE) module.elf && popd

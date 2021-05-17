#include <stdint.h>
#include <endian.h>
#include <elf.h>
#include <bootstrap.h>
#include <panic.h>
#include <_debug.h>
#include <memfuncs.h>

/* TODO PLATFORM: these functions, particularly relocation, will need to be rewritten for new platforms. */

static uintptr_t get_symbol(void *elf, elf_section_entry_t *table, uint32_t entry) {
    return ((elf_sym_t *) &((uint8_t *) elf)[table->offset])[entry].value;
}

static void handle_rel(void *elf, void *mimage, elf_rela_t *rela, elf_section_entry_t *table, uint32_t type) {
    void *where = &((uint8_t *) mimage)[rela->offset];
    uintptr_t s = get_symbol(elf, table, (rela->info) >> 32);
    switch (rela->info & 0xffffffff) {
        case 0:
            /* R_X86_64_NONE */
            break;
        case 1:
            /* R_X86_64_64 */
            *((uint64_t *) where) = s + rela->addend;
            break;
        case 8:
            /* R_X86_64_RELATIVE */
            *((uint64_t *) where) = ((uint64_t) mimage) + rela->addend;
            break;
        default:
            PANIC2("unknown ELF relocation", (uint64_t) rela->info);
            break;
    }
}

void *load_elf(void *elf) {
    elf_header_t *header = elf;
    if (header->magic != ELF_MAGIC_HE) {
        PANIC("ELF magic header does not match");
    }

    if (header->order != ENDIAN_HOST) {
        PANIC("ELF endianness does not much host");
    }

    if (header->version != ELF_VERSION) {
        PANIC("ELF version is not 1");
    }

    if (header->version2 != ELF_VERSION) {
        PANIC("ELF version2 is not 1");
    }

    /*if (header->entry) {
        PANIC("ELF has a nonzero entry address");
    }*/

    /* TODO: check ISA, etc. */

    if (header->ph_ent_size != sizeof(elf_program_entry_t)) {
        PANIC("ELF has a different program entry size");
    }

    if (header->sh_ent_size != sizeof(elf_section_entry_t)) {
        PANIC("ELF has a different section entry size");
    }

    elf_program_entry_t *ph = (void *) &((uint8_t *) elf)[header->ph_offset];
    uintptr_t fat_block_size = 0;
    for (int i = 0; i < header->ph_num_entries; i++) {
        if (ph[i].type == PT_NULL)
            continue;
        uintptr_t end = ph[i].vaddr + ph[i].memsz;
        fat_block_size = (end > fat_block_size) ? end : fat_block_size;
    }

    void *mimage = bs_alloc(fat_block_size);

    for (int i = 0; i < header->ph_num_entries; i++) {
        if (ph[i].type == PT_NULL)
            continue;
        memcpy(&((uint8_t *) mimage)[ph[i].vaddr], &((uint8_t *) elf)[ph[i].offset], ph[i].memsz);
    }

    elf_section_entry_t *sh = (void *) &((uint8_t *) elf)[header->sh_offset];
    for (int i = 0; i < header->sh_num_entries; i++) {
        switch (sh[i].type) {
            case SHT_NULL:
            case SHT_PROGBITS:
            case SHT_SYMTAB:
            case SHT_STRTAB:
            case SHT_HASH:
            case SHT_DYNAMIC:
            case SHT_NOTE:
            case SHT_DYNSYM:
                break;
            case SHT_NOBITS:
                sh[i].offset = (uintptr_t) ((uint8_t *) mimage - (uint8_t *) bs_alloc(sh[i].size));
                break;
            case SHT_RELA:
            case SHT_REL:
                for (int j = 0; j < sh[i].size; j += sh[i].entsize) {
                    handle_rel(
                        elf,
                        mimage,
                        (void *) &((uint8_t *) elf)[sh[i].offset + j],
                        (void *) &sh[sh[i].link],
                        sh[i].type
                    );
                }
                break;
            default:
                if (sh[i].type >= SHT_LOOS) {
                    break;
                }
                PANIC2("unknown ELF section type", (uint64_t) sh[i].type);
                break;
        }
    }

    return mimage;
}
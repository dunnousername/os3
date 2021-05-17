#ifndef _ELF_H_
#define _ELF_H_

#include <stdint.h>
#include <endian.h>

#define ELF_MAGIC 0x7F454C46

#if   ENDIAN_HOST == ENDIAN_BIG
#define ELF_MAGIC_HE 0x7F454C46
#elif ENDIAN_HOST == ENDIAN_LITTLE
#define ELF_MAGIC_HE 0x464C457F
#else
#error "invalid endian"
#endif

#define ELF_CLASS_32 1
#define ELF_CLASS_64 2

#if   PLATFORM_NUMBITS == 32
#define ELF_CLASS_HOST ELF_CLASS_32
#elif PLATFORM_NUMBITS == 64
#define ELF_CLASS_HOST ELF_CLASS_64
#else
#error "invalid platform pointer length"
#endif

#define ELF_VERSION  1

#define ELF_ABI_SYSTEM_V 0

#define ET_NONE 0
#define ET_REL  1
#define ET_EXEC 2
#define ET_DYN  3
#define ET_CORE 4

typedef struct {
    uint32_t magic;
    uint8_t clazz;
    uint8_t order;
    uint8_t version;
    uint8_t abi;
    uint8_t abi_version;
    uint8_t pad[7];
    uint16_t type;
    uint16_t isa;
    uint32_t version2;
    uintptr_t entry;
    uintptr_t ph_offset;
    uintptr_t sh_offset;
    uint32_t flags;
    uint16_t size;
    uint16_t ph_ent_size;
    uint16_t ph_num_entries;
    uint16_t sh_ent_size;
    uint16_t sh_num_entries;
    uint16_t sh_shstr_index;
} elf_header_t;

#define PT_NULL    0
#define PT_LOAD    1
#define PT_DYNAMIC 2
#define PT_INTERP  3
#define PT_NOTE    4

typedef struct {
    uint32_t type;
#if ELF_CLASS_HOST == ELF_CLASS_64
    uint32_t flags;
#endif
    uintptr_t offset;
    uintptr_t vaddr;
    uintptr_t paddr;
    uintptr_t filesz;
    uintptr_t memsz;
#if ELF_CLASS_HOST == ELF_CLASS_32
    uint32_t flags;
#endif
    uintptr_t align;
} elf_program_entry_t;

#define SHT_NULL     0x00
#define SHT_PROGBITS 0x01
#define SHT_SYMTAB   0x02
#define SHT_STRTAB   0x03
#define SHT_RELA     0x04
#define SHT_HASH     0x05
#define SHT_DYNAMIC  0x06
#define SHT_NOTE     0x07
#define SHT_NOBITS   0x08
#define SHT_REL      0x09
#define SHT_DYNSYM   0x0B

#define SHT_LOOS     0x60000000

#define SHF_WRITE     0x001
#define SHF_ALLOC     0x002
#define SHF_EXECINSTR 0x004
#define SHF_MERGE     0x010
#define SHF_STRINGS   0x020
#define SHF_GROUP     0x200

typedef struct {
    uint32_t name;
    uint32_t type;
    uintptr_t flags;
    uintptr_t addr;
    uintptr_t offset;
    uintptr_t size;
    uint32_t link;
    uint32_t info;
    uintptr_t align;
    uintptr_t entsize;
} elf_section_entry_t;

typedef struct {
    uintptr_t offset;
    uintptr_t info;
} elf_rel_t;

typedef struct {
    uintptr_t offset;
    uintptr_t info;
    uintptr_t addend;
} elf_rela_t;

typedef struct {
    uint32_t name;
    uint32_t value;
    uint32_t size;
    uint8_t info;
    uint8_t other;
    uint32_t shndx;
} elf_sym_32_t;

typedef struct {
    uint64_t name;
    uint8_t info;
    uint8_t other;
    uint64_t shndx;
    uint64_t value;
    uint64_t size;
} elf_sym_64_t;

#if ELF_CLASS_HOST == ELF_CLASS_64
typedef elf_sym_64_t elf_sym_t;
#else
typedef elf_sym_32_t elf_sym_t;
#endif

void *load_elf(void *elf);

#endif
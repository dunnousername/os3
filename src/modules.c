#include <stdint.h>
#include <limits.h>
#include <modules.h>
#include <memfuncs.h>
#include <_debug.h>

static module_desc_t loaded_modules[MAX_MODULES];
static uintptr_t loaded_modules_len = 0;

static void append_module(module_desc_t desc) {
    if (++loaded_modules_len >= MAX_MODULES) {
        --loaded_modules_len;
        return;
    }

    for (int i = 0; i < loaded_modules_len - 1; i++) {
        if (loaded_modules[i].start->nice > desc.start->nice) {
            for (int j = loaded_modules_len - 1; j > i; j--) {
                /* move them all up */
                loaded_modules[j] = loaded_modules[j - 1];
            }

            loaded_modules[i] = desc;
            return;
        }
    }

    loaded_modules[loaded_modules_len - 1] = desc;
}

void *kdlsym(char *name) {
    for (int i = 0; i < loaded_modules_len; i++) {
        if (!loaded_modules[i].loaded) {
            continue;
        }

        module_symbol_t *sym = loaded_modules[i].start->symbols;
        while (sym->name) {
            if (strcmp(sym->name, name) == 0) {
                return sym->symbol;
            }

            sym++;
        }
    }

    return (void *) 0;
}

void load_module(module_desc_t desc) {
    desc.loaded = 0;
    module_info_t *mod = desc.start;
    if (mod->magic != MODULE_MAGIC) {
        return;
    }

    append_module(desc);
}

void commit_modules() {
    for (int i = 0; i < loaded_modules_len; i++) {
        if (loaded_modules[i].loaded)
            continue;
        
        loaded_modules[i].start->init(kdlsym);
        
        loaded_modules[i].loaded = 1;
        
        void (*sym)(char *) = kdlsym("_debug_initmod");
        
        if (sym) {
            sym(loaded_modules[i].start->name);
        }
    }
}
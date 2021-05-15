typedef struct tty_driver_t {
    void *extra;
    void (*write)(struct tty_driver_t*, char*);
    void (*clear)(struct tty_driver_t*);
} tty_driver_t;

extern tty_driver_t *chosen_tty;
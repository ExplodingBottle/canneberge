#ifndef BOOT_HEADER_H
#define BOOT_HEADER_H

#include <stddef.h>

/* This structure represents the magic header to be added at the start of the binary */
struct userland_header_t
{
    char magic[4];
    char kernel_version[8];
    void *stor_addr;
    size_t stor_size;
    void *apps_flash_start;
    void *apps_flash_end;
    void *apps_mem_start;
    void *apps_mem_end;
    void *dn_flash_start;
    void *dn_flash_end;
    char magic2[4];

} __attribute__((packed));
typedef struct userland_header_t userland_header_t;

/* Array of bytes corresponding to the magic number */
#define MAGIC_NUMB             \
    {                          \
        0xFE, 0xED, 0xC0, 0xDE \
    }

/* Target kernel version, must be changed with each releases */
#define KERNEL_VERSION "23.2.3"

#endif

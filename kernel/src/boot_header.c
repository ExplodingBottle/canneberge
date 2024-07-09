/* Userland header support */

#include <kernel/boot_header.h>

/* We need a dummy value for things we won't handle, such as file system */
const char *dummy_value = 0;

const userland_header_t header __attribute__((section(".header"))) = {
    MAGIC_NUMB,
    KERNEL_VERSION,
    &dummy_value,
    0x1,
    &dummy_value,
    &dummy_value,
    &dummy_value,
    &dummy_value,
    &dummy_value,
    &dummy_value,
    MAGIC_NUMB};

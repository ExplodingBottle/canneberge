#include <drivers/keyboard.h>

uint64_t keyboard_scan(void)
{
    uint64_t kb_val = 0, *ptr = &kb_val;
    asm volatile("SVC #34; STR R0, [%0]; STR R1, [%0,#4]"
                 : "=g"(ptr)
                 : "r"(ptr)
                 : "r0", "r1", "r2", "r3");
    return *ptr;
}


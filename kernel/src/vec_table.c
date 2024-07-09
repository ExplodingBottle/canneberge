/* Vector table support */

#include <kernel/vec_table.h>
#include <kernel/boot.h>
#include <kernel/memory_control.h>

const ISR InitialisationVector[] __attribute__((section(".isr_vector_table"))) = {
    _estack,
    start};

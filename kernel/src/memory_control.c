#include <kernel/memory_control.h>
#include <stdint.h>
#include <assert.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/stat.h>

char *securityPoint = (char *)_estack - STACK_SIZE - sizeof(char);

void init_stack_security(void)
{
    *(uint16_t *)securityPoint = SECURITY_MARKER;
}

caddr_t _sbrk(int incr)
{
    extern char _end; /* Defined by the linker */
    static char *heap_end;
    char *prev_heap_end;

    if (heap_end == 0)
    {
        heap_end = &_end;
    }
    prev_heap_end = heap_end;

    assert(*(uint16_t *)securityPoint == SECURITY_MARKER);
    assert(heap_end + incr < securityPoint);

    heap_end += incr;
    return (caddr_t)prev_heap_end;
}

unsigned long free_mem(void)
{
    struct mallinfo mem_infs = mallinfo();
    return securityPoint - _sbrk(0) + mem_infs.fordblks;
}

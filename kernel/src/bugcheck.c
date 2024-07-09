#include <kernel/bugcheck.h>
#include <kernel/console.h>
#include <drivers/display.h>

__attribute((noreturn)) void bugcheck(void)
{
    change_graphics_mode(CONSOLE_TEXT_MODE);

    for (;;)
    {
    }
}

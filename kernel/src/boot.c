/* Userland entry point */

#include <kernel/boot.h>

#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>

#include <stdlib.h>
#include <malloc.h>

#include <drivers/keyboard.h>
#include <drivers/powmgmt.h>
#include <kernel/memory_control.h>
#include <drivers/display.h>
#include <kernel/console.h>

#ifndef SIMULATOR
const extern uint8_t _datasf;
extern uint8_t _datas;
const extern uint8_t _datae;
extern uint8_t _bsss;
const extern uint8_t _bsse;
#endif

void start(void)
{
    #ifndef SIMULATOR
    /* Setting up RAM */
    memcpy(&_datas, &_datasf, &_datae - &_datas);
    memset(&_bsss, 0, &_bsse - &_bsss);

    /* Setting up stack security */
    init_stack_security();

    #endif

    /* Cleans screen */
    fill_rect_unicolor(screen_rect, 0);
    vsync_wait();

    /* Allowing suspend to only suspend and not shutdown */
    pow_change_suspend_mode(false);

    /* Display */
    printf("System started!\n");
    printf("Stack max size: %d bytes, Heap size: %lu bytes.\n", STACK_SIZE, free_mem());

    printf("IsCharging? %d\n", pow_is_battery_charging());
    printf("ChargeLevel %d\n", pow_get_batt_charge());
    printf("Voltage %f\n", pow_get_battery_voltage());    

    printf("Press EXE to stop the loop.\n");
    /* Write your code here */
    uint64_t scan = 0;
    do
    {
        scan = keyboard_scan();
    } while (!KEY_PRESSED(KB_EXE, scan));

    /* Execution end */
    printf("==============================\n");
    printf("Stack max size: %d bytes, Heap size: %lu bytes.\n", STACK_SIZE, free_mem());
    struct mallinfo mem_infs = mallinfo();
    printf("call to mallinfo()\n");
    printf("Total allocated space: %lu bytes\n", mem_infs.uordblks);
    printf("Total free space: %lu bytes\n", mem_infs.fordblks);
    printf("Allocated heap: %lu bytes\n", mem_infs.arena);
    printf("Unused blocks: %lu\n", mem_infs.ordblks);
    printf("==============================\n");
    printf("Press EXE to reboot, ON/OFF to shutdown, BACK to restart this system, BACKSPACE to suspend, ANS to suspend but come back to this system.\n");
    while (1)
    {
        scan = keyboard_scan();
        if (KEY_PRESSED(KB_EXE, scan))
        {
            pow_reboot(true);
        }
        if (KEY_PRESSED(KB_BACK, scan))
        {
            pow_reboot(false);
        }
        if (KEY_PRESSED(KB_ON_OFF, scan))
        {
            pow_shutdown();
        }
        if (KEY_PRESSED(KB_CLEAR, scan))
        {
            pow_suspend(false);
            refresh_console();
        }
        if (KEY_PRESSED(KB_ANS, scan))
        {
            pow_suspend(false);
            pow_reboot(false);
        }
    }
    exit(0);
}

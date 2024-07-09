#include <drivers/powmgmt.h>
#include <kernel/memory_control.h>
#include <kernel/boot.h>

extern void exit_sdl(void);

bool susp_mode = false;

void pow_reboot(bool switch_back_to_main)
{
    exit_sdl();
}
void pow_suspend(bool wait_for_onoff_release)
{
    if (susp_mode)
    {
        exit_sdl();
    }
}
void pow_shutdown(void)
{
    exit_sdl();
}
void pow_change_suspend_mode(bool should_suspend_shutdown)
{
    susp_mode = should_suspend_shutdown;
}

uint8_t pow_get_batt_charge(void)
{
    return 0;
}
bool pow_is_battery_charging(void)
{
    return true;
}

float pow_get_battery_voltage(void)
{
    return 0.0f;
}
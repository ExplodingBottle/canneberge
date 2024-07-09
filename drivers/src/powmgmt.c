#include <drivers/powmgmt.h>
#include <kernel/memory_control.h>
#include <kernel/boot.h>

void pow_reboot(bool switch_back_to_main)
{
    if (switch_back_to_main)
    {
        asm("SVC #46");
    }
    else
    {
        asm volatile(
            "MSR PSP, %0; BX %1"
            :
            : "r"(_estack), "r"(start));
    }
}
void pow_suspend(bool wait_for_onoff_release)
{
    asm("SVC #44");
}
void pow_shutdown(void)
{
    asm("SVC #43");
}
void pow_change_suspend_mode(bool should_suspend_shutdown)
{
    asm("SVC #42");
}

uint8_t pow_get_batt_charge(void)
{
    uint8_t batt_charge_lvl = 0, *ptr = &batt_charge_lvl;
    asm volatile("SVC #4; STR R0, [%0]"
                 : "=g"(ptr)
                 : "r"(ptr)
                 : "r0", "r1", "r2", "r3");
    return *ptr;
}

bool pow_is_battery_charging(void)
{
    bool batt_charging = false, *ptr = &batt_charging;
    asm volatile("SVC #3; STR R0, [%0]"
                 : "=g"(ptr)
                 : "r"(ptr)
                 : "r0", "r1", "r2", "r3");
    return *ptr;
}

float pow_get_battery_voltage(void)
{
    float batt_voltage = 0, *ptr = &batt_voltage;
    asm volatile("SVC #5; VSTR S0, [%0]"
                 : "=g"(ptr)
                 : "r"(ptr)
                 : "r0", "r1", "r2", "r3");
    return *ptr;
}
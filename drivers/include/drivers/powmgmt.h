#ifndef POWMGMT_H
#define POWMGMT_H

#include <stdbool.h>
#include <stdint.h>

/* Reboots/resets the device. If switch_back_to_main is true, it will jump back to the original system instead of this one. */
void pow_reboot(bool switch_back_to_main);

/* Suspends the device. With wait_for_onoff_release to true, suspend will happen after releasing the power button */
void pow_suspend(bool wait_for_onoff_release);

/* This shuts the device down. */
void pow_shutdown(void);

/* Calling this with should_suspend_shutdown to true will make that pow_suspend() will shutdown the device instead of suspending it. */
void pow_change_suspend_mode(bool should_suspend_shutdown);

/* Returns battery charge with a number between 0 and 4 */
uint8_t pow_get_batt_charge(void);

/* Returns battery charging state */
bool pow_is_battery_charging(void);

/* Returns battery voltage */
float pow_get_battery_voltage(void);

#endif

#ifndef CONSOLE_H
#define CONSOLE_H

#include <stdint.h>

#define CONSOLE_TEXT_MODE 3
#define CONSOLE_GRAPHICS_MODE 1

void change_graphics_mode(uint8_t mode);
void console_write(char *content, int len);
void refresh_console(void);

#endif
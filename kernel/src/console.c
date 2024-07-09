#include <kernel/console.h>
#include <drivers/display.h>
#include <kernel/sysfont.h>

#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#define CHARS_PER_LINE (SCREEN_WIDTH / FONT_WIDTH)
#define CHARS_PER_COL (SCREEN_HEIGHT / FONT_HEIGHT)

uint8_t current_mode = CONSOLE_TEXT_MODE;

char textBuff[CHARS_PER_LINE * CHARS_PER_COL] = {0};

int cursor_x, cursor_y = 0;

void refresh_console(void)
{
    for (int line = 0; line < CHARS_PER_COL; line++)
    {
        for (int col = 0; col < CHARS_PER_LINE; col++)
        {
            disp_rect_t display_rect = {col * FONT_WIDTH, line * FONT_HEIGHT, FONT_WIDTH, FONT_HEIGHT};
            uint16_t buffer[FONT_WIDTH * FONT_HEIGHT];

            for (int pixel_y = 0; pixel_y < FONT_HEIGHT; pixel_y++)
            {
                for (int pixel_x = 0; pixel_x < FONT_WIDTH; pixel_x++)
                {
                    char cur_char = textBuff[col + line * CHARS_PER_LINE];
                    int elem_base = cur_char * ((FONT_HEIGHT * FONT_WIDTH) / 16);
                    int elem_idx = elem_base + ((pixel_x + (pixel_y * FONT_WIDTH)) / 16);
                    int elem_rmd = (pixel_x + (pixel_y * FONT_WIDTH)) % 16;
                    uint16_t current_char_line = sysfont[elem_idx];
                    uint16_t mask = 1 << (15 - elem_rmd);

                    buffer[pixel_x + pixel_y * FONT_WIDTH] = (current_char_line & mask) ? COLOR_WHITE : COLOR_BLACK;
                }
            }
            fill_rect(display_rect, buffer);
        }
    }
    vsync_wait();
}

void change_graphics_mode(uint8_t mode)
{
    if (mode == current_mode)
    {
        return;
    }
    current_mode = mode;
    if (mode == CONSOLE_GRAPHICS_MODE)
    {
        fill_rect_unicolor(screen_rect, 0);
    }
    if (mode == CONSOLE_TEXT_MODE)
    {
        refresh_console();
    }
}
void console_write(char *content, int len)
{
    bool leave = false;
    for (int i = 0; i < len && !leave; i++)
    {
        char c = content[i];
        switch (c)
        {
        case '\0':
            leave = true;
            break;
        case '\n':
            cursor_x = 0;
            cursor_y++;
            break;
        case '\r':
            cursor_x = 0;
            break;
        case '\b':
            cursor_x--;
            break;
        case '\f':
            cursor_x = 0;
            cursor_y = 0;
            memset(&textBuff, 0, sizeof(textBuff));
            break;
        default:
            textBuff[cursor_x + cursor_y * CHARS_PER_LINE] = c;
            cursor_x++;
        }
        if (cursor_x >= CHARS_PER_LINE)
        {
            cursor_x = 0;
            cursor_y++;
        }
        if (cursor_x < 0)
        {
            cursor_x = CHARS_PER_LINE - cursor_x;
            cursor_y--;
        }
        if (cursor_y >= CHARS_PER_COL)
        {
            for (int i = 1; i < CHARS_PER_COL; i++)
            {
                memset(&textBuff[(i - 1) * CHARS_PER_LINE], 0, CHARS_PER_LINE);
                memcpy(&textBuff[(i - 1) * CHARS_PER_LINE], &textBuff[i * CHARS_PER_LINE], CHARS_PER_LINE);
            }
            memset(&textBuff[(CHARS_PER_COL - 1) * CHARS_PER_LINE], 0, CHARS_PER_LINE);
            cursor_y = CHARS_PER_COL - 1;
        }
        if (cursor_y < 0)
        {
            cursor_y = 0;
        }
    }
    if (current_mode == CONSOLE_TEXT_MODE)
    {
        refresh_console();
    }
}

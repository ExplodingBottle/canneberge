#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define COLOR_BLACK 0x0000
#define COLOR_WHITE 0xffff

typedef struct disp_rect_t
{
    uint16_t x_origin;
    uint16_t y_origin;
    uint16_t x_size;
    uint16_t y_size;
} disp_rect_t;

const extern disp_rect_t screen_rect;

/* Fills a rect at the screen. Color is an array of colors of size rect.x_size * rect.y_size */
void fill_rect(disp_rect_t rect, const uint16_t *colors);

/* Fills a rect at screen with one unique color */
void fill_rect_unicolor(disp_rect_t rect, uint16_t color);

/* Same thing as fill_rect, but instead fetches the pixels from the screen */
void pull_rect(disp_rect_t rect, uint16_t *colors);

/* Waits for the VSync, prevents screen tearing */
void vsync_wait(void);

#endif

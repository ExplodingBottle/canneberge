#include <drivers/display.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>

uint16_t pix_buff[SCREEN_WIDTH * SCREEN_HEIGHT] = {0};

void fill_rect(disp_rect_t rect, const uint16_t *colors)
{
    for (int y = 0; y < rect.y_size; y++)
    {
        for (int x = 0; x < rect.x_size; x++)
        {
            pix_buff[rect.x_origin + x + (rect.y_origin + y) * SCREEN_WIDTH] = colors[x + y * rect.x_size];
        }
    }
}
void fill_rect_unicolor(disp_rect_t rect, uint16_t color)
{
    for (int y = 0; y < rect.y_size; y++)
    {
        for (int x = 0; x < rect.x_size; x++)
        {
            pix_buff[rect.x_origin + x + (rect.y_origin + y) * SCREEN_WIDTH] = color;
        }
    }
}
void pull_rect(disp_rect_t rect, uint16_t *colors)
{
    for (int y = 0; y < rect.y_size; y++)
    {
        for (int x = 0; x < rect.x_size; x++)
        {
            colors[x + y * rect.x_size] = pix_buff[rect.x_origin + x + (rect.y_origin + y) * SCREEN_WIDTH];
        }
    }
}
void vsync_wait(void)
{
}

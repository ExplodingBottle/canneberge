#include <drivers/display.h>

void fill_rect(disp_rect_t rect, const uint16_t *colors)
{
    asm("SVC #19");
}
void fill_rect_unicolor(disp_rect_t rect, uint16_t color)
{
    asm("SVC #20");
}
void pull_rect(disp_rect_t rect, uint16_t *colors)
{
    asm("SVC #18");
}
void vsync_wait(void)
{
    asm("SVC #21");
}

const disp_rect_t screen_rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

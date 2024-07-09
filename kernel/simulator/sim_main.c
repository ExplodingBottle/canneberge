#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <stdint.h>
#include <pthread.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <kernel/boot.h>
#include <kernel/console.h>
#include <drivers/display.h>

FILE *prbuff_file;
char printfbuff[4096];

extern uint16_t pix_buff[]; /* Comes from the display driver */
extern void keyb_evt(int key, bool released);
bool keep_window_open = true;

void exit_sdl(void)
{
   keep_window_open = false;
}

void *boot_thread_fnc()
{
    start();
}

const disp_rect_t screen_rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

int main(void)
{
    memset(pix_buff, 0xff, SCREEN_HEIGHT * SCREEN_WIDTH * 2);
    prbuff_file = fopen("/tmp/simulator-output.txt", "w+");
    dup2(fileno(prbuff_file), 1);
    dup2(fileno(prbuff_file), 2);

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Failed to initialize SDL.");
        return EXIT_FAILURE;
    }

    SDL_Window *sim_wind = SDL_CreateWindow("Canneberge - Simulator",
                                            SDL_WINDOWPOS_CENTERED,
                                            SDL_WINDOWPOS_CENTERED,
                                            SCREEN_WIDTH, SCREEN_HEIGHT,
                                            0);
    if (!sim_wind)
    {
        printf("Failed to create the window.");
        return EXIT_FAILURE;
    }

    SDL_Renderer *sdl_renderer = SDL_CreateRenderer(sim_wind, -1, SDL_RENDERER_ACCELERATED);

    pthread_t boot_thread;
    if (pthread_create(&boot_thread, NULL, boot_thread_fnc, NULL) != 0)
    {
        fprintf(stderr, "Thread creation failure.");
        return EXIT_FAILURE;
    }

    unsigned long last_read = 0;
    while (keep_window_open)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e) > 0)
        {

            SDL_UpdateWindowSurface(sim_wind);
            switch (e.type)
            {
            case SDL_QUIT:
                keep_window_open = false;
                break;
            case SDL_KEYDOWN:
                keyb_evt(e.key.keysym.sym, false);
                break;
            case SDL_KEYUP:
                keyb_evt(e.key.keysym.sym, true);
                break;
            }
        }

        SDL_RenderClear(sdl_renderer);
        for (int y = 0; y < SCREEN_HEIGHT; y++)
        {
            for (int x = 0; x < SCREEN_WIDTH; x++)
            {
                uint16_t color = pix_buff[x + y * SCREEN_WIDTH];

                int r5 = ((color >> 11) & 0x1F);
                int g6 = ((color >> 5) & 0x3F);
                int b5 = ((color) & 0x1F);

                int r8 = (r5 * 255 + 15) / 31;
                int g8 = (g6 * 255 + 31) / 63;
                int b8 = (b5 * 255 + 15) / 31;

                SDL_SetRenderDrawColor(sdl_renderer, r8, g8, b8, 0);
                SDL_RenderDrawPoint(sdl_renderer, x, y);
            }
        }
        SDL_RenderPresent(sdl_renderer);

        fflush(stdout);
        fflush(stderr);
        int rsize = fread(printfbuff, 1, 4096, prbuff_file);
        if (rsize != 0)
        {
            last_read += rsize;
            console_write(printfbuff, strlen(printfbuff));
            memset(printfbuff, 0, 4096);
        }
        fseek(prbuff_file, last_read, SEEK_SET);
    }

    pthread_cancel(boot_thread);

    SDL_DestroyWindow(sim_wind);

    return EXIT_SUCCESS;
}

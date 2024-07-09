#include <drivers/keyboard.h>
#include <SDL2/SDL.h>
#include <time.h>
#include <errno.h>
#include <stdbool.h>

uint64_t curr_state = 0;

struct mapping
{
    int sdlkey;
    keyboard_key_t syskey;
};

struct mapping key_mappings[] = {
    {SDLK_LEFT, KB_LEFT},
    {SDLK_UP, KB_UP},
    {SDLK_DOWN, KB_DOWN},
    {SDLK_RIGHT, KB_RIGHT},
    {SDLK_F1, KB_OK},
    {SDLK_F2, KB_BACK},
    {SDLK_ESCAPE, KB_HOME},
    {SDLK_F3, KB_ON_OFF},
    {SDLK_LSHIFT, KB_SHIFT},
    {SDLK_F4, KB_ALPHA},
    {SDLK_F5, KB_CUT},
    {SDLK_F6, KB_COPY},
    {SDLK_F7, KB_PASTE},
    {SDLK_BACKSPACE, KB_CLEAR},
    {SDLK_a, KB_A},
    {SDLK_b, KB_B},
    {SDLK_c, KB_C},
    {SDLK_d, KB_D},
    {SDLK_e, KB_E},
    {SDLK_f, KB_F},
    {SDLK_g, KB_G},
    {SDLK_h, KB_H},
    {SDLK_i, KB_I},
    {SDLK_j, KB_J},
    {SDLK_k, KB_K},
    {SDLK_l, KB_L},
    {SDLK_m, KB_M},
    {SDLK_n, KB_N},
    {SDLK_o, KB_O},
    {SDLK_p, KB_P},
    {SDLK_q, KB_Q},
    {SDLK_r, KB_R},
    {SDLK_s, KB_S},
    {SDLK_t, KB_T},
    {SDLK_u, KB_U},
    {SDLK_v, KB_V},
    {SDLK_w, KB_W},
    {SDLK_x, KB_X},
    {SDLK_y, KB_Y},
    {SDLK_z, KB_Z},
    {SDLK_SPACE, KB_SPACE},
    {SDLK_0, KB_ZERO},
    {SDLK_SEMICOLON, KB_DOT},
    {SDLK_END, KB_EXP},
    {SDLK_RSHIFT, KB_ANS},
    {SDLK_RETURN, KB_EXE}};

void keyb_evt(int key, bool released)
{
    keyboard_key_t syskey = -1;
    for (int i = 0; i < sizeof(key_mappings) / sizeof(struct mapping); i++)
    {
        if (key_mappings[i].sdlkey == key)
        {
            syskey = key_mappings[i].syskey;
            break;
        }
    }
    if (syskey == -1)
    {
        return;
    }
    uint64_t mask = (uint64_t)1 << syskey;
    if (released)
    {
        curr_state ^= mask;
    }
    else
    {
        curr_state |= mask;
    }
}

uint64_t keyboard_scan(void)
{
    /* It is so fast on a host system that we have to sleep a bit*/
    struct timespec to_sleep = {0, 5e7}; // Sleep for 1 second
    while ((nanosleep(&to_sleep, &to_sleep) == -1) && (errno == EINTR));

    return curr_state;
}

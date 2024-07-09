#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>

#define KEY_PRESSED(KEY, SCAN) (SCAN >> KEY) & (uint8_t)1

typedef enum keyboard_key_t
{
    KB_LEFT = 0,
    KB_UP = 1,
    KB_DOWN = 2,
    KB_RIGHT = 3,
    KB_OK = 4,
    KB_BACK = 5,
    KB_HOME = 6,
    KB_ON_OFF = 8,
    KB_SHIFT = 12,
    KB_ALPHA = 13,
    KB_CUT = 14,
    KB_COPY = 15,
    KB_PASTE = 16,
    KB_CLEAR = 17,
    KB_A = 18,
    KB_B = 19,
    KB_C = 20,
    KB_D = 21,
    KB_E = 22,
    KB_F = 23,
    KB_G = 24,
    KB_H = 25,
    KB_I = 26,
    KB_J = 27,
    KB_K = 28,
    KB_L = 29,
    KB_M = 30,
    KB_N = 31,
    KB_O = 32,
    KB_P = 33,
    KB_Q = 34,
    KB_R = 36,
    KB_S = 37,
    KB_T = 38,
    KB_U = 39,
    KB_V = 40,
    KB_W = 42,
    KB_X = 43,
    KB_Y = 44,
    KB_Z = 45,
    KB_SPACE = 46,
    KB_ZERO = 48,
    KB_DOT = 49,
    KB_EXP = 50,
    KB_ANS = 51,
    KB_EXE = 52

} keyboard_key_t;

/* Generates a keyboard scan, then use KEY_PRESSED to check if a key has been pressed */
uint64_t keyboard_scan(void);

#endif
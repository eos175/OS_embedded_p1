#pragma once

#include <drivers/kbd.h>
#include <stdbool.h>



typedef struct 
{
    bool up, down, left, right, a, b, select, start, space, enter;
} Input;



typedef enum {

    KKEY_A = 'a',
    KKEY_B = 'b',

    KKEY_SPACE = 32,
    KKEY_ENTER = 13,

    KKEY_UP = 4352,
    KKEY_DOWN = 16402,
    KKEY_LEFT = 51,
    KKEY_RIGHT = 46,

} KEY;




static inline Input input_read() 
{
    Input key;

    // TODO(eos175) esto se puede mejorar, cambiar por una tabla...
    
    int tmp = getkey();

    key.down    = tmp == KKEY_DOWN;
    key.up      = tmp == KKEY_UP;
    key.left    = tmp == KKEY_LEFT;
    key.right   = tmp == KKEY_RIGHT;
    key.a       = tmp == KKEY_A;
    key.space   = tmp == KKEY_SPACE;
    key.enter   = tmp == KKEY_ENTER;
    return key;

}



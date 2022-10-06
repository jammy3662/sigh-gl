#pragma once

#include "ext.h"
#include <raymath.h>

// ========= CONVENIENCE ============

#define let auto

// ================================

// the codebase is a mess, so
// no point in using semantic versioning
// this gets the point across
#define VERSION "testing"

/* --------------------------------------------
| TODO: Create a function that
| polls inputs independently of
| input device.
|
| For example, a function that takes
| a single input (like an enum value)
| and can return input status for keyboard,
| mouse, gamepad, etc. Without needing to
| specify which device to check for.
|
| This way, end user has complete freedom
| to map their inputs to any available device,
| without this needing to be hardcoded.
|______________________________________________*/

#define KEY_IDX 0x000
#define MOUSE_IDX 0x200
#define GAMEPAD_IDX 0x210
#define JOYSTICK_IDX 0x230

/*
// key binds
int16 knorth = KEY_W;
int16 ksouth = KEY_S;
int16 keast = KEY_D;
int16 kwest = KEY_A;

int16 kshift = KEY_LEFT_SHIFT;
int16 kctrl = KEY_LEFT_CONTROL;
int16 kjump = KEY_SPACE;
int16 ktab = KEY_TAB;

int16 kup = KEY_UP;
int16 kdown = KEY_DOWN;
int16 kright = KEY_RIGHT;
int16 kleft = KEY_LEFT;

int16 ktrigger = MOUSE_BUTTON_LEFT;
int16 kbumper = MOUSE_BUTTON_RIGHT;

int16 kexit = KEY_ESCAPE;
// ===
*/

// frame (internal render target / backbuffer)
uint16 fwidth = 1920;
uint16 fheight = 1080;

// window (onscreen drawing)
uint16 wwidth = 1280;
uint16 wheight = 720;

#ifdef DEBUG
// general-purpose error code
int8 errcode = 0;
#endif
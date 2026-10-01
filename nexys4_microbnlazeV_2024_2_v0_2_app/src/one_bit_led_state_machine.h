#ifndef BUTTON_STATE_H
#define BUTTON_STATE_H

#include <stdbool.h>
#include "xil_types.h"

#define IDLE    0
#define PRESSED 1

// Button Definitions
#define BUTTON_CENTRE	0x1
#define BUTTON_UP	    0x2
#define BUTTON_LEFT 	0x4
#define BUTTON_RIGHT    0x8
#define BUTTON_DOWN	    0x10


typedef struct {
    u16 State;
    bool Transitioned;
} StateAndTransition_t;

typedef struct {
    u32 color_right;
    u32 color_left;
    u32 color;
    StateAndTransition_t state_centre;
    StateAndTransition_t state_left;
    StateAndTransition_t state_right;
    StateAndTransition_t state_up;
    StateAndTransition_t state_down;
} ColorState_t;

StateAndTransition_t find_state(const StateAndTransition_t current, const u32 ButtonStatus, const u32 BUTTON);
void init_state(StateAndTransition_t* state);
void init_ColorState(ColorState_t* state);
ColorState_t get_next_Color(const ColorState_t current, const u32 ButtonStatus);
#endif
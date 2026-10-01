#include "one_bit_led_state_machine.h"

StateAndTransition_t find_state(const StateAndTransition_t current, const u32 ButtonStatus, const u32 BUTTON) {
    StateAndTransition_t next_state;
    if (current.State == IDLE) 
    {   
        if ((ButtonStatus & BUTTON) != 0) 
        { // then we have a button press
            next_state.State = PRESSED;
            next_state.Transitioned = true;
        }
        else 
        { // no transition
            next_state.State = IDLE;
            next_state.Transitioned = false;
        }
    }

    if (current.State == PRESSED)
    {
        if ((ButtonStatus & BUTTON) != 0) 
        { // button pressed, while it's already moved to pressed, just a fat finger so no transition
            next_state.State = PRESSED;
            next_state.Transitioned = false;
        }
        else 
        { // no button pressed, means our fat fingers have left the button
            next_state.State = IDLE;
            next_state.Transitioned = true;
        }
    }

    return next_state;
}

void init_state (StateAndTransition_t* state) {
    state->State = IDLE;
    state->Transitioned = false;
}

void init_ColorState (ColorState_t* state) {
    state->color_right = 0;
    state->color_left = 0;
    state->color = 0;

    init_state(&state->state_centre);
    init_state(&state->state_up);
    init_state(&state->state_down);
    init_state(&state->state_left);
    init_state(&state->state_right);

}

ColorState_t get_next_Color(const ColorState_t current, const u32 ButtonStatus) {
    ColorState_t next;
    init_ColorState(&next);
    
    next.state_left = find_state(current.state_left, ButtonStatus, BUTTON_LEFT);
    next.state_right = find_state(current.state_right, ButtonStatus, BUTTON_RIGHT);
    next.state_up = find_state(current.state_up, ButtonStatus, BUTTON_UP);
    next.state_down = find_state(current.state_down, ButtonStatus, BUTTON_DOWN);
    next.state_centre = find_state(current.state_centre, ButtonStatus, BUTTON_CENTRE);

    if ((next.state_left.State == PRESSED) && next.state_left.Transitioned) {next.color_right = (current.color_right - 1) % 8;}
    if ((next.state_right.State == PRESSED) && next.state_right.Transitioned) {next.color_right = (current.color_right + 1) % 8;}

    if ((next.state_down.State == PRESSED) && next.state_down.Transitioned) {next.color_left = (current.color_left - 1) % 8;}
    if ((next.state_up.State == PRESSED) && next.state_up.Transitioned) {next.color_left = (current.color_left + 1) % 8;}

    if ((next.state_centre.State == PRESSED) && next.state_centre.Transitioned) {next.color_left = 0; next.color_right = 0;}

    next.color = (next.color_left << 3) + next.color_right;

    return next;
}

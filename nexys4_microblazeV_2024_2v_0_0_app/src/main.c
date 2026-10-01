#include <stdio.h>
#include "xparameters.h"
#include "xgpio.h"
// #include "xtmrctr.h"

#include <xil_types.h>
#include <xstatus.h>
#include "time.h"
#include <stdbool.h>
//Ref:  https://xilinx.github.io/embeddedsw.github.io/gpio/doc/html/api/grocentre__gpio__api.html#ga5b6948513889f043a40494dba1904828

// GPIO_0 Channel Definitions
#define SWITCH_CHANNEL 1
#define LED_CHANNEL 2

// GPIO_1 Channel Definitoins
#define RGB_LED_CHANNEL 1
#define BUTTON_CHANNEL 2

// Button Definitions
#define BUTTON_CENTRE	0x1
#define BUTTON_UP	    0x2
#define BUTTON_LEFT 	0x4
#define BUTTON_RIGHT    0x8
#define BUTTON_DOWN	    0x10



// Define States 
#define IDLE 0
#define PRESSED 1

typedef struct {
    u16 State;
    bool Transitioned;
} StateAndTransition_t;


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

typedef struct {
    u32 color_right; u32 color_left; u32 color;
    StateAndTransition_t state_centre;
    StateAndTransition_t state_left;
    StateAndTransition_t state_right;
    StateAndTransition_t state_up;
    StateAndTransition_t state_down;

} ColorState_t;

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







XGpio Gpio_0, Gpio_1;

// XTmrCtr Timer_LED16_R, Timer_LED16_G, Timer_LED16_B;
// XTmrCtr Timer_LED17_R, Timer_LED17_G, Timer_LED17_B;


int main() {


    // INIT   -----------------------------------------------------------------------------
    int Status_0, Status_1;
    Status_0 = XGpio_Initialize(&Gpio_0, XPAR_AXI_GPIO_0_BASEADDR);
    if (Status_0 != XST_SUCCESS) {
        xil_printf("GPIO 0 Initialisaiton failed!!\r\n");
    }

    Status_1 = XGpio_Initialize(&Gpio_1, XPAR_AXI_GPIO_1_BASEADDR);
    if (Status_1 != XST_SUCCESS) {
        xil_printf("GPIO 1 Initialisation failed!!\r\n");
    }
    XGpio_SetDataDirection(&Gpio_0, SWITCH_CHANNEL, 0xFFFF);
    XGpio_SetDataDirection(&Gpio_0, LED_CHANNEL, 0x0000);

    XGpio_SetDataDirection(&Gpio_1, RGB_LED_CHANNEL, 0x0000);
    XGpio_SetDataDirection(&Gpio_1, BUTTON_CHANNEL, 0xFFFF);

    StateAndTransition_t state_button_centre, state_button_down, state_button_up, state_button_right, state_button_left;
    init_state(&state_button_centre);
    init_state(&state_button_down);
    init_state(&state_button_up);
    init_state(&state_button_right);
    init_state(&state_button_left);

    // int Status_timer_0, Status_timer_1, Status_timer_2, Status_timer_3, Status_timer_4, Status_timer_5;
    
    // Status_timer_0 = XTmrCtr_Initialize(&Timer_LED16_R, XPAR_AXI_TIMER_0_BASEADDR);
    // if (Status_timer_0 != XST_SUCCESS) { xil_printf("Timer 0 Initialisation Failed! \r\n");}

    // Status_timer_1 = XTmrCtr_Initialize(&Timer_LED16_G, XPAR_AXI_TIMER_1_BASEADDR);
    // if (Status_timer_1 != XST_SUCCESS) { xil_printf("Timer 1 Initialisation Failed! \r\n");}
    
    // Status_timer_2 = XTmrCtr_Initialize(&Timer_LED16_B, XPAR_AXI_TIMER_2_BASEADDR);
    // if (Status_timer_2 != XST_SUCCESS) { xil_printf("Timer 2 Initialisation Failed! \r\n");}

    // Status_timer_3 = XTmrCtr_Initialize(&Timer_LED17_R, XPAR_AXI_TIMER_3_BASEADDR);
    // if (Status_timer_3 != XST_SUCCESS) { xil_printf("Timer 3 Initialisation Failed! \r\n");}

    // Status_timer_4 = XTmrCtr_Initialize(&Timer_LED17_G, XPAR_AXI_TIMER_5_BASEADDR);
    // if (Status_timer_4 != XST_SUCCESS) { xil_printf("Timer 5 (5th one) Initialisation Failed! \r\n");}

    // Status_timer_5 = XTmrCtr_Initialize(&Timer_LED17_B, XPAR_AXI_TIMER_6_BASEADDR);
    // if (Status_timer_5 != XST_SUCCESS) { xil_printf("Timer 6 (6th one) Initialisation Failed! \r\n");}

    // ------------------------------------------------------------------------------------


    // Now let's try and get discrete button presses, because typically, if you hold the button down then for each loop the effect will occur
    // it needs to have gone low. for that we need a simple state machine

    u32 finish = 0;
    
    ColorState_t current_color_state;
    init_ColorState(&current_color_state);

    while (1) {
        u32 SwitchStatus = XGpio_DiscreteRead(&Gpio_0, SWITCH_CHANNEL);
        XGpio_DiscreteWrite(&Gpio_0, LED_CHANNEL, SwitchStatus);

        u32 ButtonStatus = XGpio_DiscreteRead(&Gpio_1, BUTTON_CHANNEL);
        
        ColorState_t next_color_state = get_next_Color(current_color_state, ButtonStatus);
        
        XGpio_DiscreteWrite(&Gpio_1, RGB_LED_CHANNEL, next_color_state.color);

        // XTmrCtr_PwmConfigure(XTmrCtr *InstancePtr, u32 PwmPeriod, u32 PwmHighTime)
        if (finish == 1) { return 0; }
    }   

    return 0;
}
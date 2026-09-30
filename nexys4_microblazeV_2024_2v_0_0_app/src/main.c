#include "xparameters.h"
#include "xgpio.h"
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

// LED Colour Definitions
#define RIGHT_RED    0b00000001
#define RIGHT_GREEN  0b00000010
#define RIGHT_BLUE   0b00000100

#define LEFT_RED    0b000001000
#define LEFT_GREEN  0b000010000
#define LEFT_BLUE   0b000100000

// Button Definitions
#define BUTTON_CENTRE	0x1
#define BUTTON_UP	    0x2
#define BUTTON_LEFT 	0x4
#define BUTTON_RIGHT    0x8
#define BUTTON_DOWN	    0x10


/*

state 1: IDLE
state 2: PRESSED

we only trigger the effect ON the transition from IDLE -> PRESSED 

i'll run the same function for EACH button, checking EACH of the state changes

pressed = ButtonStatus & BUTTON_X != 0x0

if pressed and state == IDLE then state <- PRESSED

if !pressed and state == PRESSED then state <- IDLE

*/

// Define States 
#define IDLE 0
#define PRESSED 1
typedef struct {
    u16 State;
    bool Transitioned
} StateAndTransition_t;


StateAndTransition_t find_state(const StateAndTransition_t current, const u32 ButtonStatus, const u32 BUTTON) {
    StateAndTransition_t new;
    if (current.State == IDLE) 
    {   
        if ((ButtonStatus & BUTTON) != 0) 
        { // then we have a button press
            new.State = PRESSED;
            new.Transitioned = true;
        }
        else 
        { // no transition
            new.State = IDLE;
            new.Transitioned = false;
        }
    }

    if (current.State == PRESSED)
    {
        if ((ButtonStatus & BUTTON) != 0) 
        { // button pressed, while it's already moved to pressed, just a fat finger so no transition
            new.State = PRESSED;
            new.Transitioned = false;
        }
        else 
        { // no button pressed, means our fat fingers have left the button
            new.State = IDLE;
            new.Transitioned = true;
        }
    }

    return new;
}

void init_state (StateAndTransition_t* state) {
    state->State = IDLE;
    state->Transitioned = false;
}




XGpio Gpio_0, Gpio_1;


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
    // ------------------------------------------------------------------------------------


    // Now let's try and get discrete button presses, because typically, if you hold the button down then for each loop the effect will occur
    // it needs to have gone low. for that we need a simple state machine

    u32 finish = 0;
    
    u32 Color_right_led = 0;
    u32 Color_left_led = 0;
    while (1) {
        u32 SwitchStatus = XGpio_DiscreteRead(&Gpio_0, SWITCH_CHANNEL);
        XGpio_DiscreteWrite(&Gpio_0, LED_CHANNEL, SwitchStatus);

        u32 ButtonStatus = XGpio_DiscreteRead(&Gpio_1, BUTTON_CHANNEL);

        // Left and Right is for right LED
        StateAndTransition_t new_state_left = find_state(state_button_left, ButtonStatus, BUTTON_LEFT);
        state_button_left = new_state_left;

        if ((state_button_left.State == PRESSED) && state_button_left.Transitioned) {Color_right_led = (Color_right_led - 1) % 8;}

        StateAndTransition_t new_state_right = find_state(state_button_right, ButtonStatus, BUTTON_RIGHT);
        state_button_right = new_state_right;

        if ((state_button_right.State == PRESSED) && state_button_right.Transitioned) {Color_right_led = (Color_right_led + 1) % 8;}

        // Up and Down is for left LED
        StateAndTransition_t new_state_down = find_state(state_button_down, ButtonStatus, BUTTON_DOWN);
        state_button_down = new_state_down;

        if ((state_button_down.State == PRESSED) && state_button_down.Transitioned) {Color_left_led = (Color_left_led - 1) % 8;}

        StateAndTransition_t new_state_up = find_state(state_button_up, ButtonStatus, BUTTON_UP);
        state_button_up = new_state_up;

        if ((state_button_up.State == PRESSED) && state_button_up.Transitioned) {Color_left_led = (Color_left_led + 1) % 8;}



        // Centre button is a reset!
        StateAndTransition_t new_state_centre = find_state(state_button_centre, ButtonStatus, BUTTON_CENTRE);
        state_button_centre = new_state_centre;

        if ((state_button_centre.State == PRESSED) && state_button_centre.Transitioned) {Color_left_led = 0; Color_right_led = 0;}

        // Combine the two colors
        u32 Color = (Color_left_led << 3) + Color_right_led;

        XGpio_DiscreteWrite(&Gpio_1, RGB_LED_CHANNEL, Color);



        if (finish == 1) { return 0; }
    }   


}
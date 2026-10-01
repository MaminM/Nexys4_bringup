#include <stdio.h>
#include "xparameters.h"
#include "xtmrctr.h"
#include "xgpio.h"
// #include "xtmrctr.h"
#include "one_bit_led_state_machine.h"
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

XGpio Gpio_0, Gpio_1;

XTmrCtr Timer_LED16_R, Timer_LED16_G, Timer_LED16_B;
XTmrCtr Timer_LED17_R, Timer_LED17_G, Timer_LED17_B;

typedef struct {
    u32 red;
    u32 green;
    u32 blue;
    u32 max_strength;
}  ColorStrength_t;

void init_ColorStrength(ColorStrength_t *color_strength) {
    color_strength->red = 0;
    color_strength->green = 0;
    color_strength->blue = 0;
    color_strength->max_strength = 0xFF;
} 

/*
            What I want to do, is have the ButtonState (which corresponds to 16 bits, i.e. two colors)
            I want to only write the first 8 bits as the strength of LED16_R, then have that run on PWM
            
            This is just to verify
            
            The current challenge is that I don't know how to set up the PWM!

/*


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


    int Status_led16_R, Status_led16_G, Status_led16_B, Status_led17_R, Status_led17_G, Status_led17_B;

    Status_led16_R = XTmrCtr_Initialize(&Timer_LED16_R, XPAR_XTMRCTR_0_BASEADDR);
    Status_led16_G = XTmrCtr_Initialize(&Timer_LED16_G, XPAR_AXI_TIMER_1_BASEADDR);
    Status_led16_B = XTmrCtr_Initialize(&Timer_LED16_B, XPAR_XTMRCTR_2_BASEADDR);

    Status_led17_R = XTmrCtr_Initialize(&Timer_LED17_R, XPAR_XTMRCTR_3_BASEADDR);
    Status_led17_G = XTmrCtr_Initialize(&Timer_LED17_G, XPAR_XTMRCTR_5_BASEADDR);
    Status_led17_B = XTmrCtr_Initialize(&Timer_LED17_B, XPAR_AXI_TIMER_6_BASEADDR);

    if (Status_led16_R+ Status_led16_G+ Status_led16_B+ Status_led17_R+ Status_led17_G+ Status_led17_B != XST_SUCCESS)
    {
        xil_printf("One of the Timer Initialisations Failed\r\n");
        if (Status_led17_B != XST_SUCCESS) {xil_printf("it's the second Blue light, must be the weird AXI_TIMER name\r\n");}
    }

    // END OF INIT   ----------------------------------------------------------------------
    u32 finish = 0;

    // now let's look at PWM
    // clock is 100MHz, 1kHz is too fast for the human eye. 
    
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
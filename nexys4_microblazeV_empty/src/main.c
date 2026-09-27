#include "xparameters.h"
#include "xgpio.h"
#include <xstatus.h>
//Ref:  https://xilinx.github.io/embeddedsw.github.io/gpio/doc/html/api/group__gpio__api.html#ga5b6948513889f043a40494dba1904828


// Extracting relevant params from xparameters.h
#define GPIO_DEVICE_ID   XPAR_GPIO_0_DEVICE_ID
#define GPIO_BASEADDR   XPAR_XGPIO_0_BASEADDR
// for easy coding
#define LED_CHANNEL 1
#define SWITCH_CHANNEL 2

XGpio Gpio;



int main () {
    int Status;
    Status = XGpio_Initialize(&Gpio, GPIO_BASEADDR);
    if (Status != XST_SUCCESS) {
        xil_printf("GPIO Initialisation failed!\r\n");
        return XST_FAILURE;
    }
    
    
    XGpio_SetDataDirection(&Gpio, LED_CHANNEL, 0x0); // outputs
    XGpio_SetDataDirection(&Gpio, SWITCH_CHANNEL, 0xFFFF); // inputs
    
    while (1) {
        u32 SwitchStatus = XGpio_DiscreteRead(&Gpio, SWITCH_CHANNEL);
        XGpio_DiscreteWrite(&Gpio, LED_CHANNEL, SwitchStatus);
    }
    
    return 0;
}
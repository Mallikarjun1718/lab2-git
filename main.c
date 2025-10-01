#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"

#define red_led (1<<1)
#define blue_led (1<<2)



void gpio_portf_interrupt(void){
    GPIO_PORTF_ICR_R=1;//isr is finished here
    GPIO_PORTF_DATA_R^= blue_led;
    //GPIO_PORTF_ICR_R=1;isr is again called and toggles the led.
}

void timer (void){
    GPIO_PORTF_DATA_R^= red_led;
}
int main(void){
    SYSCTL_RCGC2_R   |= 0x00000020;      // ENABLE CLOCK TO GPIOF
    GPIO_PORTF_LOCK_R = 0x4C4F434B;      // UNLOCK COMMIT REGISTER
    GPIO_PORTF_CR_R   = 0x0F;            // MAKE PORTF0 CONFIGURABLE
    GPIO_PORTF_DEN_R  = 0x0F;            // SET PORTF PINS 4 PIN
    GPIO_PORTF_DIR_R  = 0x0E;            // SET PORTF4 PIN AS INPUT USER SWITCH PIN
    GPIO_PORTF_PUR_R  = 0x11;            // PORTF4 IS PULLED UP
    GPIO_PORTF_DATA_R = 0x00;

    NVIC_ST_RELOAD_R=0xFFFFFF;
    NVIC_ST_CTRL_R=(1<<2 | 1<<1 | 1);

    //GPIO interrupt mask
    GPIO_PORTF_IM_R = 0;
    GPIO_PORTF_IS_R = 0;//edge triggered
    GPIO_PORTF_IEV_R =1;//falling edge as when pressed it goes from 1 to 0
    GPIO_PORTF_ICR_R=1;
    GPIO_PORTF_IM_R = 1;

    //NVIC

    NVIC_EN0_R|=1<<30;

    while(1){
        //do nothing
    }

}



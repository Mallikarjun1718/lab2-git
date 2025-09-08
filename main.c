#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"

int main (void){
    SYSCTL_RCGC2_R   |= 0x00000020;      // ENABLE CLOCK TO GPIOF
    GPIO_PORTF_LOCK_R = 0x4C4F434B;      // UNLOCK COMMIT REGISTER
    GPIO_PORTF_CR_R   = 0x1F;            // MAKE PORTF0 CONFIGURABLE
    GPIO_PORTF_DEN_R  = 0x1F;            // SET PORTF PINS 4 PIN
    GPIO_PORTF_DIR_R  = 0x0E;            // SET PORTF4 PIN AS INPUT USER SWITCH PIN
    GPIO_PORTF_PUR_R  = 0x11;            // PORTF4 IS PULLED UP
    GPIO_PORTF_DATA_R = 0x02;            // LED OFF

    NVIC_ST_RELOAD_R=0x40FFFF;
    NVIC_ST_CTRL_R=(1<<2);
    NVIC_ST_CTRL_R|=1;
    while(1){
        if((NVIC_ST_CTRL_R & 0x10000)==0x10000){
            GPIO_PORTF_DATA_R ^=0x02;
            NVIC_ST_CTRL_R^=1;
            NVIC_ST_CURRENT_R=0;
            NVIC_ST_CTRL_R|=1;
        }
    }
}


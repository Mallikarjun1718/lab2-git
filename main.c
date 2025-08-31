#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"

int main(void)
{
    SYSCTL_RCGC2_R |=   0x00000020;      // ENABLE CLOCK TO GPIOF
    GPIO_PORTF_LOCK_R = 0x4C4F434B;      // UNLOCK COMMIT REGISTER
    GPIO_PORTF_CR_R   = 0x1F;            // MAKE PORTF0 CONFIGURABLE
    GPIO_PORTF_DEN_R  = 0x1F;
    GPIO_PORTF_DIR_R  = 0x06;
    GPIO_PORTF_PUR_R  = 0x11;
    GPIO_PORTF_DATA_R = 0x00;

    while(1){
        if ((GPIO_PORTF_DATA_R & 0x11)==0 ){
            GPIO_PORTF_DATA_R = 0x06;
        }
        else if((GPIO_PORTF_DATA_R & 0x01)==0){
            GPIO_PORTF_DATA_R = 0x02;
        }
        else if((GPIO_PORTF_DATA_R & 0x10)==0){
            GPIO_PORTF_DATA_R = 0x04;
        }
        else{
            GPIO_PORTF_DATA_R = 0x00;
        }
    }
}


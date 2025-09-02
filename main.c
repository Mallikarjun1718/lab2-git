#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"

#define RED_LED (1<<1)
#define BLUE_LED (1<<2)
#define GREEN_LED (1<<3)

int main(void)
{
    SYSCTL_RCGC2_R |=   0x00000020;      // ENABLE CLOCK TO GPIOF
    GPIO_PORTF_LOCK_R = 0x4C4F434B;      // UNLOCK COMMIT REGISTER
    GPIO_PORTF_CR_R   = 0x1F;            // MAKE PORTF0 CONFIGURABLE
    GPIO_PORTF_DEN_R  = 0x1F;            // SET PORTF PINS 4 PIN
    GPIO_PORTF_DIR_R  = 0x0E;            // SET PORTF4 PIN AS INPUT USER SWITCH PIN
    GPIO_PORTF_PUR_R  = 0x11;            // PORTF4 IS PULLED UP
    GPIO_PORTF_DATA_R = 0x00;            // LED OFF

    while(1)
    {
        if((GPIO_PORTF_DATA_R & 0x11)==0x01)
        {
            delay(10000);
            GPIO_PORTF_DATA_R |= RED_LED ;
        }
        else if((GPIO_PORTF_DATA_R & 0x11)==0x10)
        {
            delay(10000);
            GPIO_PORTF_DATA_R |= BLUE_LED;
        }
        else if((GPIO_PORTF_DATA_R & 0x11)==0x00)
        {
            delay(10000);
            GPIO_PORTF_DATA_R |= GREEN_LED;
        }
        else
        {
            delay(10000);
            GPIO_PORTF_DATA_R = 0x00;
        }
    }
}


void delay(int ms){
    int i,j,count=100;
    for(i=0;i<ms;i++){
        for(j=0;j<ms;j++){
            if(count==0){
                break;
                }
            else{
                count--;
            }
        }
    }
}

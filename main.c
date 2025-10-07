#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"


void main(void){
    int count=0,i;
    SYSCTL_RCGC2_R   |= 0x00000020;      // ENABLE CLOCK TO GPIOF
    SYSCTL_RCGCTIMER_R |= (1 << 1);   // Enable Timer0 clock
    GPIO_PORTF_LOCK_R = 0x4C4F434B;      // UNLOCK COMMIT REGISTER
    GPIO_PORTF_CR_R   = 0x1F;            // MAKE PORTF0 CONFIGURABLE
    GPIO_PORTF_DEN_R  = 0x1F;            // SET PORTF PINS 4 PIN
    GPIO_PORTF_DIR_R  = 0x0E;            // SET PORTF4 PIN AS INPUT USER SWITCH PIN
    GPIO_PORTF_PUR_R  = 0x11;            // PORTF4 IS PULLED UP
    GPIO_PORTF_DATA_R = 0x00;

    GPIO_PORTF_AFSEL_R = 0X04;
    GPIO_PORTF_PCTL_R = 0X700;

    TIMER1_CTL_R = 0X00;
    TIMER1_CFG_R = 0X04;
    TIMER1_TAMR_R = 0X0A;

    TIMER1_CTL_R &= ~(1<<6);
    TIMER1_TAPR_R = 0X0;

    TIMER1_TAILR_R = 0X140;
    TIMER1_TAMATCHR_R = 0XA0;
    TIMER1_CTL_R |= 0X01;

    while(1){
        if((GPIO_PORTF_DATA_R & 0x01)== 0){
            if(TIMER1_TAMATCHR_R<TIMER1_TAILR_R-0xF)
                TIMER1_TAMATCHR_R += 0X0F;
            for(i=0;i<500000;i++);
        }
        if((GPIO_PORTF_DATA_R & 0x10)== 0){
            if(TIMER1_TAMATCHR_R > 0x0F)
                TIMER1_TAMATCHR_R -= 0X0F;
            for(i=0;i<500000;i++);
        }
    }
}




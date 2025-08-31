#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"

int main(void)
{
    SYSCTL_RCGC2_R |=   0x00000020;      // ENABLE CLOCK TO GPIOF
    GPIO_PORTF_LOCK_R = 0x4C4F434B;      // UNLOCK COMMIT REGISTER
    GPIO_PORTF_CR_R   = 0x1F;            // MAKE PORTF0 CONFIGURABLE
    GPIO_PORTF_DEN_R  = 0x0F;
    GPIO_PORTF_DIR_R  = 0x0E;
    GPIO_PORTF_PUR_R  = 0x01;
    GPIO_PORTF_DATA_R = 0X00;
    int count=1;
    while(1){
        switch((GPIO_PORTF_DATA_R & 0x01)==0){
            case(0):
                    count=1;
                    continue;

            case (1):
                    if((GPIO_PORTF_DATA_R & 0x02)!=0 & count==1){
                        delay(10000);
                        GPIO_PORTF_DATA_R = 0x08;
                    }
                    else if((GPIO_PORTF_DATA_R  & 0x08)!=0 & count==1){
                        delay(10000);
                        GPIO_PORTF_DATA_R = 0x04;
                    }
                    else if( count==1){
                        delay(10000);
                        GPIO_PORTF_DATA_R =0x02;
                    }
                    count=0;
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



#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"

int series_sum(int k){
    volatile int a,b,c,d,e;
    int temp_sum=0;
    if(k==0){
        return 0;

    }
    else{
        temp_sum=series_sum(k-1);
        temp_sum+=k;
        return temp_sum;
    }
}
void main(void)
{
    int sum;
    int k;
    k=31;
    sum=series_sum(k);
	while(1) ;
}

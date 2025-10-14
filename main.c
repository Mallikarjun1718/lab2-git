//#include "fp.h"
#include<stdio.h>
#include <stdint.h>
#include "tm4c123gh6pm.h"

struct
{
    uint32_t u;     // 32-bit IEEE format computed by fadd
    float f;        // reference result computed by c = a + b
} buf[0x100];
int index;


uint32_t fadd(uint32_t a, uint32_t b){
    int exp1=0,exp2=0,i,rem,a1,b1,mantisa;
    a1=a;
    b1=b;
    a=0,b=0;
    uint32_t result=0;
    for(i=0;i<23;i++){
        rem=a1%2;
        a1=a1/2;
        if((i==22)){
            exp1=a1-127;
        }
        if(i<23){
            a=a+rem*(1<<i);
        }
    }
    for(i=0;i<23;i++){
        rem=b1%2;
        b1=b1/2;
        if((i==22)){
            exp2=b1-127;
        }
        if(i<23){
            b=b+rem*(1<<i);
        }
    }

    if(exp1>exp2){
        b=b+(1<<23);
        b=(b>>(exp1-exp2));
        if(a+b>((1<<23)-1)){
            //printf("hello");
            exp1+=1;
            mantisa=a+b;
            mantisa=(mantisa & 0X7FFFFF);
            mantisa=mantisa>>1;
        }
        else{
            mantisa=a+b;
        }
        result=0;
        result=result<<31;
        result=result+exp1+127;
        result=result<<23;
        result=result+mantisa;
    }
    else{
        //a=a+(1<<23)
        if((exp2-exp1)==0){
            exp2+=1;
            mantisa=a+b;
            mantisa=mantisa>>1;
        }
        else{
            a=a+(1<<23);
            a=(a>>(exp2-exp1));
            if(a+b>((1<<23)-1)){
                exp2+=1;
                mantisa=a+b;
                mantisa=(mantisa && 0X7FFFFF);
                mantisa=mantisa>>1;
            }
            else{
                mantisa=a+b;
            }
        }
        result=0;
        result=result<<31;
        result=result+exp2+127;
        result=result<<23;
        result=result+mantisa;
    }
    printf("0x%08X\n",result);
    return result;
}



void fadd_test(float a, float b)
{
    union
    {
        uint32_t u;     // access as 32-bit raw bits
        float f;        // access as a floating-point number
    } A, B, C;

    float c;

    A.f = a;
    B.f = b;

    C.u = fadd(A.u, B.u);       // output of asm code
    c = a + b;                  // reference output by C code

    if (index < 0x100)
    {
        buf[index].u = C.u;     // asm result
        buf[index].f = c;       // C result
        index++;
    }

    return;
}

int main(void)
{
    fadd_test(100.0f, 0.25f);       // 100.25f  (0x42C88000)
    fadd_test(1.5f, 1.5f);          // 3.0f     (0x40400000)
    fadd_test(2.75f, 1.5f);         // 4.25f    (0x40880000)
    fadd_test(1024.0f, 1.0f);       // 1025.0f  (0x44802000)
    fadd_test(1.0f, 0.125f);        // 1.125f   (0x3F900000)
    fadd_test(65536.0f, 256.0f);    // 65792.0f (0x47808000)

    //while (1);

    return 0;
}


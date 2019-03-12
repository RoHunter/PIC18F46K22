#define _XTAL_FREQ  64000000
#include <xc.h>
#include "bit_config.h"
#include "config.h"
#include <math.h>
#include <stdio.h>

#define inainte_var 1  
#define inapoi_var  2
#define negru LATDbits.LD6
#define maro LATDbits.LD7
#define galben LATDbits.LD5
#define roz LATDbits.LD4
unsigned int cnt=1;

void stepper_move(unsigned directie, unsigned pasi)
{
    if(directie==inainte_var)
    {
       if(cnt<=pasi)
    {
    negru=0;
    maro=1;
    galben=0;
    roz=1;
    __delay_ms(5);
    
    negru=0;
    maro=1;
    galben=1;
    roz=0;   
    __delay_ms(5);
    
    negru=1;
    maro=0;
    galben=1;
    roz=0;
     __delay_ms(5);
 
    negru=1;
    maro=0;
    galben=0;
    roz=1;
    __delay_ms(500);
    
    cnt++;
       }
       
    cnt=0;

    }
    
    if(directie==inapoi_var)
    {
    negru=1;
    maro=0;
    galben=0;
    roz=1;
    __delay_ms(50);
    
    negru=1;
    maro=0;
    galben=1;
    roz=0;
     __delay_ms(50);
     
    negru=0;
    maro=1;
    galben=1;
    roz=0;   
    __delay_ms(50);
    
    negru=0;
    maro=1;
    galben=0;
    roz=1;
    __delay_ms(50);
 
   
   
    }

}
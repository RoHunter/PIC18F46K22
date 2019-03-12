#define _XTAL_FREQ  64000000
#include <xc.h>
#include "bit_config.h"
#include "config.h"
#include "pwm_con.h"
#include <math.h>
#include <stdio.h>
#include "adc.h"
#include "MPPT.h"
#define CCPR1L boost;
#define CCPR2L buck;

void main(void)
{
    
    config();
    pwm_config();
    adc_config();
    init_io_display();
    int port;
    Lcd_Clear();     
      
         
         
         
    while(1)
    {

        if(port==0);
        {
            read_Uout();
            port=1;
            __delay_ms(100);
            ADRESH=0X00;
            __delay_ms(100);
         }
    
        if(port==1);
        {   
            read_Iout();
            port=2;
            __delay_ms(100);
            ADRESH=0X00;
            __delay_ms(100);
        }
        
        if(port==2);
        {   
           read_Uin();
            port=0;
            __delay_ms(100);
            ADRESH=0X00;
            __delay_ms(100);
        }

//Power=Uout*Iout;

    }
}
#include <xc.h>
#include "config.h"
#include "usart_pic16.h" 
    void adc_U(void)
    {
    

    ADCON0=0b00000011;  //RA0

    }
    
    void adc_A(void)
    {
    

    ADCON0=0b00000111;  //RA1

    }
    
 

/*
 * File:   MPPT.c
 * Author: Silviu
 *
 * Created on March 12, 2019, 12:45 PM
 */


#include <xc.h>
#include "bit_config.h"
#include "config.h"

float rez_adc_A,tens_A,Iout,rez_adc_U,tens,Uout,Uin;

void read_Iout(void)
{
    ADCON0=0b00001011;
    __delay_ms(10);
    ADCON0bits.GO=1;
    __delay_ms(100);
    rez_adc_A=ADRESH;
    tens_A=rez_adc_A*0.0181372549019608;
    Iout=tens_A;
}



void read_Uout(void)
{
    ADCON0=0b00000111;
    __delay_ms(10);
    ADCON0bits.GO=1;
    __delay_ms(100);
    rez_adc_U=ADRESH;
    tens=rez_adc_U*0.01953125;
    Uout=tens/0.25;

}
void read_Uin(void)
{
    ADCON0=0b00001111;
    __delay_ms(10);
    ADCON0bits.GO=1;
    __delay_ms(100);
    rez_adc_U=ADRESH;
    tens=rez_adc_U*0.01953125;
     Uin=tens/0.2;
}
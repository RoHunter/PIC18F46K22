/*
 * File:   MPPT.c
 * Author: Silviu
 *
 * Created on March 12, 2019, 12:45 PM
 */


#include <xc.h>
#include "bit_config.h"
#include "config.h"
#include <stdio.h>

char str_V[8],str_A[8],str_P[8];
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
    Lcd_Set_Cursor(2,1);
    Lcd_Write_String("I=");
    sprintf(str_A, "%.2f", Iout);
    Lcd_Set_Cursor(2,3);
    Lcd_Write_String(str_A);
    Lcd_Write_String(" A");
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
    Lcd_Set_Cursor(1,1);
    Lcd_Write_String("U=");
    sprintf(str_V, "%.2f", Uout);
    Lcd_Set_Cursor(1,3);
    Lcd_Write_String(str_V);
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
    Lcd_Set_Cursor(1,9);
    Lcd_Write_String("Ui=");
    sprintf(str_V, "%.2f", Uin);
    Lcd_Set_Cursor(1,12);
    Lcd_Write_String(str_V);
    Lcd_Write_String(" V");
}
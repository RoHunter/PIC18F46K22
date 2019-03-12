/*
 * File:   afis_dispay.c
 * Author: Silviu
 *
 * Created on March 12, 2019, 1:05 PM
 */


#include <xc.h>
#include "bit_config.h"
#include "config.h"
#include "afis_display.h"

char str_V[8],str_A[8],str_P[8];
float tens,curent;

void write_Uout()
{
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("U=");
        sprintf(str_V, "%.2f", tens);
        Lcd_Set_Cursor(1,3);
        Lcd_Write_String(str_V);
}

void write_Uin()
{
        Lcd_Set_Cursor(1,9);
        Lcd_Write_String("Ui=");
        sprintf(str_V, "%.2f", tens);
        Lcd_Set_Cursor(1,12);
        Lcd_Write_String(str_V);
         Lcd_Write_String(" V");
}
//
void write_Iout(void)
{
        Lcd_Set_Cursor(2,1);
        Lcd_Write_String("I=");
        sprintf(str_A, "%.2f", curent);
        Lcd_Set_Cursor(2,3);
        Lcd_Write_String(str_A);
         Lcd_Write_String(" A");
}
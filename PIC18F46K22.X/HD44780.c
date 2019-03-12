#define _XTAL_FREQ 32000000
#include <xc.h>
#include "HD44780.h"
#include "bit_config.h"
#include <stdio.h>
#include <string.h>
#define data_port LATC
#define RS LATAbits.LATA6
#define E LATAbits.LATA7

void init_hd44780()
{
    RS=0;

    
    
    E=1;
    data_port=0b00000001;//clear display
    __delay_ms(10);
    E=0;
    
   
     
     E=1;
    data_port=0b00001110;//display on, cursor on
    __delay_ms(10);
     E=0;
   
    

}

void write_char_hd44780(char chr)
{
    RS=1;
    E=1;
    data_port=chr;
    __delay_ms(10);
    RS=0;
    E=0;
    
   
}

void write_string_hd44780(char *string,unsigned rand)
{
    
    for(int i=0;i<strlen(string);i++)
    {
    RS=1;
    E=1;
    data_port=string[i];
    __delay_ms(10);
    RS=0;
    E=0;
    
    }


}

void row_sel_hd44780(unsigned row)
{

    RS=0;
    E=1;
    data_port=0xc0;//row 2
    __delay_ms(10);
    E=0;


}
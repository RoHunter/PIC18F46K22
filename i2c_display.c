/*
 * File:   i2c.c
 * Author: georg
 *
 * Created on August 28, 2016, 3:25 PM
 */

#define adress 0x70//70
#define RS0 0x00//00
#define RS1 0x01//01
#define EN0 0x00//00 
#define EN1 0x04//04
#define BGL 0x00
#define _XTAL_FREQ 64000000
#include <xc.h>
#include "i2c_display.h"

unsigned int data;

void Lcd_Port(char data)
{   I2C_Master_Start();
    I2C_Write_Display(adress);
	I2C_Write_Display(data);
    I2C_Master_Stop();
}
void Lcd_Cmd(char a)
{
    int buff;
    a=a<<4;
    
	//RS = 0;            
    Lcd_Port(0x00 || RS0 || EN0 || BGL);
    
	Lcd_Port(a);
    
	//EN  = 1;             
    buff=a | RS0 | EN1 | BGL;
    Lcd_Port(buff);
        __delay_ms(4);
    //EN  = 0;             
    buff=a | RS0 | EN0 | BGL;    
    Lcd_Port(buff);    
}

void Lcd_Clear()
{
	Lcd_Cmd(0);
	Lcd_Cmd(1);
}

void Lcd_Set_Cursor(char a, char b)
{
	char temp,z,y;
	if(a == 1)
	{
	  temp = 0x80 + b - 1;
		z = temp>>4;
		y = temp & 0x0F;
		Lcd_Cmd(z);
		Lcd_Cmd(y);
	}
	else if(a == 2)
	{
		temp = 0xC0 + b - 1;
		z = temp>>4;
		y = temp & 0x0F;
		Lcd_Cmd(z);
		Lcd_Cmd(y);
	}
}

void Lcd_Init()
{
  Lcd_Port(0x00);
   __delay_ms(20);
  Lcd_Cmd(0x03);
	__delay_ms(5);
  Lcd_Cmd(0x03);
	__delay_ms(11);
  Lcd_Cmd(0x03);
  /////////////////////////////////////////////////////
  Lcd_Cmd(0x02);
  Lcd_Cmd(0x02);
  Lcd_Cmd(0x08);
  Lcd_Cmd(0x00);
  Lcd_Cmd(0x0C);
  Lcd_Cmd(0x00);
  Lcd_Cmd(0x06);
}

void Lcd_Write_Char(char a)
{
   char temp,y;
   temp = a&0x0F;
   temp=temp<<4;
   y = a&0xF0;

 //  RS = 1;             
   Lcd_Port(0x00 | RS1 | EN0 | BGL);
   Lcd_Port(y);             //Data transfer
   //EN = 1;
   Lcd_Port(y | RS1 | EN1 | BGL);
   __delay_us(40);
   //EN = 0;
   Lcd_Port(y | RS1 | EN0 | BGL);
   Lcd_Port(temp);
   
   //EN = 1;
   Lcd_Port(temp | RS1 | EN1 | BGL);
   __delay_us(40);
   //EN = 0;
   Lcd_Port(temp | RS1 | EN0 | BGL);
}

void Lcd_Write_String(char *a)
{
	int i;
	for(i=0;a[i]!='\0';i++)
	   Lcd_Write_Char(a[i]);
}

void Lcd_Shift_Right()
{
	Lcd_Cmd(0x01);
	Lcd_Cmd(0x0C);
}

void Lcd_Shift_Left()
{
	Lcd_Cmd(0x01);
	Lcd_Cmd(0x08);
}

void Cursor_On()
{
Lcd_Cmd(0x00);
Lcd_Cmd(0x0F);        
        }

void Cursor_Off()
{
Lcd_Cmd(0x00);
Lcd_Cmd(0x0C);        
        }

void Cursor_Left()
{
Lcd_Cmd(0x01);
Lcd_Cmd(0x00);   
}

void Cursor_Right()
{
Lcd_Cmd(0x02);
Lcd_Cmd(0x04);   
}




/////////////////////////////I2C/////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void I2C_Master_Init(const unsigned long c)
{
    SSP1CON1 = 0b00101000;
    SSP1CON2 = 0x00;
    SSP1ADD = (_XTAL_FREQ/(4*c))-1;
    SSP1STAT = 0x00;
    TRISCbits.TRISC3=1;
    TRISCbits.TRISC4=1;
}
////////////////////////////////////////////////////////////////////////////////
void I2C_Master_Wait()
{
   while ((SSP1STAT & 0x04) || (SSP1CON2 & 0x1F));
   // while(PIR1bits.SSPIF==0);
  //  PIR1bits.SSPIF=1;
}
////////////////////////////////////////////////////////////////////////////////
void I2C_Master_Start()
{
    I2C_Master_Wait();
    SSP1CON2bits.SEN = 1;
}
////////////////////////////////////////////////////////////////////////////////
void I2C_Master_RepeatedStart()
{
    I2C_Master_Wait();
    SSP1CON2bits.RSEN = 1;
}
////////////////////////////////////////////////////////////////////////////////
void I2C_Master_Stop()
{
    I2C_Master_Wait();
    SSP1CON2bits.PEN = 1;
}
////////////////////////////////////////////////////////////////////////////////
void I2C_Master_Write(unsigned d)
{
    I2C_Master_Wait();
    SSP1BUF = d;
}
////////////////////////////////////////////////////////////////////////////////
void I2C_Write_Display(unsigned d)
{
    I2C_Master_Wait();
    SSP1BUF = d;
}
////////////////////////////////////////////////////////////////////////////////
unsigned short I2C_Master_Read(unsigned short a)
{
    unsigned short temp;
    I2C_Master_Wait();
    SSP1CON2bits.RCEN = 1;
    I2C_Master_Wait();
    temp = SSPBUF;
    I2C_Master_Wait();
    SSP1CON2bits.ACKDT = (a)?0:1;
    SSP1CON2bits.ACKEN = 1;
    return temp;
}
////////////////////////////////////////////////////////////////////////////////

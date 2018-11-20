/******************************************************************************

 Serial communication library for PIC16F series MCUs.

 Compiler: Microchip XC8 v1.12 (http://www.microchip.com/xc)

 Version: 1.0 (21 July 2013)

 MCU: PIC16F877A
 Frequency: 20MHz

                                     NOTICE

NO PART OF THIS WORK CAN BE COPIED, DISTRIBUTED OR PUBLISHED WITHOUT A
WRITTEN PERMISSION FROM EXTREME ELECTRONICS INDIA. THE LIBRARY, NOR ANY PART
OF IT CAN BE USED IN COMMERCIAL APPLICATIONS. IT IS INTENDED TO BE USED FOR
HOBBY, LEARNING AND EDUCATIONAL PURPOSE ONLY. IF YOU WANT TO USE THEM IN
COMMERCIAL APPLICATION PLEASE WRITE TO THE AUTHOR.


WRITTEN BY:
AVINASH GUPTA
me@avinashgupta.com

*******************************************************************************/
#include <stdint.h>
#include <xc.h>
#include "config.h"
#include "usart_pic16.h"

void USARTInit(uint16_t baud_rate)
{
    //Setup queue
    UQFront=UQEnd=-1;
        
    //SPBRG
    switch(baud_rate)
    {
     case 9600:
        SPBRG1=207;//103
        break;
     case 19200:
        SPBRG1=51;
        break;
     case 28800:
        SPBRG1=42;
        break;
     case 33600:
        SPBRG1=36;
        break;
    }
    //TXSTA
    TXSTA1bits.TX9=0;  //8 bit transmission
    TXSTA1bits.TXEN=1; //Transmit enable
    TXSTA1bits.SYNC=0; //Async mode
    TXSTA1bits.BRGH=0; //High speed baud rate
//    TXSTA1=0b00100000;
//    TXSTA1bits.SYNC=0;
//    TXSTA1bits.TXEN=1;
//    RCSTA1bits.SPEN=1;
//    BAUDCON1=0b00000000;
//    SPBRG1=51;

    //RCSTA
    RCSTA1bits.SPEN=1;   //Serial port enabled
    RCSTA1bits.RX9=0;    //8 bit mode
    RCSTA1bits.CREN=1;   //Enable receive
    RCSTA1bits.ADDEN=0;  //Disable address detection
   

//    //Receive interrupt
//    PIE1bits.RC1IE=0;
//    PEIE=0;

    ei();
}

void USARTWriteChar(char ch)
{
  while(!PIR1bits.TXIF);

  TXREG=ch;
}

void USARTWriteString(const char *str)
{
  while(*str!='\0')
  {
      USARTWriteChar(*str);
      str++;
  }
}

void USARTWriteLine(const char *str)
{
    USARTWriteChar('\r');//CR
    USARTWriteChar('\n');//LF

    USARTWriteString(str);
}

void USARTHandleRxInt()
{
 if(PORTBbits.RB1==1)
    PORTBbits.RB1=0;
  else
    PORTBbits.RB1=1;
  
    //Read the data
    char data=RCREG;

    //Now add it to q
    if(((UQEnd==RECEIVE_BUFF_SIZE-1) && UQFront==0) || ((UQEnd+1)==UQFront))
    {
        //Q Full
	UQFront++;
	if(UQFront==RECEIVE_BUFF_SIZE) UQFront=0;
    }

    if(UQEnd==RECEIVE_BUFF_SIZE-1)
        UQEnd=0;
    else
	UQEnd++;

    URBuff[UQEnd]=data;

    if(UQFront==-1) UQFront=0;
    
}

char USARTReadData()
{
    char data;

    //Check if q is empty
    if(UQFront==-1)
	return 0;

    data=URBuff[UQFront];

    if(UQFront==UQEnd)
    {
        //If single data is left
	//So empty q
	UQFront=UQEnd=-1;
    }
    else
    {
	UQFront++;

	if(UQFront==RECEIVE_BUFF_SIZE)
            UQFront=0;
    }

    return data;
}

uint8_t USARTDataAvailable()
{
    if(UQFront==-1) return 0;
    if(UQFront<UQEnd)
	return(UQEnd-UQFront+1);
    else if(UQFront>UQEnd)
	return (RECEIVE_BUFF_SIZE-UQFront+UQEnd+1);
    else
	return 1;
}

void USARTWriteInt(int16_t val, int8_t field_length)
{
    char str[5]={0,0,0,0,0};
    int8_t i=4,j=0;

    //Handle negative integers
    if(val<0)
    {
        USARTWriteChar('-');   //Write Negative sign
        val=val*-1;     //convert to positive
    }
    else
    {
        USARTWriteChar(' ');
    }

    if(val==0 && field_length<1)
    {
        USARTWriteChar('0');
        return;
    }
    while(val)
    {
        str[i]=val%10;
        val=val/10;
        i--;
    }

    if(field_length==-1)
        while(str[j]==0) j++;
    else
        j=5-field_length;


    for(i=j;i<5;i++)
    {
        USARTWriteChar('0'+str[i]);
    }
}

void USARTGotoNewLine()
{
    USARTWriteChar('\r');//CR
    USARTWriteChar('\n');//LF
}

void USARTReadBuffer(char *buff,uint16_t len)
{
	uint16_t i;
	for(i=0;i<len;i++)
	{
		buff[i]=USARTReadData();
	}
}
void USARTFlushBuffer()
{
	while(USARTDataAvailable()>0)
	{
		USARTReadData();
	}
}


//////////////2////////////////////////////////////////
void USART2Init(uint16_t baud_rate)
{
    //Setup queue
    UQFront=UQEnd=-1;
    TRISDbits.RD7=0;
    TRISDbits.RD6=0;
    //SPBRG
    BAUDCON2bits.BRG162=1;
    switch(baud_rate)
    {
     case 2400:
        SPBRGH2= 0X1A;
        SPBRG2=0X0A;//103
        break;
     case 19200:
        SPBRG2=64;
        break;
     case 28800:
        SPBRG2=42;
        break;
     case 33600:
        SPBRG2=36;
        break;
    }
    //TXSTA
    TXSTA2bits.TX9=0;  //8 bit transmission
    TXSTA2bits.TXEN=1; //Transmit enable
    TXSTA2bits.SYNC=0; //Async mode
    TXSTA2bits.BRGH=1; //High speed baud rate

    //RCSTA
    RCSTA2bits.SPEN=1;   //Serial port enabled
    RCSTA2bits.RX9=0;    //8 bit mode
    RCSTA2bits.CREN=1;   //Enable receive
    RCSTA2bits.ADDEN=0;  //Disable address detection
   

    //Receive interrupt
    PIE3bits.RC2IE=0;
    

    ei();
}

void USART2WriteChar(char ch)
{
  while(!PIR3bits.TX2IF);

  TXREG2=ch;
}

void USART2WriteString(const char *str)
{
  while(*str!='\0')
  {
      USART2WriteChar(*str);
      str++;
  }
}

void USART2GotoNewLine()
{
    USART2WriteChar('\r');//CR
    USART2WriteChar('\n');//LF
}


void USART2WriteInt(int16_t val, int8_t field_length)
{
    char str[5]={0,0,0,0,0};
    int8_t i=4,j=0;

    //Handle negative integers
    if(val<0)
    {
        USART2WriteChar('-');   //Write Negative sign
        val=val*-1;     //convert to positive
    }
    else
    {
        USART2WriteChar(' ');
    }

    if(val==0 && field_length<1)
    {
        USART2WriteChar('0');
        return;
    }
    while(val)
    {
        str[i]=val%10;
        val=val/10;
        i--;
    }

    if(field_length==-1)
        while(str[j]==0) j++;
    else
        j=5-field_length;


    for(i=j;i<5;i++)
    {
        USART2WriteChar('0'+str[i]);
    }
}
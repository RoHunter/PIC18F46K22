#include <xc.h>
#include "config.h"
#include "usart_pic16.h" 
#include <pic18f46k22.h>
#include "bit_config.h"

void config(void)
{
    TRISA=0Xff;
    TRISB=0X00;
    TRISC=0X00;
    TRISD=0X00;
    TRISE=0Xff;
    
    PORTA=0X00;
    PORTB=0X00;
    PORTC=0X00;
    PORTD=0X00;
    PORTE=0X00;
     
    LATA=0X00;
    LATB=0X00;
    LATC=0X00;
    LATD=0X00;
    LATE=0X00;
    
    ANSELA=0Xff;
    ANSELB=0X00;
    ANSELC=0X00;
    ANSELD=0X00;
    ANSELE=0X00;
    
    OSCCON=0b01110100;
    OSCTUNEbits.PLLEN=1;
    //OSCCON2=0b10000000;
   
    

    

   
    
    
}

void pwm_config(void)
{
    CCPTMRS0=0b00000000;
    CCP2CON=0b00001100; //RC2
    CCP1CON=0b00001100; //RC1
    T2CON=0b01111101;
    PR2=160;
    
    CCPR2L=128;
    CCPR1L=64;
    CCP3CON=0b00001100; //RB5
    CCPR3L=128;
  

}

void adc_config(void)
{   TRISAbits.RA0=1;
    ANSELAbits.ANSA0=1;
    TRISAbits.RA1=1;
    ANSELAbits.ANSA1=1;
    

    ADCON0=0b00000011;  //RA0
    ADCON1=0b10000000;
    ADCON2=0b00111110;
    ADCON2bits.ADFM=0;

}

void eusart_config(void)
{
    TRISCbits.RC6=1;
    USARTInit(19200);//19200
    TRISCbits.RC7=1;
    INTCONbits.GIE=1;
    INTCONbits.PEIE=1;
    PIE1bits.RC1IE=1;
    

}

void init_io_display()
{
    TRISCbits.TRISC3=1;//i2c
    TRISCbits.TRISC4=1;//i2c
    I2C_Master_Init(100000);
    __delay_ms(100);
    Lcd_Init();
    Lcd_Clear();
    Cursor_Off();
    Lcd_Set_Cursor(1,1);
    Lcd_Write_String("Test");
    __delay_ms(100);
}
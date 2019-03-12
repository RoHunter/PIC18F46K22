#define _XTAL_FREQ  64000000
#include <xc.h>
#include "bit_config.h"
#include "config.h"
#include "pwm_con.h"
#include <math.h>
#include <stdio.h>
#include "adc.h"
#include "MPPT.h"


#define   forward   1  
#define   backward   2  
#define   new_transmision 2
#define   transmision_done 1
#define   sel PORTEbits.RE0
#define   dir1  LATCbits.LATC3
#define   dir2  LATCbits.LATC4
#define   br1  LATCbits.LATC5
#define   br2  LATCbits.LATC6
unsigned duty_boost,duty_buck;
unsigned int pasi,dir,nr_pasi,directie_2,go_stepper,start,pasi_int,sel_pasi,nt;
char str[20];
void main(void)
{
    
   char pwm_buffer[20];
    config();
    pwm_config();
    adc_config();
    init_io_display();
    char str_V[8],str_A[8],str_P[8];
    float tens,tens_A,curent,Power,Iout,Uout,Uin;
    int rez_adc_A,rez_adc_U;
    int dty,rez_adc,tip,port,c=100;
    float numar;
    dty=0;
    port=0;
    TRISDbits.RD4=0;
    LATDbits.LD6=0;
    LATDbits.LD7=0;
    LATDbits.LD5=0;
    LATDbits.LD4=0; 

         
    ADCON0=0b00010011;    
         
    Lcd_Clear();     
      
         
         
         
    while(1)
    {
        

//        buck_boost (2,50 );
   if(port==0);
    {
        read_Uout();
        
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("U=");
        sprintf(str_V, "%.2f", tens);
        Lcd_Set_Cursor(1,3);
        Lcd_Write_String(str_V);
        port=1;
         __delay_ms(100);
         ADRESH=0X00;
         __delay_ms(100);
    }
    
    if(port==1);
    {   
        read_Iout();
        
        Lcd_Set_Cursor(2,1);
        Lcd_Write_String("I=");
        sprintf(str_A, "%.2f", curent);
        Lcd_Set_Cursor(2,3);
        Lcd_Write_String(str_A);
         Lcd_Write_String(" A");
        port=2;
         __delay_ms(100);
         ADRESH=0X00;
         __delay_ms(100);
    }
if(port==2);
    {   
        read_Uin();
        
        Lcd_Set_Cursor(1,9);
        Lcd_Write_String("Ui=");
        sprintf(str_V, "%.2f", tens);
        Lcd_Set_Cursor(1,12);
        Lcd_Write_String(str_V);
         Lcd_Write_String(" V");
        port=0;
         __delay_ms(100);
         ADRESH=0X00;
         __delay_ms(100);
    }

//Power=Uout*Iout;
if(Uin<12)
{
    CCPR1L=0;
    Power=Uout*Iout; 
    CCPR2L=c;
        ADCON0=0b00001011;
        __delay_ms(10);
        ADCON0bits.GO=1;
        __delay_ms(100);
        rez_adc_A=ADRESH;
        tens_A=rez_adc_A*0.0181372549019608;
        Iout=tens_A;
    
        ADCON0=0b00000111;
        __delay_ms(10);
        ADCON0bits.GO=1;
        __delay_ms(100);
        rez_adc_U=ADRESH;
        tens=rez_adc_U*0.01953125;
        Uout=tens/0.25;
}

}
}
#define _XTAL_FREQ  64000000
#include <xc.h>
#include "bit_config.h"
#include "config.h"
#include "pwm_con.h"
#include "usart_pic16.h"
#include <math.h>
#include <stdio.h>
#include "stepper.h"
#include "main.h"
#include "adc.h"
//#include "HD44780.h"
#define   forward   1  
#define   backward   2  
#define   new_transmision 2
#define   transmision_done 1

int a,c,fac;
unsigned buck,boost,duty_boost,duty_buck;
unsigned int pasi,dir,nr_pasi,directie_2,go_stepper,start,pasi_int,sel_pasi,nt;
char str[20];
void main(void)
{
    dir=0;
    nt=0;
    nr_pasi=0;
    go_stepper=0;
    start=0;
    sel_pasi=0;
   char pwm_buffer[20];
    config();
    pwm_config();
    adc_config();
    eusart_config();

    int dty,rez_adc;
    float numar;
    dty=0;
         LATDbits.LD6=0;
         LATDbits.LD7=0;
         LATDbits.LD5=0;
         LATDbits.LD4=0; 
         
         
         
         
         
         
         
         
         
    while(1)
    {

//        ADCON0bits.GO=1;
//        
//        __delay_ms(100);
////        USARTWriteChar('R');
////     
        rez_adc=ADRESH;
        numar=rez_adc*0.0182;
        dty=rez_adc*0.39;
        dty=75;
//        duty_buck=25;
//        duty_boost=75;
//    
/*
 Buck:

	    CCPR1L=0;///boost MOS boost OFF==OPEN
        
	    CCPR2L=64;///buck //// PWM
 */        
        
  pwm_set_duty3(75) ;   
  pwm_set_duty2(75) ; 
 
        
        
        
        
        
        
        
//        sprintf(str, "Voltage= %.2f", numar);
//        USARTWriteString(str);
//        USARTGotoNewLine();
//        sprintf(pwm_buffer, "PWM= %u", dty);
//        USARTWriteString(pwm_buffer);
//        USARTGotoNewLine();
//	USARTWriteChar('B');
        
        
        
//        if(start==0)
//        {
//        USARTWriteString("Alege dicectia cu tasta D"); 
//        USARTGotoNewLine();
//        USARTWriteString("Reseteaza cu tasta R");
//        USARTGotoNewLine();
//        USARTGotoNewLine();
//        start=1;
//        }
//        
//        __delay_ms(100);
//        if(go_stepper==1)
//        {
//           stepper_move(directie_2, pasi);
//           go_stepper=0;
//        } 
//        else
//        {
//         LATDbits.LD6=0;
//         LATDbits.LD7=0;
//         LATDbits.LD5=0;
//         LATDbits.LD4=0; 
//        }
//     
//        
//       __delay_ms(100);
   }
}

//void interrupt gen_int(void)
//{
//    if(RC1IF==1)
//    {
////        #define    new_transmision 2
////        #define    transmision_done 1
//        nt=new_transmision;
//        PIE1bits.RC1IE=0;
//        
//        if((RCREG1=='R'|RCREG1=='r') & (nt==new_transmision))
//        {
//            USARTWriteString("reset");
//            USARTGotoNewLine();
//            USARTGotoNewLine();
//            dir=0;
//            nr_pasi=0;
//            start=0;
//            nt=transmision_done;
//        }
//        if((RCREG1=='D'|RCREG1=='d') & (nt==new_transmision))
//        {
//            USARTWriteString("Alege sensul");
//            USARTGotoNewLine();
//            USARTWriteString("Inainte tasta F");
//            USARTGotoNewLine();  
//            USARTWriteString("Inapoi tasta B");
//            USARTGotoNewLine();
//            USARTGotoNewLine();
//            dir=1;
//            nt=transmision_done;
//        }
//        if(((RCREG1=='F'|RCREG1=='f')& dir==1) & (nt==new_transmision))
//        {
//          directie_2=forward  ; 
//           USARTWriteString("Inainte");
//           USARTGotoNewLine();
//           USARTWriteString("Selecteaza numar pasi");
//           USARTGotoNewLine();
//           USARTGotoNewLine();
//          dir=0;
//          sel_pasi=1;
//          nt=transmision_done;
//        }
//        
//        if(sel_pasi==1&nt==new_transmision)
//        {
//         
//           pasi_int=RCREG1;
//           pasi=pasi_int-48;
//            sprintf(str, "Numar pasi= %u", pasi);
//            USARTWriteString(str);
//             USARTGotoNewLine();
//           USARTWriteString("Porneste cu tasta G");
//           USARTGotoNewLine();
//           USARTGotoNewLine();
//           sel_pasi=0;
//           nt=transmision_done;
//        }
//        
//        
//        if((RCREG1=='G'|RCREG1=='g') & (nt==new_transmision))
//        {
//            USARTWriteString("go");
//            USARTGotoNewLine();
//            USARTGotoNewLine();
//          go_stepper=1;
//          start=0;
//          nt=transmision_done;
//        }
//   
//        nt=transmision_done;
//        RC1IF=0;
////        PIE1bits.RC1IE=1;
//    }
//    
//}

/*
 * File:   pwm_con.c
 * Author: Silviu
 *
 * Created on June 28, 2018, 8:05 PM
 */


#include <xc.h>
#include "bit_config.h"
#include "config.h"

int c,b,d,adcp,adcn,type,dty,buck,boost;


//
//void buck(int duty_cycle)
//{
//	if(duty_cycle>100)
//    {
//    duty_cycle=100;
//    }
//    
//	c=duty_cycle*1.7; 
//	CCPR2L=c;
//    
//	
//}
//void boost(int duty_cycle)
//{
//	if(duty_cycle>100)
//    {
//    duty_cycle=100;
//    }
//    
//	c=duty_cycle*1.7; 
//	CCPR1L=c;
//    
//	
//}

void buck_boost (int type, int dty )
{
    if (type==1)
    {
        CCPR1L=0;
        	if(dty>100)
    {
    dty=100;
    }
    
	c=dty*1.7; 
	CCPR2L=c;
        
    }
    
    if (type==2)
    {
        CCPR2L=0b11111111;
        	if(dty>100)
    {
    dty=100;
    }
    
	c=dty*1.7; 
	CCPR1L=c;
        
    }
};
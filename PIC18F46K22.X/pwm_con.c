/*
 * File:   pwm_con.c
 * Author: Silviu
 *
 * Created on June 28, 2018, 8:05 PM
 */


#include <xc.h>
#include "bit_config.h"
#include "config.h"

int c,b,d,adcp,adcn,type,dty,buck,boost,dty_car;


//
//void boost(int dty_car)
//{
//	if(dty_car>100)
//    {
//    dty_car=100;
//    }
//    
//	c=dty_car*1.7; 
//	CCPR2L=c;
//    
//	
//}
//void buck(int dty_car)
//{
//	if(dty_car>100)
//    {
//    dty_car=100;
//    }
//    
//	c=dty_car*1.7; 
//	CCPR1L=c;
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
        CCPR2L=100;
        	if(dty>100)
    {
    dty=100;
    }
    
	c=dty*1.7; 
	CCPR1L=c;
        
    }
};


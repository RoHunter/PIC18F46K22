/*
 * File:   pwm_con.c
 * Author: Silviu
 *
 * Created on June 28, 2018, 8:05 PM
 */


#include <xc.h>
#include "bit_config.h"
#include "config.h"

int c,b,d,adcp,adcn;
    


void pwm_set_duty2(int duty_cycle)
{
	if(duty_cycle>100)
    {
    duty_cycle=100;
    }
    
	c=duty_cycle*1.7; 
	CCPR2L=c;
    
	
}
void pwm_set_duty3(int duty_cycle)
{
	if(duty_cycle>100)
    {
    duty_cycle=100;
    }
    
	c=duty_cycle*1.7; 
	CCPR1L=c;
    
	
}

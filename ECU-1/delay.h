#ifndef DELAY_H
#define DELAY_H

#include <LPC21xx.H>
void delay_s(unsigned int s);
void delay_ms(unsigned int ms);
void delay_ms(unsigned int ms)
{

	T0PR=60000-1; //assigning value to prescale register
	T0TCR=0x1;	//enable the count register(T0PC,T0TC)
	while(T0TC<ms);//waiting for ms milliseconds
	T0TCR=0x03;//reset the count registers
	T0TCR = 0x00; //disable the count register
}

void delay_s(unsigned int s)
{
	T0PR=60000000-1; //assigning value to prescale register
	T0TCR=0x1;	//enable the count register(T0PC,T0TC)
	while(T0TC<s);//waiting for  s seconds
	T0TCR=0x03;//reset the count registers
	T0TCR = 0x00; //disable the count register
}


#endif






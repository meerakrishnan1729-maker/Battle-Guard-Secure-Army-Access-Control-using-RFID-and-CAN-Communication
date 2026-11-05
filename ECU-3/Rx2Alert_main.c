//Rx2Alert_main.c

#include <LPC21xx.H>
#include "can2.h"
#include "delay.h"
#define LED     (1<<0)     // P0.0
#define BUZZER  (1<<2)     // P0.2

int main()
{
    CAN2_MSG m1;
    IODIR0|= LED | BUZZER;
    IOSET0 = LED | BUZZER;
    can2_init();
		while(1)
    {  	   

      can2_rx(&m1);
        if(m1.id == 0x101)
        {  
	        if(m1.byteA == 0x02)

				{

					   IOCLR0 = LED | BUZZER; //ON active low lewd and buzzer
					   delay_ms(5000);
					   IOSET0=LED|BUZZER;
				}			
        }
    }
}




//gsm.h

#ifndef GSM_H
#define GSM_H

#include "uart.h"
#include "delay.h"
void gsm_msg(void);
void gsm_msg(void)
{

    uart1_tx_string("AT\r\n");
    delay_ms(500);
    uart1_tx_string("AT+CMGF=1\r\n");
    delay_ms(500);
    uart1_tx_string("AT+CMGS=\"+919446507060\"\r\n");
    delay_ms(500);
    uart1_tx_string(" ALERT! UNAUTHORISED VEHICLE ACCESS DETECTED\r\n");
    delay_ms(500);																																																											  
    uart1_tx(0X1A);
    delay_ms(2000);

}



#endif







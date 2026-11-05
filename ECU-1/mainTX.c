#include <LPC21xx.h>

#include <string.h>
#include "lcd.h"
#include "can2.h"
#include "uart.h"
#include "gsm.h"
#include "delay.h"

int main()
{	
    CAN2_MSG m1;
    int i;
    char valid_tag[] = "06003B4E2E5D";
    char tag_id[13];
    //char ch;
    /* RFID - UART0 */
    uart0_init(9600);
    //GSM - UART1 */
    uart1_init(9600);
    /* CAN initialization */
    can2_init();
	LCD_INIT();
	LCD_COMMAND(0x80);
	LCD_STR("BATTLE-GUARD: ARMY");
	LCD_COMMAND(0xC0);
	LCD_STR("ACCESS CONTROL USING");
	LCD_COMMAND(0x94);
	LCD_STR("RFID AND CAN");
	LCD_COMMAND(0xD4);
	LCD_STR("COMMUNICATION");
	delay_ms(5000);
	LCD_COMMAND(0X01);
    LCD_COMMAND(0x80);
    LCD_STR("BATTLE GUARD");
    LCD_COMMAND(0xC0);
	LCD_STR("SCAN RFID");

    while(1)
    {


	for(i=0;i<12;i++)

{

tag_id[i]=uart0_rx();

}

tag_id[i]='\0';


/*           //Read RFID continuously 
        i = 0;


        while(i < 12)
        {
            ch = uart0_rx();
            //Accept only hexadecimal characters 
            if((ch >= '0' && ch <= '9') ||
               (ch >= 'A' && ch <= 'F') ||
               (ch >= 'a' && ch <= 'f'))
            {
                tag_id[i] = ch;
                i++;
            }

        }
        // End of string 
        tag_id[12] = '\0';

 
  */
        /* Compare RFID */
        if(strcmp(valid_tag, tag_id) == 0)
        {

            /* CAN RFID VALID MESSAGE */
            m1.id = 0x101;
            m1.rtr = 0;
            m1.dlc = 1;
            m1.byteA = 0x01;       /* VALID */
            m1.byteB = 0x00;
            can2_tx(m1);
            LCD_COMMAND(0X01);
		    LCD_COMMAND(0x80);
            LCD_STR((unsigned char *)tag_id);
		    LCD_COMMAND(0xC0);
	        LCD_STR("  VALID RFID");
			LCD_COMMAND(0x94);
	        LCD_STR("ACCESS GRANTED");
	        LCD_COMMAND(0xD4);
	        LCD_STR("< < GATE OPENING > >");
	        delay_ms(6000);
			// BACK TO NORMAL STATE
			LCD_COMMAND(0X01);
		    LCD_COMMAND(0x80);
            LCD_STR("BATTLE GUARD");
		    LCD_COMMAND(0xC0);
	        LCD_STR("SCAN RFID");
        }

        else
        {

            /* CAN RFID INVALID MESSAGE */
            m1.id = 0x101;
            m1.rtr = 0;
            m1.dlc = 1;
            m1.byteA = 0x02;       /* INVALID */
            m1.byteB = 0x00;
            can2_tx(m1);

			

            LCD_COMMAND(0X01);
		    LCD_COMMAND(0x80);
            //LCD_STR("    BATTLE GUARD");
			LCD_STR((unsigned char *)tag_id);
		    LCD_COMMAND(0xC0);
	        LCD_STR("  INVALID RFID");
			LCD_COMMAND(0x94);
	        LCD_STR("UNAUTHORIZED");
	        LCD_COMMAND(0xD4);
	        LCD_STR("***ACCESS DENIED***");
			 delay_ms(5000);
			  /* GSM disabled during RFID testing */
            gsm_msg();
			delay_ms(200);
			// BACK TO NORMAL STATE
			LCD_COMMAND(0X01);
		    LCD_COMMAND(0x80);
            LCD_STR("BATTLE GUARD");
		    LCD_COMMAND(0xC0);
	        LCD_STR("SCAN RFID");


           

        }

    }

}




//lcd.h 

#ifndef LCD_H
#define LCD_H

#include<lpc21xx.h>
#include"delay.h"
#define LCD_D 0Xff<<16
#define RS 1<<24
#define E 1<<25

void LCD_INIT(void);
void LCD_COMMAND(unsigned char);
void LCD_DATA(unsigned char);
void LCD_STR(unsigned char*);

void LCD_INIT(void)
{
IODIR1|=LCD_D|RS|E;
LCD_COMMAND(0X01);
LCD_COMMAND(0X02);
LCD_COMMAND(0X0C);
LCD_COMMAND(0X38);
}


void LCD_COMMAND(unsigned char CMD)
{
IOCLR1=LCD_D;
IOSET1=CMD<<16;
IOCLR1=RS;
IOSET1=E;
delay_ms(2);
IOCLR1=E;
}

void LCD_DATA(unsigned char d)
{
IOCLR1=LCD_D;
IOSET1=d<<16;
IOSET1=RS;
IOSET1=E;		 
delay_ms(2);
IOCLR1=E;
}

void LCD_STR(unsigned char*p)
{
while(*p)
{
LCD_DATA(*p++);
}
}


#endif


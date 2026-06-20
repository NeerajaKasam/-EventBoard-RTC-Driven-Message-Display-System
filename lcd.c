#include <LPC21xx.h>

#include "types.h"
#include "delay.h"
#include "defines.h"
#include "lcd_defines.h"
#include "lcd.h"


/* Write a byte to LCD */
void WriteLCD(u8 byte)
{
    /* Place data on LCD data bus */
    WRITEBYTE(IOPIN0, LCD_DATA, byte);

    /* Select write operation */
    IOCLR0 = 1 << LCD_RW;

    /* Generate enable pulse */
    IOSET0 = 1 << LCD_EN;
    delay_us(1);
    IOCLR0 = 1 << LCD_EN;

    delay_ms(2);
}


/* Send command to LCD */
void CmdLCD(u8 cmd)
{
    IOCLR0 = 1 << LCD_RS;
    WriteLCD(cmd);
}


/* Initialize LCD in 8-bit mode */
void InitLCD(void)
{
    delay_ms(15);

    /* Configure LCD data pins as output */
    WRITEBYTE(IODIR0, LCD_DATA, 0xFF);

    /* Configure LCD control pins as output */
    WRITENIBBLE(IODIR0, LCD_RS, 7);

    /* LCD initialization sequence */
    CmdLCD(0x30);
    delay_ms(4);
    delay_us(100);

    CmdLCD(0x30);
    delay_us(100);

    CmdLCD(0x30);

    CmdLCD(MODE_8BIT_2LINE);
    CmdLCD(DSP_ON_CUR_OFF);
    CmdLCD(CLEAR_LCD);
    CmdLCD(SHIFT_CUR_RIGHT);
}


/* Display a character on LCD */
void CharLCD(u8 asciiVal)
{
    IOSET0 = 1 << LCD_RS;
    WriteLCD(asciiVal);
}


/* Display string on LCD */
void StrLCD(s8 *p)
{
    while(*p)
        CharLCD(*p++);
}


/* Display signed integer on LCD */
void S32LCD(s32 n)
{
    if(n < 0)
    {
        CharLCD('-');
        n = -n;
    }

    U32LCD(n);
}


/* Display unsigned integer on LCD */
void U32LCD(u32 n)
{
    u8 a[10];
    s32 i = 0;

    if(n == 0)
    {
        CharLCD('0');
    }
    else
    {
        /* Convert number into ASCII digits */
        while(n)
        {
            a[i] = (n % 10) + 48;
            n /= 10;
            i++;
        }

        /* Display digits in correct order */
        for(--i; i >= 0; i--)
        {
            CharLCD(a[i]);
        }
    }
}
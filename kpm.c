#include <lpc21xx.h>
#include "types.h"
#include "kpm_defines.h"
#include "defines.h"
#include "lcd_defines.h"
#include "lcd.h"
#include "delay.h"

/* 4x4 keypad lookup table */
u32 kpmLUT[4][4] =
{
    {'1','2','3','/'},
    {'4','5','6','*'},
    {'7','8','9','-'},
    {'C','0','=','+'}
};

/* Initialize keypad interface */
void InitKPM(void)
{
    /* Configure keypad row pins as outputs */
    WRITENIBBLE(IODIR1, ROW0, 15);
}

/* Check whether any key is pressed */
u32 Colscan(void)
{
    u32 t;

    t = READNIBBLE(IOPIN1, COL0);

    return (t < 15) ? 0 : 1;
}

/* Identify active keypad row */
u32 Rowcheck(void)
{
    u32 r;

    for(r = 0; r <= 3; r++)
    {
        /* Drive one row low at a time */
        WRITENIBBLE(IOPIN1, ROW0, ~(1 << r));

        if(Colscan() == 0)
        {
            break;
        }
    }

    WRITENIBBLE(IOPIN1, ROW0, 0);

    return r;
}

/* Identify active keypad column */
u32 Colcheck(void)
{
    u32 c;

    for(c = 0; c <= 3; c++)
    {
        if(READBIT(IOPIN1, COL0 + c) == 0)
            break;
    }

    return c;
}

/* Scan keypad and return pressed key */
u32 Keyscan(void)
{
    u32 r,c,keyv;

    /* Wait for key press */
    while(Colscan());

    r = Rowcheck();
    c = Colcheck();

    /* Get key value from lookup table */
    keyv = kpmLUT[r][c];

    /* Wait for key release */
    while(Colscan() == 0);

    return keyv;
}

/* Read password with masked display */
u32 ReadPSW(void)
{
    u32 sum = 0;
    s8 key;
    u32 count = 0;

    while(1)
    {
        key = Keyscan();

        if((key >= '0') && (key <= '9'))
        {
            sum = (sum * 10) + (key - '0');

            CmdLCD(GOTO_LINE2_POS0 + count);

            /* Display '*' instead of actual digit */
            CharLCD('*');

            count++;

            while(Colscan() == 0);
        }
        else if(key == '-')
        {
            /* Backspace operation */
            if(count > 0)
            {
                sum = sum / 10;
                count--;

                CmdLCD(GOTO_LINE2_POS0 + count);
                CharLCD(' ');

                CmdLCD(GOTO_LINE2_POS0 + count);
            }

            while(Colscan() == 0);
        }
        else if(key == 'C')
        {
            /* Clear complete password */
            sum = 0;

            CmdLCD(GOTO_LINE2_POS0);
            StrLCD("    ");

            count = 0;
        }
        else if(key == '=')
        {
            /* Accept password entry */
            while(Colscan() == 0);
            break;
        }
    }

    return sum;
}

/* Read numeric input with character limit */
s32 ReadNum2(u32 n)
{
    u32 sum = 0;
    s8 key;
    u32 count = 0;
    u32 char_cnt = 0;

    while(1)
    {
        key = Keyscan();

        if((key >= '0') && (key <= '9'))
        {
            if(n == 10)
            {
                /* Password entry mode */
                sum = (sum * 10) + (key - '0');

                CmdLCD(GOTO_LINE2_POS0 + count);
                CharLCD('*');

                count++;
            }
            else
            {
                /* Normal numeric display mode */
                sum = (sum * 10) + (key - '0');

                CmdLCD(GOTO_LINE2_POS0);
                U32LCD(sum);

                count++;
            }

            char_cnt++;

            /* Check maximum allowed digits */
            if((n == 10 || n == 2 || n == 4) && char_cnt > n)
            {
                return -1;
            }

            while(Colscan() == 0);
        }
        else if(key == '-')
        {
            /* Backspace operation */
            if(count > 0)
            {
                sum = sum / 10;
                count--;
                char_cnt--;

                CmdLCD(GOTO_LINE2_POS0 + count);
                CharLCD(' ');

                CmdLCD(GOTO_LINE2_POS0 + count);
            }

            while(Colscan() == 0);
        }
        else if(key == 'C')
        {
            /* Clear complete input */
            sum = 0;

            CmdLCD(GOTO_LINE2_POS0);
            StrLCD("    ");

            count = 0;
            char_cnt = 0;
        }
        else if(key == '=' && count > 0)
        {
            /* Accept entered value */
            while(Colscan() == 0);
            break;
        }
    }

    return sum;
}
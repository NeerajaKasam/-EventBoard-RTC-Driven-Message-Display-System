#include "admin.h"
#include "lcd_defines.h"
#include "lcd.h"
#include "delay.h"
#include "types.h"
#include "kpm.h"

#include <lpc21xx.h>
#include <stdlib.h>

/* Default Admin Password */
u32 PSW = 1234;

s32 UserPSW;
u8 choice;

/* Event display control flag from main.c */
extern u32 msg_flag;

/* Event Schedule Structure */
typedef struct
{
    u8 hour;
    u8 minute;
    char text[80];
    u8 enabled;
} Message;

extern Message messageList[10];
extern s8 hour,min,sec,dom,month,year,dow;


/* Enter Admin Mode */
void adminMode(void)
{
    u8 flag = 1;

    /* Display Admin Mode Screen */
    CmdLCD(CLEAR_LCD);
    StrLCD("  ADMIN ");
    CmdLCD(GOTO_LINE2_POS0);
    StrLCD("        MODE");

    delay_s(2);

b:
    CmdLCD(CLEAR_LCD);
    StrLCD("ENTER PASSWORD");

    UserPSW = ReadNum2(10);

    if(UserPSW == -1)
    {
        CmdLCD(CLEAR_LCD);
        StrLCD("INVALID");
        delay_s(2);
        goto b;
    }

    /* Verify Password */
    if(UserPSW == PSW)
    {
        while(1)
        {
a:
            CmdLCD(CLEAR_LCD);

            /* Admin Menu */
            CmdLCD(GOTO_LINE1_POS0);
            StrLCD("1.Time 2.Date");

            CmdLCD(GOTO_LINE2_POS0);
            StrLCD("3.Day 4.Msg 5.Ex");

            choice = Keyscan();

            switch(choice)
            {
                case '1':
                    Edit_time();
                    break;

                case '2':
                    Edit_date();
                    break;

                case '3':
                    DOW = Edit_day();
                    break;

                case '4':
                    MsgDisp();
                    break;

                case '5':
                    flag = 0;
                    break;

                default:
                    CmdLCD(CLEAR_LCD);
                    StrLCD("Invalid Input");
                    delay_s(2);
                    goto a;
            }

            if(flag == 0)
                break;
        }
    }
    else
    {
        CmdLCD(CLEAR_LCD);
        StrLCD("INVALID PASSWORD");
        delay_s(2);
        goto b;
    }
}


/* Time Configuration Menu */
void Edit_time(void)
{
    while(1)
    {
        u8 ch;
        u8 flag = 1;

        CmdLCD(CLEAR_LCD);

        StrLCD("1.Hr 2.Min 3.Sec");

        CmdLCD(GOTO_LINE2_POS0);
        StrLCD("4.Back");

        ch = Keyscan();

        switch(ch)
        {
            case '1':
                HOUR = Edit_hour();
                break;

            case '2':
                MIN = Edit_min();
                break;

            case '3':
                SEC = Edit_sec();
                break;

            case '4':
                flag = 0;
                break;

            default:
                StrLCD(" Invalid");
                delay_s(2);
        }

        if(flag == 0)
            break;
    }
}


/* Edit Hour (0-23) */
s8 Edit_hour(void)
{
    s32 h;

    while(1)
    {
        CmdLCD(CLEAR_LCD);
        StrLCD("ENTER HOUR(0-23)");

        CmdLCD(GOTO_LINE2_POS0);

        h = ReadNum2(2);

        if(h == -1 || h > 23)
        {
            StrLCD(" Invalid");
            delay_s(2);
        }
        else
        {
            return h;
        }
    }
}


/* Edit Minute (0-59) */
s8 Edit_min(void)
{
    s32 m;

    while(1)
    {
        CmdLCD(CLEAR_LCD);
        StrLCD("ENTER MIN(0-59)");

        CmdLCD(GOTO_LINE2_POS0);

        m = ReadNum2(2);

        if(m == -1 || m > 59)
        {
            StrLCD(" Invalid");
            delay_s(2);
        }
        else
        {
            return m;
        }
    }
}


/* Edit Second (0-59) */
s8 Edit_sec(void)
{
    s32 s;

    while(1)
    {
        CmdLCD(CLEAR_LCD);
        StrLCD("ENTER SEC(0-59)");

        CmdLCD(GOTO_LINE2_POS0);

        s = ReadNum2(2);

        if(s == -1 || s > 59)
        {
            StrLCD(" Invalid");
            delay_s(2);
        }
        else
        {
            return s;
        }
    }
}


/* Date Configuration Menu */
void Edit_date(void)
{
    s8 choice;
    s8 flag = 1;

    while(1)
    {
        CmdLCD(CLEAR_LCD);

        StrLCD("1.Date 2.Month");

        CmdLCD(GOTO_LINE2_POS0);
        StrLCD("3.Year 4.Back");

        choice = Keyscan();

        switch(choice)
        {
            case '1':
                DOM = Edit_Ndate();
                break;

            case '2':
                MONTH = Edit_month();
                break;

            case '3':
                YEAR = Edit_year();
                break;

            case '4':
                flag = 0;
                break;

            default:
                CmdLCD(CLEAR_LCD);
                StrLCD("Invalid");
                delay_s(2);
        }

        if(flag == 0)
            break;
    }
}


/* Edit Day of Month (1-31) */
s8 Edit_Ndate(void)
{
    s32 d;

    while(1)
    {
        CmdLCD(CLEAR_LCD);
        StrLCD("ENTER DATE(1-31)");

        d = ReadNum2(2);

        if(d == -1 || d == 0 || d > 31)
        {
            StrLCD(" Invalid");
            delay_s(2);
        }
        else
        {
            return d;
        }
    }
}


/* Edit Month (1-12) */
s8 Edit_month(void)
{
    s32 m;

    while(1)
    {
        CmdLCD(CLEAR_LCD);
        StrLCD("ENTER MONTH");

        m = ReadNum2(2);

        if(m == -1 || m == 0 || m > 12)
        {
            StrLCD(" Invalid");
            delay_s(2);
        }
        else
        {
            return m;
        }
    }
}


/* Edit Year (2025-2999) */
s32 Edit_year(void)
{
    s32 y;

    while(1)
    {
        CmdLCD(CLEAR_LCD);
        StrLCD("ENTER 2025-2999");

        y = ReadNum2(4);

        if(y == -1 || y < 2025 || y > 2999)
        {
            StrLCD(" Invalid");
            delay_s(2);
        }
        else
        {
            return y;
        }
    }
}


/* Select Day of Week */
s8 Edit_day(void)
{
    s8 d;

    while(1)
    {
        CmdLCD(CLEAR_LCD);

        StrLCD("0.Su 1.M 2.T 3.W");

        CmdLCD(GOTO_LINE2_POS0);
        StrLCD("4.Th 5.Fr 6.Sa");

        d = Keyscan() - '0';

        if(d > 6)
        {
            CmdLCD(CLEAR_LCD);
            StrLCD("Invalid");
            delay_s(2);
        }
        else
        {
            return d;
        }
    }
}


/* Enable / Disable Scheduled Messages */
void MsgDisp(void)
{
    s32 ch;
    s32 n;

    while(1)
    {
        u8 flag = 1;

a:
        CmdLCD(CLEAR_LCD);
        StrLCD("Enter Num:1-10");

        ch = ReadNum2(2);

        if(ch <= 0 || ch > 10)
        {
            StrLCD(" Invalid");
            delay_s(2);
            goto a;
        }

        CmdLCD(CLEAR_LCD);
        StrLCD("1.En 2.Dis");

        n = Keyscan();

        switch(n)
        {
            case '1':

                /* Enable selected message */
                messageList[ch-1].enabled = 1;
                msg_flag = 1;

                CmdLCD(GOTO_LINE2_POS0);
                StrLCD("Enabled");

                flag = 0;
                delay_ms(500);
                break;

            case '2':

                /* Disable selected message */
                messageList[ch-1].enabled = 0;
                msg_flag = 0;

                CmdLCD(GOTO_LINE2_POS0);
                StrLCD("Disabled");

                flag = 0;
                delay_ms(500);
                break;

            default:

                StrLCD("Invalid");
                delay_s(2);
        }

        if(flag == 0)
            break;
    }
}
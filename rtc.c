#include <LPC214X.H>

#include "lcd_defines.h"
#include "lcd.h"
#include "rtc_defines.h"

/* Array containing day names */
char week[][4] = {"SUN","MON","TUE","WED","THU","FRI","SAT"};


/* Initialize RTC module */
void RTC_Init(void)
{
    /* Reset RTC before configuration */
    CCR = RTC_RESET;

    /* Configure RTC prescaler values */
    PREINT = PREINT_VAL;
    PREFRAC = PREFRAC_VAL;

    /* Enable RTC */
#ifndef _LPC2148_
    CCR = RTC_ENABLE;
#else
    CCR = RTC_ENABLE | RTC_CLKSRC;
#endif
}


/* Read current RTC time */
void GetRTCTimeInfo(s32 *hour,s32 *minute,s32 *second)
{
    *hour   = HOUR;
    *minute = MIN;
    *second = SEC;
}


/* Display time in HH:MM:SS format */
void DisplayRTCTime(u32 hour,u32 minute,u32 second)
{
    CharLCD((hour/10)+48);
    CharLCD((hour%10)+48);

    CharLCD(':');

    CharLCD((minute/10)+48);
    CharLCD((minute%10)+48);

    CharLCD(':');

    CharLCD((second/10)+48);
    CharLCD((second%10)+48);
}


/* Read current RTC date */
void GetRTCDateInfo(s32 *date,s32 *month,s32 *year)
{
    *date  = DOM;
    *month = MONTH;
    *year  = YEAR;
}


/* Display date in DD/MM/YYYY format */
void DisplayRTCDate(u32 date,u32 month,u32 year)
{
    CmdLCD(GOTO_LINE2_POS0);

    CharLCD((date/10)+48);
    CharLCD((date%10)+48);
    CharLCD('/');

    CharLCD((month/10)+48);
    CharLCD((month%10)+48);
    CharLCD('/');

    U32LCD(year);
}


/* Update RTC time */
void SetRTCTimeInfo(u32 hour,u32 minute,u32 second)
{
    HOUR = hour;
    MIN  = minute;
    SEC  = second;
}


/* Update RTC date */
void SetRTCDateInfo(u32 date,u32 month,u32 year)
{
    DOM   = date;
    MONTH = month;
    YEAR  = year;
}


/* Read current day of week */
void GetRTCDay(s32 *day)
{
    *day = DOW;
}


/* Display day name on LCD */
void DisplayRTCDay(u32 day)
{
    CmdLCD(GOTO_LINE1_POS0 + 10);
    StrLCD(week[day]);
}


/* Update day of week */
void SetRTCDay(u32 day)
{
    DOW = day;
}
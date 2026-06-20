#include <LPC21XX.h>
#include <string.h>

#include "types.h"
#include "delay.h"
#include "lcd.h"
#include "lcd_defines.h"
#include "rtc.h"
#include "adc.h"
#include "kpm.h"
#include "pin_connect_block.h"
#include "interrupts_defines.h"
#include "admin.h"

#define TIME_LIMIT      15              /* Event display duration in minutes */
#define TOTAL_MESSAGES  10              /* Total scheduled event messages */
#define LCD_WIDTH       16              /* LCD characters per row */

#define LED_RED         25
#define LED_GREEN       26

void msg_scroll(const char *p,u32 size,u32 timems);
void eint0_isr(void) __irq;
int find_strlen(const char *p);

s32 hour,min,sec;           /* Current RTC time */
s32 date,month,year,day;    /* Current RTC date */
s32 startHour,startMin;     /* Stores event start time */

/* Controls event display operation */
u32 msg_flag=1;

typedef struct
{
    u8 hour;          /* Scheduled event hour */
    u8 minute;        /* Scheduled event minute */
    char text[80];    /* Event message */
    u8 enabled;       /* Event enable flag */
}Message;

/* Predefined event schedule table */
Message messageList[TOTAL_MESSAGES]=
{
    {7,45 ,"               Good Morning! Classes Start Soon ",1},
    {9,45 ,"               ARM Workshop on external interrupts in LAB1 at 10AM ",1},
    {10,0 ,"               ARM kit issue time from 10AM - 10:30AM ",1},
    {10,15,"               C module lab exam in LAB2 ",1},
    {11,15,"               C module theory exam in LAB1 ",1},
    {12,45,"               Lunch Break from 1PM - 2PM ",1},
    {13,45,"               C Programming Session in Room 2 ",1},
    {15,15,"               Only 15 mins break time for next ARM session ",1},
    {17,0 ,"               Revise today's programs at home! ",1},
    {17,45,"               End of Day - See You Tomorrow! ",1}
};

int main()
{
    s32 i;
    u8 len;

    /* Initialize all peripherals */
    InitLCD();
    InitKPM();
    RTC_Init();
    Init_ADC();

    /* Configure status LEDs as output pins */
    IODIR1 |= (1<<LED_RED) | (1<<LED_GREEN);

    /* Red LED indicates normal monitoring mode */
    IOSET1 = (1<<LED_RED);
    IOCLR1 = (1<<LED_GREEN);

    /* Configure EINT0 pin for Admin Mode access */
    cfgPortPin(0,1,EINT0_PIN_FUNC);

    /* Configure external interrupt controller */
    VICIntSelect = 0;
    VICIntEnable = (1<<EINT0_VIC_CHNO);
    VICVectCntl0 = (1<<5) | EINT0_VIC_CHNO;
    VICVectAddr0 = (u32)eint0_isr;

    /* Configure EINT0 as edge-triggered interrupt */
    EXTMODE = (1<<0);

    while(1)
    {
        msg_flag = 1;

        /* Normal mode indication */
        IOSET1 = (1<<LED_RED);
        IOCLR1 = (1<<LED_GREEN);

        /* Read current RTC date and time */
        GetRTCTimeInfo(&hour,&min,&sec);
        GetRTCDateInfo(&date,&month,&year);
        GetRTCDay(&day);

        /* Display current time and day */
        CmdLCD(GOTO_LINE1_POS0);
        DisplayRTCTime(hour,min,sec);
        CharLCD(' ');
        DisplayRTCDay(day);

        /* Display current date */
        CmdLCD(GOTO_LINE2_POS0);
        DisplayRTCDate(date,month,year);

        /* Display current temperature from LM35 sensor */
        CmdLCD(GOTO_LINE2_POS0+11);
        U32LCD(Read_LM35());
        CharLCD(223);
        CharLCD('C');

        /* Check whether current time matches any scheduled event */
        for(i=0;i<TOTAL_MESSAGES;i++)
        {
            /* Check only enabled events */
            if(messageList[i].enabled &&
               messageList[i].hour == hour &&
               messageList[i].minute == min)
            {
                /* Store event start time for countdown calculation */
                startHour = hour;
                startMin  = min;

                /* Green LED indicates active event display mode */
                IOCLR1 = (1<<LED_RED);
                IOSET1 = (1<<LED_GREEN);

                CmdLCD(CLEAR_LCD);

                while(1)
                {
                    /* Read RTC continuously during event display */
                    GetRTCTimeInfo(&hour,&min,&sec);

                    /* Exit event mode after configured timeout */
                    if((((hour*60+min) -
                         (startHour*60+startMin)) > TIME_LIMIT) ||
                       (((hour*60+min) -
                         (startHour*60+startMin)) < 0))
                    {
                        break;
                    }

                    /* Get message length for scrolling */
                    len = find_strlen(messageList[i].text);

                    /* Display scrolling event message */
                    msg_scroll(messageList[i].text,len,200);

                    /* Exit scrolling when Admin Mode is entered */
                    if(msg_flag == 0)
                        break;
                }

                CmdLCD(CLEAR_LCD);

                /* Return to normal monitoring mode */
                IOSET1 = (1<<LED_RED);
                IOCLR1 = (1<<LED_GREEN);
            }
        }
    }
}

void msg_scroll(const char *p,u32 size,u32 timems)
{
    /* Buffer used for scrolling message display */
    char window[LCD_WIDTH+1];

    u32 i,j;
    
    /* Variables used for countdown timer calculation */
    s32 totalRemain;
    s32 remMin;
    s32 remSec;

    for(i=0;i<=size;i++)
    {
        for(j=0;j<LCD_WIDTH;j++)            /* Generate scrolling window */
        {
            if((i+j) < size)
                window[j] = p[i+j];
            else
                window[j] = ' ';            /* Fill unused positions with spaces */
        }

        window[LCD_WIDTH] = '\0';

        /* Display scrolling message on LCD */
        CmdLCD(GOTO_LINE1_POS0);
        StrLCD(window);

        GetRTCTimeInfo(&hour,&min,&sec);

        /* Calculate remaining event display time */
        totalRemain =
        (TIME_LIMIT * 60) -
        (((hour * 60 + min) -
          (startHour * 60 + startMin)) * 60)
        - sec;

        if(totalRemain < 0)
            totalRemain = 0;

        /* Convert remaining seconds into MM:SS format */
        remMin = totalRemain / 60;
        remSec = totalRemain % 60;

        /* Display countdown timer */
        CmdLCD(GOTO_LINE2_POS0);

        CharLCD((remMin/10)+'0');
        CharLCD((remMin%10)+'0');

        CharLCD(':');

        CharLCD((remSec/10)+'0');
        CharLCD((remSec%10)+'0');

        /* Display current temperature during event */
        CmdLCD(GOTO_LINE2_POS0+11);

        U32LCD(Read_LM35());
        CharLCD(223);
        CharLCD('C');

        /* Control scrolling speed */
        delay_ms(timems);

        if(msg_flag == 0)
            break;
    }
}

int find_strlen(const char *p)
{
    int i = 0;

    /* Calculate string length */
    while(p[i])
        i++;

    return i;
}

void eint0_isr(void) __irq
{   
    adminMode();         /* Enter password protected admin mode */

    CmdLCD(CLEAR_LCD);   /* Clear LCD before exiting ISR */

    EXTINT = (1<<0);     /* Clear EINT0 interrupt flag */

    VICVectAddr = 0;     /* End of interrupt service routine */
}
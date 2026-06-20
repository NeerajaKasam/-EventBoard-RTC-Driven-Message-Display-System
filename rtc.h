#ifndef _RTC_H
#define _RTC_H

#include "types.h"

/* Initialize RTC module */
void RTC_Init(void);

/* Read current RTC time */
void GetRTCTimeInfo(s32 *, s32 *, s32 *);

/* Display time in HH:MM:SS format */
void DisplayRTCTime(u32, u32, u32);

/* Read current RTC date */
void GetRTCDateInfo(s32 *, s32 *, s32 *);

/* Display date in DD/MM/YYYY format */
void DisplayRTCDate(u32, u32, u32);

/* Update RTC time */
void SetRTCTimeInfo(u32, u32, u32);

/* Update RTC date */
void SetRTCDateInfo(u32, u32, u32);

/* Read current day of week */
void GetRTCDay(s32 *);

/* Display day name on LCD */
void DisplayRTCDay(u32);

/* Update day of week */
void SetRTCDay(u32);

#endif
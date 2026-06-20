#ifndef _ADMIN_H
#define _ADMIN_H

#include "types.h"

/* Enter Admin Mode */
void adminMode(void);

/* Time configuration menu */
void Edit_time(void);

/* Date configuration menu */
void Edit_date(void);

/* Select day of week */
s8 Edit_day(void);

/* Edit RTC hour */
s8 Edit_hour(void);

/* Edit RTC minute */
s8 Edit_min(void);

/* Edit RTC second */
s8 Edit_sec(void);

/* Edit day of month */
s8 Edit_Ndate(void);

/* Edit RTC month */
s8 Edit_month(void);

/* Edit RTC year */
s32 Edit_year(void);

/* Enable or disable scheduled messages */
void MsgDisp(void);

/* Enable selected message */
void MsgEnable(void);

/* Disable selected message */
void MsgDisable(void);

#endif

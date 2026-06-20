#ifndef _KPM_H
#define _KPM_H

#include "types.h"

/* Initialize keypad interface */
void InitKPM(void);

/* Check keypad column status */
u32 Colscan(void);

/* Identify active keypad row */
u32 Rowcheck(void);

/* Identify active keypad column */
u32 Colcheck(void);

/* Scan keypad and return pressed key */
u32 Keyscan(void);

/* Read numeric value from keypad */
u32 ReadNum(void);

/* Read password with masked display */
u32 ReadPSW(void);

/* Read numeric input with digit limit */
s32 ReadNum2(u32 maxDigits);

#endif
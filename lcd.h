#ifndef _LCD_H
#define _LCD_H

#include "types.h"

/* Write a byte to LCD */
void WriteLCD(u8 byte);

/* Send command to LCD */
void CmdLCD(u8 cmd);

/* Initialize LCD module */
void InitLCD(void);

/* Display a character on LCD */
void CharLCD(u8 asciival);

/* Display string on LCD */
void StrLCD(s8 *str);

/* Display unsigned integer on LCD */
void U32LCD(u32 num);

/* Display signed integer on LCD */
void S32LCD(s32 num);

/* Display floating point value on LCD */
void F32LCD(f32 num, u32 precision);

/* Load custom character into CGRAM */
void BuildCGRAM(u8 *p, u8 nbytes);

#endif
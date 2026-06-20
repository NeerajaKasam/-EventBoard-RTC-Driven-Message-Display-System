#ifndef _LCD_DEFINES_H
#define _LCD_DEFINES_H

/* LCD pin connections on LPC2148 Port 0 */
#define LCD_DATA 8          // P0.8 - P0.15 connected to LCD data pins D0-D7
#define LCD_RS   16         // P0.16 -> Register Select pin
#define LCD_RW   17         // P0.17 -> Read/Write pin
#define LCD_EN   18         // P0.18 -> Enable pin

/* HD44780 LCD command definitions */
#define CLEAR_LCD          0x01   // Clear display screen
#define RET_CUR_HOME       0x02   // Move cursor to home position
#define SHIFT_CUR_RIGHT    0x06   // Move cursor right after each character
#define SHIFT_CUR_LEFT     0x07   // Move cursor left after each character

#define DSP_OFF            0x08   // Display OFF
#define DSP_ON_CUR_OFF     0x0C   // Display ON, Cursor OFF
#define DSP_ON_CUR_ON      0x0E   // Display ON, Cursor ON
#define DSP_ON_CUR_BLINK   0x0F   // Display ON, Cursor blinking

#define SHIFT_DSP_LEFT     0x10   // Shift display left
#define SHIFT_DSP_RIGHT    0x14   // Shift display right

/* LCD interface configuration modes */
#define MODE_4BIT_1LINE    0x20   // 4-bit interface, 1-line display
#define MODE_4BIT_2LINE    0x28   // 4-bit interface, 2-line display
#define MODE_8BIT_1LINE    0x30   // 8-bit interface, 1-line display
#define MODE_8BIT_2LINE    0x38   // 8-bit interface, 2-line display

/* DDRAM starting addresses */
#define GOTO_LINE1_POS0 0x80      // Line 1, position 0
#define GOTO_LINE2_POS0 0xC0      // Line 2, position 0
#define GOTO_LINE3_POS0 0x94      // Line 3, position 0 (for 4-line displays)
#define GOTO_LINE4_POS0 0xD4      // Line 4, position 0 (for 4-line displays)

/* CGRAM starting address for custom characters */
#define GOTO_CGRAM_START   0x40

#endif
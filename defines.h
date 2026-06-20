#ifndef _DEFINES_H
#define _DEFINES_H

/* Read a single bit from a register or variable */
#define READBIT(WORD,BIT) \
        ((WORD >> BIT) & 1)

/* Write a 4-bit value at the specified bit position */
#define WRITENIBBLE(WORD,NIBBLESTARTBITPOS,VAL) \
        WORD=((WORD & (~(15 << NIBBLESTARTBITPOS))) | (((VAL & 15) << NIBBLESTARTBITPOS)))

/* Read a 4-bit nibble from the specified bit position */
#define READNIBBLE(WORD,NIBBLESTARTBIT) \
        ((WORD >> NIBBLESTARTBIT) & 15)

/* Write an 8-bit value at the specified bit position */
#define WRITEBYTE(WORD,BYTESTARTBITPOS,VAL) \
        WORD=((WORD & (~(255 << BYTESTARTBITPOS))) | (((VAL & 255) << BYTESTARTBITPOS)))

/* Write a single bit value (0 or 1) */
#define WRITEBIT(WORD,BITPOS,BIT) \
        WORD=((WORD & (~(1 << BITPOS))) | (BIT << BITPOS))

#endif
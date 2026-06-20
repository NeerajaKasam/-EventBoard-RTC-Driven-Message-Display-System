// pin_connect_block.h

#ifndef _PIN_CONNECT_BLOCK_H
#define _PIN_CONNECT_BLOCK_H

#include "types.h"

/* Configure pin function using PINSEL registers */
void cfgPortPin(u32 portNo, u32 pinNo, u32 pinFunc);

#endif
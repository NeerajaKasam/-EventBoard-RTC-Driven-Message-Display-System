#ifndef _ADC_H
#define _ADC_H

#include "types.h"

/* Initialize ADC peripheral */
void Init_ADC(void);

/* Read ADC channel and return analog & digital values */
void Read_ADC(u8 chNo, f32 *eAR, u32 *dVal);

/* Read temperature from LM35 sensor */
u32 Read_LM35(void);

#endif
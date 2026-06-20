#include "types.h"
#include "pin_connect_block.h"
#include "delay.h"
#include "adc_defines.h"
#include <LPC21XX.h>

/* Initialize ADC peripheral */
void Init_ADC(void)
{
    /* Configure P0.28 as ADC input pin */
    cfgPortPin(0, 28, AN0_INPUT_PIN);

    /* Power ON ADC and configure ADC clock */
    ADCR = (1 << PDN_BIT) | (CLKDIV << CLKDIV_BITS);
}


/* Read ADC channel and return analog & digital values */
void Read_ADC(u8 chNo, f32 *eAR, u32 *dVal)
{
    /* Clear previously selected ADC channels */
    ADCR &= 0xFFFFFF00;

    /* Select ADC channel and start conversion */
    ADCR |= (1 << ADC_START_BIT) | (1 << chNo);

    delay_us(3);

    /* Wait until ADC conversion is complete */
    while(((ADDR >> DONE_BIT) & 1) == 0);

    /* Stop ADC conversion */
    ADCR &= ~(1 << ADC_START_BIT);

    /* Extract 10-bit ADC result */
    *dVal = ((ADDR >> RESULT_BITS) & 1023);

    /* Convert digital value into voltage */
    *eAR = (*dVal * (3.3 / 1023));
}


/* Read temperature from LM35 sensor */
u32 Read_LM35(void)
{
    f32 eAR;
    u32 dVal;
    u32 tdegC;

    static u32 flag;

    /* Initialize ADC only once */
    if(flag == 0)
    {
        Init_ADC();
        flag = 1;
    }

    /* Read LM35 output from ADC channel 1 */
    Read_ADC(1, &eAR, &dVal);

    /* LM35 provides 10mV output per °C */
    tdegC = eAR * 100;

    return tdegC;
}
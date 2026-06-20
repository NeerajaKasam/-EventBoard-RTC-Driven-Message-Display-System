#include "types.h"
#include <LPC21XX.h>

/* Configure pin function using PINSEL registers */
void cfgPortPin(u32 portNo, u32 pinNo, u32 pinFunc)
{
    /* PINSEL0 controls P0.0-P0.15
       PINSEL1 controls P0.16-P0.31 */
    if(portNo == 0)
    {
        if(pinNo <= 15)
        {
            /* Configure pin function in PINSEL0 */
            PINSEL0 = (PINSEL0 & ~(3 << (pinNo * 2)))
                    | (pinFunc << (pinNo * 2));
        }
        else if(pinNo <= 31)
        {
            /* Configure pin function in PINSEL1 */
            PINSEL1 = (PINSEL1 & ~(3 << ((pinNo - 16) * 2)))
                    | (pinFunc << ((pinNo - 16) * 2));
        }
    }
}
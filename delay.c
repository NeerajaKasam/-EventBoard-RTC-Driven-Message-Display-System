#include "types.h"

/* Generate delay in microseconds */
void delay_us(u32 dlyus)
{
/* Adjust loop count based on CPU clock frequency */
dlyus *= 12;

```
while(dlyus--);
```

}

/* Generate delay in milliseconds */
void delay_ms(u32 dlyms)
{
/* Convert milliseconds into loop count */
dlyms *= 12000;

```
while(dlyms--);
```

}

/* Generate delay in seconds */
void delay_s(u32 dlys)
{
/* Convert seconds into loop count */
dlys *= 12000000;

```
while(dlys--);
```

}

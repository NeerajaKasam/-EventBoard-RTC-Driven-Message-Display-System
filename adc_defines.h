/* System clock configuration */
#define FOSC        12000000          // Main oscillator frequency (12 MHz)
#define CCLK        (FOSC * 5)        // CPU clock frequency
#define PCLK        (CCLK / 4)        // Peripheral clock frequency

/* ADC clock configuration */
#define ADCCLK      3000000                 // ADC operating clock (3 MHz)
#define CLKDIV      ((PCLK / ADCCLK) - 1)   // Clock divider to get ADC clock from PCLK

/* ADCR register bit positions */
#define CLKDIV_BITS 8                 // ADC clock divider field
#define PDN_BIT     21                // ADC power control bit
#define ADC_START_BIT 24              // Start ADC conversion

/* ADDR register bit positions */
#define RESULT_BITS 6                 // Start position of ADC result
#define DONE_BIT   31                 // Conversion complete flag

/* ADC pin function selection */
#define PIN_FUNC2       1
#define AN0_INPUT_PIN   PIN_FUNC2
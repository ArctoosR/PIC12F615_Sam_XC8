#include <xc.h>

// Configuration bits
#pragma config FEXTOSC = OFF    // External Oscillator mode selection bits (Oscillator not enabled)
#pragma config RSTOSC = HFINT1  // Power-up default value for COSC bits (HFINTOSC with HFFRQ = 1 MHz and CDIV = 1:1)
#pragma config WDTE = OFF       // WDT operating mode (WDT Disabled)

// Define the frequency
#define _XTAL_FREQ 1000000  // 1 MHz

void main(void) {
    // Set RB0 as output
    TRISAbits.TRISA5 = 0;
    
    while(1) {
        LATAbits.LATA5 = 1;  // Turn on LED
        __delay_ms(500);     // Delay 500 ms
        LATAbits.LATA5 = 0;  // Turn off LED
        __delay_ms(500);     // Delay 500 ms  
    }
}

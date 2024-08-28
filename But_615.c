
#ifndef _XTAL_FREQ
   #define _XTAL_FREQ 4000000  // 4MHZ crystal
#endif


//__CONFIG(CP_OFF & BOREN_ON & IOSCFS_4MHZ & MCLRE_OFF & WDTE_OFF & PWRTE_OFF & FOSC_INTOSCIO);


// CONFIG
#pragma config FOSC = INTOSCIO  // Oscillator Selection bits (INTOSCIO oscillator: I/O function on GP4/OSC2/CLKOUT pin, I/O function on GP5/OSC1/CLKIN)
#pragma config WDTE = ON        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select bit (MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config IOSCFS = 8MHZ    // Internal Oscillator Frequency Select (8 MHz)
#pragma config BOREN = ON       // Brown-out Reset Selection bits (BOR enabled)


#include <xc.h>
#include <stdint.h>
void main(void) {
    
   

    ADCON0=0x00;                // Internal ADC OFF
    ANSEL=0x00;                  // All Analog selections pins are assigned as
    TRISIO = 0b000001;  // GP0 as input (button), GP2 as output (LED)
    CMCON0 = 7; //comparators disabled
    GPIO = 0;           // Clear GPIO
    

    while (1) {
        if (GP0 == 1) {     // ????? ????? ???? (GP0)
            GP2 = 1;        // ???? ???? LED (GP2)
        } else {
            GP2 = 0;        // ????? ???? LED (GP2)
        }
    }
}
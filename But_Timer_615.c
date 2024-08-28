#ifndef _XTAL_FREQ
   #define _XTAL_FREQ 4000000  // 4MHZ crystal
#endif

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

volatile uint8_t button_pressed = 0;

void __interrupt() ISR() {
    if (TMR1IF) {  // ????? ???? ????? 1
        TMR1IF = 0;  // ??? ???? ??? ????
        TMR1 = 3036;  // ????? ???? ????? ???? 1 ?????
        if (button_pressed) {
            GP2 = ~GP2;  // ????? ????? LED
            button_pressed = 0;  // ???? ???? ????? ????
        }
    }
}

void main(void) {
    ADCON0 = 0x00;                // Internal ADC OFF
    ANSEL = 0x00;                 // All Analog selections pins are assigned as digital
    TRISIO = 0b000001;            // GP0 as input (button), GP2 as output (LED)
    CMCON0 = 7;                   // Comparators disabled
    GPIO = 0;                     // Clear GPIO

    // ????? ????? 1
    T1CON = 0x31;  // ???? ???? ????? 1 ?? ??????????????? 1:8
    TMR1 = 3036;  // ????? ????? ???? 1 ?????
    TMR1IE = 1;  // ???? ???? ???? ????? 1
    PEIE = 1;    // ???? ???? ???????? ?????
    GIE = 1;     // ???? ???? ???????? ?????

    while (1) {
        if (GP0 == 1) {           // ????? ????? ???? (GP0)
            __delay_ms(50);       // ????? ???? ??????? ?? ????
            if (GP0 == 1) {       // ????? ???? ????? ????
                button_pressed = 1;  // ????? ????? ????
                TMR1ON = 1;          // ???? ???? ?????
            }
        }
    }
}

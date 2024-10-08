#include <xc.h>

// ??????? ??????
#pragma config FOSC = INTRCIO   // ??????? ?? ???????? ?????
#pragma config WDTE = OFF       // ??????? ???? Watchdog Timer
#pragma config PWRTE = ON       // ???? ???? Power-up Timer
#pragma config MCLRE = OFF      // ??????? ???? Master Clear Reset
#pragma config BOREN = ON       // ???? ???? Brown-out Reset
#pragma config CP = OFF         // ??????? ???? Code Protection
#pragma config CPD = OFF        // ??????? ???? Data Code Protection

#define _XTAL_FREQ 4000000  // ?????? ???????? ????? 4MHz

void main(void) {
    // ????? ??????
    TRISIO0 = 1;  // ??? GP0 ?? ????? ????? (????)
    TRISIO2 = 0;  // ??? GP2 ?? ????? ????? (LED)
    GPIO = 0;     // ????? ???? ?????? ?? ???
    CMCON = 7;
    ANSEL = 0 ;

    while (1) {
        if (GP0 == 1) {  // ????? ???? ???? ????
            GP2 = 1;     // ???? ???? LED
            __delay_ms(1000);  // ????? 1 ?????
            GP2 = 0;     // ????? ???? LED
        }
    }
}

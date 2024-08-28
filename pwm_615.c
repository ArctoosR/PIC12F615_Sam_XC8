
#include <xc.h>

#define _XTAL_FREQ 4000000  // 4MHz crystal

// CONFIG
#pragma config FOSC = INTOSCIO  // Oscillator Selection bits (INTOSCIO oscillator: I/O function on GP4/OSC2/CLKOUT pin, I/O function on GP5/OSC1/CLKIN)
#pragma config WDTE = ON        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select bit (MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config IOSCFS = 8MHZ    // Internal Oscillator Frequency Select (8 MHz)
#pragma config BOREN = ON       // Brown-out Reset Selection bits (BOR enabled)

void PWM_Init() {
    PR2 = 0x63;  // ????? ????? ???? 20kHz
    CCP1CON = 0x0C;  // ????? CCP1 ???? PWM
    T2CON = 0x04;  // ????? ?????2 ?? prescaler 1:1
    CCPR1L = 0x32;  // ????? ????? ????? PWM
    TMR2 = 0;  // ??? ???? ?????2
    T2CONbits.TMR2ON = 1;  // ???? ???? ?????2
}

void PWM_SetDutyCycle(unsigned int duty) {
    CCPR1L = duty >> 2;  // ????? 8 ??? ??????
    CCP1CONbits.DC1B1 = (duty & 0x02) >> 1;  // ????? ??? DC1B1
    CCP1CONbits.DC1B0 = duty & 0x01;  // ????? ??? DC1B0
}



void main() {
    
   
    TRISAbits.TRISIO2 = 0 ; // ????? GP2 ?? ????? ?????
    PWM_Init();  // ???????? ????? PWM

   
    
    

    PWM_Init();  // ???????? ????? PWM

    while (1) {
                // ????? Duty Cycle ?? 50%
        PWM_SetDutyCycle(100);
        __delay_ms(1000);

        // ????? Duty Cycle ?? 75%
        PWM_SetDutyCycle(200);
        __delay_ms(1000);

        // ????? Duty Cycle ?? 25%
        PWM_SetDutyCycle(20);
          __delay_ms(1000);
       
    }
}

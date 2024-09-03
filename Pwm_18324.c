
#include <xc.h>
#include <pic16f18324.h> // ????? ???? ??? ???????? ???? ????? OSCCON

#define _XTAL_FREQ 4000000 // Definition for delay_ms(x)

// CONFIG1
#pragma config FEXTOSC = OFF    // FEXTOSC External Oscillator mode Selection bits (Oscillator not enabled)
#pragma config RSTOSC = HFINT32 // Power-up default value for COSC bits (HFINTOSC with 2x PLL (32MHz))
#pragma config CLKOUTEN = OFF   // Clock Out Enable bit (CLKOUT function is disabled; I/O or oscillator function on OSC2)
#pragma config CSWEN = ON       // Clock Switch Enable bit (Writing to NOSC and NDIV is allowed)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)

// CONFIG2
#pragma config MCLRE = ON       // Master Clear Enable bit (MCLR/VPP pin function is MCLR; Weak pull-up enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config WDTE = ON        // Watchdog Timer Enable bits (WDT enabled, SWDTEN is ignored)
#pragma config LPBOREN = OFF    // Low-power BOR enable bit (ULPBOR disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bits (Brown-out Reset enabled, SBOREN bit ignored)
#pragma config BORV = LOW       // Brown-out Reset Voltage selection bit (Brown-out voltage (Vbor) set to 2.45V)
#pragma config PPS1WAY = ON     // PPSLOCK bit One-Way Set Enable bit (The PPSLOCK bit can be cleared and set only once; PPS registers remain locked after one clear/set cycle)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable bit (Stack Overflow or Underflow will cause a Reset)
#pragma config DEBUG = OFF      // Debugger enable bit (Background debugger disabled)

// CONFIG3
#pragma config WRT = OFF        // User NVM self-write protection bits (Write protection off)
#pragma config LVP = ON         // Low Voltage Programming Enable bit (Low Voltage programming enabled. MCLR/VPP pin function is MCLR. MCLRE configuration bit is ignored.)

// CONFIG4
#pragma config CP = OFF         // User NVM Program Memory Code Protection bit (User NVM code protection disabled)
#pragma config CPD = OFF        // Data NVM Memory Code Protection bit (Data NVM code protection disabled)

void MCU_Init(void){
     WPUA5 = 1;
    TRISA = 0b111111;
    TRISC = 0b000000;
    LATC = 0;
    ANSELA = 0;
    ANSELC = 0;

}

void PWM()
{
     TRISA = 0b111111; // Port All input
    TRISC = 0b110000; // RC0-RC3 output
    ANSELA = 0; // all digital
    ANSELC = 0; // all digital
    WPUA5 = 1; // RA5 weakly pulled up
    RC3PPS = 2;
//------------ Initialize PWM ----------------------------------
    T2CON = 0b00000100; // Timer 2 PS1/1 setting
    PR2 = 0xFF; // Timer2 Period Register setting
    PWM5CON= 0b11000000; // Positive logic output
    PWM5DCH= 0x80; // Set duty cycle
}

void main(void) {
 MCU_Init();
PWM();
   
 
  
    while(1) {
        PWM5DCH += 1 ;
        __delay_ms(10);
    }
}









//
//
//
//
//#include <xc.h>
//#include <stdbool.h>
//#include <stdint.h>
//
//// Configuration bits
//#pragma config FEXTOSC = OFF    // External Oscillator mode selection bits (Oscillator not enabled)
//#pragma config RSTOSC = HFINT1  // Power-up default value for COSC bits (HFINTOSC with HFFRQ = 1 MHz and CDIV = 1:1)
//#pragma config WDTE = OFF       // WDT operating mode (WDT Disabled)
//#define _XTAL_FREQ 1000000
//
//
//unsigned int flag_TMR2 = 0;
//
//
//void MCU_Init(void){
//     WPUA5 = 1;
//    TRISA = 0b111111;
//    TRISC = 0b000000;
//    LATC = 0;
//    ANSELA = 0;
//    ANSELC = 0;
//
//}
//
//void PWM()
//{
//     TRISA = 0b111111; // Port All input
//    TRISC = 0b110000; // RC0-RC3 output
//    ANSELA = 0; // all digital
//    ANSELC = 0; // all digital
//    WPUA5 = 1; // RA5 weakly pulled up
//    RC3PPS = 2;
////------------ Initialize PWM ----------------------------------
//    T2CON = 0b00000100; // Timer 2 PS1/1 setting
//    PR2 = 0xFF; // Timer2 Period Register setting
//    PWM5CON= 0b11000000; // Positive logic output
//    PWM5DCH= 0x80; // Set duty cycle
//}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//void initial_PORT()
//{
//    /*input*/
//    TRISAbits.TRISA5 = 1; 
//    PORTAbits.RA5 = 0;
//    ANSELAbits.ANSA5 = 0;
//
//    /*output*/
//    TRISCbits.TRISC1 = 0;
//    TRISCbits.TRISC2 = 0;
//    PORTCbits.RC1 = 0;
//    PORTCbits.RC2 = 0;
//    ANSELCbits.ANSC1 = 0;
//    ANSELCbits.ANSC2 = 0; 
//}
//
//void initial_INTERRUPT()
//{
//    INTCONbits.GIE = 1;
//    INTCONbits.PEIE = 1;
//    PIE1bits.TMR2IE = 1;
//    PIE4bits.CCP4IE = 1;
//}
//
//void initial_TIMER()
//{
//    T2CONbits.TMR2ON = 1;
//    T2CONbits.T2OUTPS = 0b1111; // Postscaler 1:16
//    T2CONbits.T2CKPS = 0b01;    // Prescaler 4
//    TMR2 = 0;
//}
//
//void initial_PPS()
//{
//    /*RC1 use as CCP4*/
//    RC1PPS = 0x05;  // Configure RC1 as CCP4 output
//}
//
//void initial_PWM()
//{
//    CCP4CONbits.CCP4EN = 1;      // CCP enable
//    CCP4CONbits.CCP4FMT = 0;     // Right aligned format 
//    CCP4CONbits.CCP4MODE = 0b1111; // Select PWM mode
//    CCPTMRSbits.C4TSEL = 0b01;   // Select PWM on TMR2
//    PR2 = 100;
//}
//
//void delayTMR(int a) 
//{
//    flag_TMR2 = 0; 
//    while(a > flag_TMR2); 
//}
//
//void __interrupt() ISR() 
//{
//    if(PIR1bits.TMR2IF == 1)
//    { 
//        flag_TMR2 ++;
//        PIR1bits.TMR2IF = 0;
//    }
//
//    if(PIR4bits.CCP4IF == 1)
//    {
//         PIR4bits.CCP4IF = 0;
//    }
//}
//
//void main(void)
//{
////    initial_PORT();
////    initial_INTERRUPT();
////    initial_TIMER();
////    initial_PPS();
////    initial_PWM();
////
////    PORTCbits.RC2 = 1;  // Enable
//
//    MCU_Init();
//    PWM();
//    while(1)
//    {
//       // CCPR4L = 150;
//        PWM5DCH += 1 ;
//        __delay_ms(100);
//    }
//
//    return;
//}



//
//#include <xc.h>
//
//
//// Configuration bits
//#pragma config FEXTOSC = OFF    // External Oscillator mode selection bits (Oscillator not enabled)
//#pragma config RSTOSC = HFINT1  // Power-up default value for COSC bits (HFINTOSC with HFFRQ = 1 MHz and CDIV = 1:1)
//#pragma config WDTE = OFF       // WDT operating mode (WDT Disabled)
//#define _XTAL_FREQ 1000000
//
//void main(void) {
//
//    // ??????? ????
//    TRISCbits.TRISC1 = 0;
//    ANSELCbits.ANSC1 = 0;
//
//    // ??????? ????? ? PWM
//    T2CON = 0b00000101;       // ???? ???? ????? 2 ? ????? prescaler ?? 1:4
//    PR2 = 100;                // ????? ????? ????? 2
//    CCP4CON = 0b00001100;     // ???? ???? PWM
//    CCPR4L = 50;              // ???? ??? PWM (50%)
//
//    // ??????? PPS
//    RC1PPS = 0x05;            // ????? RC1 ?? ????? ????? CCP4
//    
//    
// 
//    while (1) {
//     
//        
//    }
//}

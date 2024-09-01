#include <xc.h>

// CONFIG1
#pragma config FEXTOSC = OFF    // FEXTOSC External Oscillator mode Selection bits (Oscillator not enabled)
#pragma config RSTOSC = HFINT1  // Power-up default value for COSC bits (HFINTOSC (1MHz))
#pragma config CLKOUTEN = OFF   // Clock Out Enable bit (CLKOUT function is disabled; I/O or oscillator function on OSC2)
#pragma config CSWEN = ON       // Clock Switch Enable bit (Writing to NOSC and NDIV is allowed)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)

// CONFIG2
#pragma config MCLRE = ON       // Master Clear Enable bit (MCLR/VPP pin function is MCLR; Weak pull-up enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config WDTE = OFF       // Watchdog Timer Enable bits (WDT disabled; SWDTEN is ignored)
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

#define _XTAL_FREQ 4000000  // ?????? ???????

#define tm1637_dio LATAbits.LATA1
#define tm1637_clk LATAbits.LATA0
#define tm1637_dio_tris TRISAbits.TRISA1
#define tm1637_clk_tris TRISAbits.TRISA0

void tm1637_start(void);
void tm1637_stop(void);
void tm1637_write_byte(unsigned char b);
void tm1637_display_number(int num);

void main(void) {
    // ????? ??????? ?? ????? ?????
    tm1637_dio_tris = 0;
    tm1637_clk_tris = 0;
    ANSELA = 0;  // ????? ??????? ?? ????? ???????
    CM1CON0 = 0x00;  // ??????? ???? ???????????
    CM2CON0 = 0x00;

    while (1) {
        for (int i = 0; i < 100; i++) {
            tm1637_display_number(i);

            __delay_ms(100);
        }
    }
}

void tm1637_start(void) {
    tm1637_dio = 1;
    tm1637_clk = 1;
    __delay_us(2);
    tm1637_dio = 0;
}

void tm1637_stop(void) {
    tm1637_clk = 0;
    tm1637_dio = 0;
    __delay_us(2);
    tm1637_clk = 1;
    tm1637_dio = 1;
}

void tm1637_write_byte(unsigned char b) {
//    for (int i = 0; i < 8; i++) {
//        tm1637_clk = 0;
//        if (b & 0x01) {
//            tm1637_dio = 1;
//        } else {
//            tm1637_dio = 0;
//        }
//        b >>= 1;
//        tm1637_clk = 1;
//    }
//    tm1637_clk = 0;
//    tm1637_dio_tris = 1;  // ????? ?? ????? ????? ???? ACK
//    tm1637_clk = 1;
//    while (tm1637_dio) {
//        // ????? ACK
//    }
//    
//   
//    tm1637_clk = 0;
//    tm1637_dio_tris = 0;  // ????? ?? ????? ?????
    
  for (int i = 0; i < 8; i++) {
        tm1637_clk = 0;
        if (b & 0x01) {
            tm1637_dio = 1;
        } else {
            tm1637_dio = 0;
        }
        b >>= 1;
        tm1637_clk = 1;
    }
    tm1637_clk = 0;
    tm1637_dio_tris = 1;  // ????? ?? ????? ????? ???? ACK
    tm1637_clk = 1;
    __delay_us(50);  // ????? ???? ????? ???? ????? ??????
    if (tm1637_dio) {
        // ACK ?????? ???
        // ????? ????????? ?? ??????? ????? ????
    }
    tm1637_clk = 0;
    tm1637_dio_tris = 0;  // ????? ?? ????? ?????   
    
}

void tm1637_display_number(int num) {
    tm1637_start();
    tm1637_write_byte(0x40);  // ????? ?? ???? ????? ????
    tm1637_stop();

    tm1637_start();
    tm1637_write_byte(0xC0);  // ????? ???? ????
    tm1637_write_byte(num % 10);  // ????? ??? ????
    tm1637_write_byte((num / 10) % 10);  // ????? ??? ?????
    tm1637_stop();

    tm1637_start();
    tm1637_write_byte(0x88);  // ???? ???? ???????
    tm1637_stop();
}

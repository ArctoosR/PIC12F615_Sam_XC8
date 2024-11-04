//#ifndef _XTAL_FREQ
//   #define _XTAL_FREQ 8000000  // 8MHZ crystal
//#endif
//
//#pragma config FOSC = INTOSCIO  // Oscillator Selection bits (INTOSCIO oscillator: I/O function on GP4/OSC2/CLKOUT pin, I/O function on GP5/OSC1/CLKIN)
//#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
//#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
//#pragma config MCLRE = OFF      // MCLR Pin Function Select bit (MCLR pin function is MCLR)
//#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
//#pragma config IOSCFS = 8MHZ    // Internal Oscillator Frequency Select (8 MHz)
//#pragma config BOREN = ON       // Brown-out Reset Selection bits (BOR enabled)
//
//#include <xc.h>
//#include <stdint.h>
//#include <stdio.h>
//
//#define BAUDRATE 9600
//#define BIT_DELAY (100000 / BAUDRATE) // ?????? ????? ?? ???? ??? ????
//
//#define TX_PIN GP1 // ??? ????? ?????
//#define TOGGLE_PIN GP4 // ??? ???? ???? ????
//
//// ???????
//volatile unsigned int edge_count = 0;
//volatile unsigned int timer_val = 0;
//volatile unsigned int frequency = 0;
//
//void delay_us(unsigned int us) {
//    while(us--) {
//        __delay_us(1);
//    }
//}
//
//void UART_Init(void) {
//    TRISIO1 = 0; // ????? ??? TX ?? ????? ?????
//    TX_PIN = 1; // ??? TX ?? ?? ???? ????? ???? ????
//}  
//
//void UART_Write(unsigned char Data) {
//    unsigned char mask;
//    TX_PIN = 0; // ????? ??? ????
//    delay_us(BIT_DELAY);
//
//    // ????? 8 ??? ????
//    for (mask = 0x01; mask != 0; mask = mask << 1) {
//        if (Data & mask)
//            TX_PIN = 1;
//        else
//            TX_PIN = 0;
//        delay_us(BIT_DELAY); // ????? ???
//    }
//
//    TX_PIN = 1; // ????? ??? ????
//    delay_us(BIT_DELAY);
//
//    // ????? ????? ???? ??????? ?? ?????? ????????
//    delay_us(100);
//}
//
//void UART_Write_Text(const char *text) {
//    while (*text) {
//        UART_Write(*text++);
//    }
//}
//
//void UART_Write_Int(unsigned int num) { 
//    char buffer[6];
//    int i = 0;
//    do {
//        buffer[i++] = (num % 10) + '0';
//        num /= 10;
//    } while (num > 0);
//
//    for (int j = i - 1; j >= 0; j--) {
//        UART_Write(buffer[j]);
//    }
//}
//
//void itoa(int value, char* buffer) {
//    char temp[10];
//    int i = 0, j = 0;
//    if (value == 0) {
//        buffer[j++] = '0';
//        buffer[j] = '\0';
//        return;
//    }
//    while (value > 0) {
//        temp[i++] = (value % 10) + '0';
//        value /= 10;
//    }
//    for (j = 0; i > 0; j++) {
//        buffer[j] = temp[--i];
//    }
//    buffer[j] = '\0';
//}
//int count = 0 ;
//void __interrupt() ISR(void) {
//    if (INTF) {
//        
//        edge_count++;
//        timer_val = TMR0;
//        //TMR0 = 0; // ???? ???? ?????0
//        if (edge_count >= 2) { // ?? ?? ??? (???? ? ?????)
//            frequency = (_XTAL_FREQ / (4 * 8)) / (timer_val * 2);
//            edge_count = 0;
//        }
//        INTF = 0; // ??? ???? ??? ????
//    }
//    if (T0IF) {
//      count ++ ;
//      if(count > 78 )
//      {
//         TOGGLE_PIN = ~ TOGGLE_PIN; 
//         count  = 0 ;
//      }
//              
//        
//        T0IF = 0;
//    }
//}
//
//void main(void) {
//    ANSEL =  0b00000000; // Analog Select
//    OPTION_REGbits.nGPPU =  1; // GPIO pull-ups are disabled
//    TRISIO2 = 1; // ????? GP0 ?? ????? ?????
//    TRISIO4 = 0; // ????? GP4 ?? ????? ?????
//    OPTION_REGbits.INTEDG = 1; // ???? ?? ??? ?????????
//    CMCON0 = 0b00000000; // Comparator Control
//    WPU = 0b00000100; // Weak Pull-up
//    IOC = 0b00001000; // Interrupt-on-change
//    INTE = 1; // ???? ???? ???? ?????
//
//    
//
//    TRISIO = 0b000100; // GP0 ?? ????? ?????? GP2 ?? ????? ?????
//    CMCON0 = 7; // ???????????? ???????
//
//    // ??????? ?????0
//    OPTION_REGbits.T0CS = 0; // ?????0 ?? ???? ?????
//    OPTION_REGbits.PSA = 0; // ?????????? ?? ?????0 ????? ??????
//    OPTION_REGbits.PS = 0b010; // ?????????? 1:8
//    TMR0 = 0;
//
//    PEIE = 1;
//    GIE = 1;
//  
//    UART_Init();
//    int test = 8620;
//
//    while(1) {
//        // ???? ???? ??? GP4
//      
//        __delay_ms(1000); // ????? 1 ?????
//        
//        // ????? ????? ?????? ?? ???? ?????
//        UART_Write_Int(frequency);
//        UART_Write_Text("\r\n");
//
//        if (frequency == 50) {
//            // ??? ?????? 50 ???? ????? ???? ??
//        }
//    }
//}

//
//
//#ifndef _XTAL_FREQ
//   #define _XTAL_FREQ 8000000  // 4MHZ crystal
//#endif
//
//
//
////__CONFIG(CP_OFF & BOREN_ON & IOSCFS_4MHZ & MCLRE_OFF & WDTE_OFF & PWRTE_OFF & FOSC_INTOSCIO);
//
//
//// CONFIG
//#pragma config FOSC = INTOSCIO  // Oscillator Selection bits (INTOSCIO oscillator: I/O function on GP4/OSC2/CLKOUT pin, I/O function on GP5/OSC1/CLKIN)
//#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT enabled)
//#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
//#pragma config MCLRE = ON       // MCLR Pin Function Select bit (MCLR pin function is MCLR)
//#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
//#pragma config IOSCFS = 8MHZ    // Internal Oscillator Frequency Select (8 MHz)
//#pragma config BOREN = ON       // Brown-out Reset Selection bits (BOR enabled)
//
//
//#include <xc.h>
//#include <stdint.h>
//#include <stdio.h>
//
//#define BAUDRATE 9600
//#define BIT_DELAY (100000 / BAUDRATE) // ?????? ????? ?? ???? ??? ????
//
//#define TX_PIN GP1 // ??? ????? ?????
//#define TOGGLE_PIN GP4 // ??? ???? ???? ????
//
//// ???????
//volatile unsigned int edge_count = 0;
//volatile unsigned int timer_val = 0;
//volatile unsigned int frequency = 0;
//
//int count = 0 ;
//
//void delay_us(unsigned int us) {
//    while(us--) {
//        __delay_us(1);
//    }
//}
//
//void UART_Init(void) {
//    TRISIO1 = 0; // ????? ??? TX ?? ????? ?????
//    TX_PIN = 1; // ??? TX ?? ?? ???? ????? ???? ????
//}  
//
//void UART_Write(unsigned char Data) {
//    unsigned char mask;
//    TX_PIN = 0; // ????? ??? ????
//    delay_us(BIT_DELAY);
//
//    // ????? 8 ??? ????
//    for (mask = 0x01; mask != 0; mask = mask << 1) {
//        if (Data & mask)
//            TX_PIN = 1;
//        else
//            TX_PIN = 0;
//        delay_us(BIT_DELAY); // ????? ???
//    }
//
//    TX_PIN = 1; // ????? ??? ????
//    delay_us(BIT_DELAY);
//
//    // ????? ????? ???? ??????? ?? ?????? ????????
//    delay_us(100);
//}
//
//void UART_Write_Text(const char *text) {
//    while (*text) {
//        UART_Write(*text++);
//    }
//}
//
//void UART_Write_Int(unsigned int num) { 
//    char buffer[6];
//    int i = 0;
//    do {
//        buffer[i++] = (num % 10) + '0';
//        num /= 10;
//    } while (num > 0);
//
//    for (int j = i - 1; j >= 0; j--) {
//        UART_Write(buffer[j]);
//    }
//}
//
//void itoa(int value, char* buffer) {
//    char temp[10];
//    int i = 0, j = 0;
//    if (value == 0) {
//        buffer[j++] = '0';
//        buffer[j] = '\0';
//        return;
//    }
//    while (value > 0) {
//        temp[i++] = (value % 10) + '0';
//        value /= 10;
//    }
//    for (j = 0; i > 0; j++) {
//        buffer[j] = temp[--i];
//    }
//    buffer[j] = '\0';
//}
//
//void __interrupt() ISR(void) {
//    if (INTF) {
//        
//        edge_count++;
//        timer_val = TMR0;
//        //TMR0 = 0; // ???? ???? ?????0
//        if (edge_count >= 2) { // ?? ?? ??? (???? ? ?????)
//            frequency = (_XTAL_FREQ / (4 * 8)) / (timer_val * 2);
//            edge_count = 0;
//        }
//        INTF = 0; // ??? ???? ??? ????
//    }
//    if (T0IF) {
//        
//                   GP4 = 1;        // ???? ???? LED (GP2)
//    
//            GP4 = 0;        // ????? ???? LED (GP2)
//      count ++ ;
//      if(count > 78 )
//      {
//       //  TOGGLE_PIN = ~ TOGGLE_PIN; 
//         count  = 0 ;
//      }
//              
//        
//        T0IF = 0;
//    }
//}
//void main(void) {
//    
//   
//
////    ADCON0=0x00;                // Internal ADC OFF
////    ANSEL=0x00;                  // All Analog selections pins are assigned as
////    TRISIO = 0b000001;  // GP0 as input (button), GP2 as output (LED)
////    CMCON0 = 7; //comparators disabled
////    GPIO = 0;           // Clear GPIO
//    
//    
//        ANSEL =  0b00000000; // Analog Select
//    OPTION_REGbits.nGPPU =  1; // GPIO pull-ups are disabled
//    TRISIO2 = 1; // ????? GP0 ?? ????? ?????
//    TRISIO4 = 0; // ????? GP4 ?? ????? ?????
//    OPTION_REGbits.INTEDG = 1; // ???? ?? ??? ?????????
//    CMCON0 = 0b00000000; // Comparator Control
//    WPU = 0b00000100; // Weak Pull-up
//    IOC = 0b00001000; // Interrupt-on-change
//    INTE = 1; // ???? ???? ???? ?????
//
//    
//
//    TRISIO = 0b000100; // GP0 ?? ????? ?????? GP2 ?? ????? ?????
//    CMCON0 = 7; // ???????????? ???????
//
//    // ??????? ?????0
//    OPTION_REGbits.T0CS = 0; // ?????0 ?? ???? ?????
//    OPTION_REGbits.PSA = 0; // ?????????? ?? ?????0 ????? ??????
//    OPTION_REGbits.PS = 0b010; // ?????????? 1:8
//    TMR0 = 0;
//
//    PEIE = 1;
//    GIE = 1;
//    
//UART_Init();
//    while (1) {
//        
//         __delay_ms(1000); // ????? 1 ?????
//        
//        // ????? ????? ?????? ?? ???? ?????
//        UART_Write_Int(frequency);
//        UART_Write_Text("\r\n");
//        
//    }
//}


#ifndef _XTAL_FREQ
   #define _XTAL_FREQ 8000000  // 8MHZ crystal
#endif

#pragma config FOSC = INTOSCIO  // Oscillator Selection bits (INTOSCIO oscillator: I/O function on GP4/OSC2/CLKOUT pin, I/O function on GP5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // MCLR Pin Function Select bit (MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config IOSCFS = 8MHZ    // Internal Oscillator Frequency Select (8 MHz)
#pragma config BOREN = ON       // Brown-out Reset Selection bits (BOR enabled)

#include <xc.h>
#include <stdint.h>
#include <stdio.h>

#define BAUDRATE 12500
#define BIT_DELAY (100000 / BAUDRATE) // ?????? ????? ?? ???? ??? ????
#define BIT_DELAY_FOR_WRITE BIT_DELAY // ???? ??? ????? ?? ?????

#define TX_PIN GP1 // ??? ????? ?????
#define TOGGLE_PIN GP0 // ??? ???? ???? ????

// ???????
 unsigned int edge_count = 0;
 unsigned int timer_val = 0;
 unsigned int frequency = 0;
 unsigned char new_data_flag = 0 ;
void delay_us(unsigned int us) {
    while(us--) {
        __delay_us(1);
    }
}

void UART_Init(void) {
    TRISIO1 = 0; // ????? ??? TX ?? ????? ?????
    TX_PIN = 1; // ??? TX ?? ?? ???? ????? ???? ????
}  

void UART_Write(unsigned char Data) {
    unsigned char mask;
    TX_PIN = 0; // ????? ??? ????
    delay_us(BIT_DELAY);

    // ????? 8 ??? ????
    for (mask = 0x01; mask != 0; mask = mask << 1) {
        if (Data & mask)
            TX_PIN = 1;
        else
            TX_PIN = 0;
        delay_us(BIT_DELAY); // ????? ???
    }

    TX_PIN = 1; // ????? ??? ????
    delay_us(BIT_DELAY);

    // ????? ????? ???? ??????? ?? ?????? ????????
    delay_us(1000);
}

void UART_Write_Text(const char *text) {
    while (*text) {
        UART_Write(*text++);
    }
}

void UART_Write_Int(unsigned int num) { 
    char buffer[6];
    int i = 0;
    do {
        buffer[i++] = (num % 10) + '0';
        num /= 10;
    } while (num > 0);

    for (int j = i - 1; j >= 0; j--) {
        UART_Write(buffer[j]);
    }
}

void itoa(int value, char* buffer) {
    char temp[10];
    int i = 0, j = 0;
    if (value == 0) {
        buffer[j++] = '0';
        buffer[j] = '\0';
        return;
    }
    while (value > 0) {
        temp[i++] = (value % 10) + '0';
        value /= 10;
    }
    for (j = 0; i > 0; j++) {
        buffer[j] = temp[--i];
    }
    buffer[j] = '\0';
}

volatile int count = 0;

void __interrupt() ISR(void) {
    if (INTF) {
     edge_count++;
        timer_val = TMR1; // مقدار تایمر1 را ذخیره می‌کند
        TMR1 = 0; // ریست کردن تایمر1
        new_data_flag = 1; // تنظیم فلگ برای نشان دادن داده جدید
        INTF = 0; // پاک کردن فلگ وقفه
        }
       
    
    if (TMR1IF) {
        
         //TOGGLE_PIN = ~TOGGLE_PIN;
//        count++;
//        if(count == 10) { // ?? ???? ??????? ????
//            TOGGLE_PIN = ~TOGGLE_PIN;
//           count = 0;
//        }
        TMR1IF = 0;
    }
}

void main(void) {
    ANSEL =  0b00000000; // Analog Select
    OPTION_REGbits.nGPPU =  1; // GPIO pull-ups are disabled
    TRISIO2 = 1; // ????? GP0 ?? ????? ?????
    TRISIO4 = 0; // ????? GP4 ?? ????? ?????
    OPTION_REGbits.INTEDG = 1; // ???? ?? ??? ?????????
    CMCON0 = 0b00000000; // Comparator Control
    WPU = 0b00001000; // Weak Pull-up
    IOC = 0b00000100; // Interrupt-on-change
    INTE = 1; // ???? ???? ???? ?????

    TRISIO = 0b000100; // GP0 ?? ????? ?????? GP2 ?? ????? ?????
    CMCON0 = 7; // ???????????? ???????
    CMCON1bits.T1ACS = 0 ;
//    // ??????? ?????0
//    OPTION_REGbits.T0CS = 0; // ?????0 ?? ???? ?????
//    OPTION_REGbits.PSA = 0; // ?????????? ?? ?????0 ????? ??????
//    OPTION_REGbits.PS = 0b010; // ?????????? 1:16
//    TMR0 = 0;
    // ??????? ?????1 
    T1CON = 0b00110001; // ?????1 ???? ?? ?????????? 1:1 
    TMR1 = 0;
    
   // PR2 =255 ;
    TMR1IE = 1 ;
    
    PEIE = 1;
  
    GIE = 1;
  
    UART_Init();
    int test = 8620;

    while(1) {
        // ???? ???? ??? GP4
       // TOGGLE_PIN = ~TOGGLE_PIN; 
        __delay_ms(100); // ????? 1 ?????
        
        
        // ????? ????? ?????? ?? ???? ?????
        UART_Write_Int(frequency);
        UART_Write_Text("\r\n");
         frequency = 0;
        // محاسبه فرکانس در حلقه اصلی
        if (new_data_flag) {
            if (edge_count >= 2) {
                frequency = (_XTAL_FREQ / (1 * 16)) / (timer_val * 2);
                edge_count = 0;
            }
            new_data_flag = 0; // ریست فلگ داده جدید
        }

       if (frequency >= 40) 
       {
         if (frequency <= 60) 
          {
       
                // ??? ?????? 50 ???? ????? ???? ??
               TOGGLE_PIN = ~TOGGLE_PIN; 
              timer_val = 0 ;
             
               //count = 0 ;
          
       
          }
         }
    }
}

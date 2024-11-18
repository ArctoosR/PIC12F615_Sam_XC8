


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

//#define TX_PIN GP1 // ??? ????? ?????
#define TOGGLE_PIN GP0 // ??? ???? ???? ????

#define Start_PIN GP1 // ??? ???? ???? ????
#define V_Fan_PIN GP3 // ??? ???? ???? ????
#define V_Reg_PIN GP5 // ??? ???? ???? ????
#define En_598_PIN GP4 // ??? ???? ???? ????
// ???????
 unsigned int edge_count = 0;
 unsigned int timer_val = 0;
 unsigned int frequency = 0;
 unsigned char new_data_flag = 0 ;
 unsigned char flag_Start = 0 ;
 unsigned char Flag_50h = 0 ;
 unsigned int count_7ms = 0;
  unsigned char Flag_V_Reg = 0 ;
 
void delay_us(unsigned int us) {
    while(us--) {
        __delay_us(1);
    }
}
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
//    delay_us(1000);
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

volatile int count = 0;

void __interrupt() ISR(void) {
    if (INTF) {
     edge_count++;
        timer_val = TMR1; // ????? ?????1 ?? ????? ??????
        TMR1 = 0; // ???? ???? ?????1
        new_data_flag = 1; // ????? ??? ???? ???? ???? ???? ????
        INTF = 0; // ??? ???? ??? ????
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


void Start_Power(void)
{
                  En_598_PIN = 0 ; 
                  En_598_PIN = 1 ; 
              __delay_ms(200);
               En_598_PIN = 0 ; 
               Start_PIN = 1 ; 
              __delay_ms(120);
              Start_PIN = 0 ; 
               __delay_ms(500);
}
void main(void) {
    ANSEL =  0b00000000; // Analog Select
    OPTION_REGbits.nGPPU =  1; // GPIO pull-ups are disabled
    TRISIO2 = 1; // ????? GP0 ?? ????? ?????
    TRISIO3 = 1; // ????? GP0 ?? ????? ?????
    TRISIO4 = 0; // ????? GP0 ?? ????? ?????
    TRISIO5 = 1; // ????? GP4 ?? ????? ?????
    TRISIO1 = 0; // ????? GP4 ?? ????? ?????
    OPTION_REGbits.INTEDG = 1; // ???? ?? ??? ?????????
    CMCON0 = 0b00000000; // Comparator Control
    WPU = 0b00000000; // Weak Pull-up
    IOC = 0b00000100; // Interrupt-on-change
    INTE = 1; // ???? ???? ???? ?????

    TRISIO = 0b101100; // GP0 ?? ????? ?????? GP2 ?? ????? ?????
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
  
   // UART_Init();
    int test = 8620;

            En_598_PIN = 0 ; 

              Start_PIN = 0 ; 

              Flag_50h = 0 ;
              count_7ms = 0 ;
      __delay_ms(1000);
     Start_Power();
     Flag_V_Reg =  1 ;
    while(1) {
      
        // ???? ???? ??? GP4
        TOGGLE_PIN = ~TOGGLE_PIN; 
        __delay_ms(100); // ????? 1 ?????
        
        
        // ????? ????? ?????? ?? ???? ?????
       // UART_Write_Int(frequency);
       // UART_Write_Text("\r\n");
         frequency = 0;
        // ?????? ?????? ?? ???? ????
        if (new_data_flag) {
            if (edge_count >= 2) {
                frequency = (_XTAL_FREQ / (1 * 16)) / (timer_val * 2);
                edge_count = 0;
            }
            new_data_flag = 0; // ???? ??? ???? ????
        }

       if (frequency >= 40) 
       {
         if (frequency <= 60) 
          {
  
//                        while(V_Reg_PIN == 1 )
//                            {
//                                 __delay_ms(7000) ;
//                                 if(V_Fan_PIN == 1 )
//                                     {
//                                        En_598_PIN = 1 ; 
//                                        break ;
//                                      }
//                            }  
             
             Flag_50h = 1 ;
               
                        timer_val = 0 ;
                   
            }
         }
       else 
       {
            Flag_50h = 0 ;
            En_598_PIN = 1 ; 
       }
        
         if(V_Reg_PIN == 0  && Flag_V_Reg == 1)
         {
           
             Flag_V_Reg = 0 ;
             Start_Power();
         }
           if(V_Reg_PIN == 1 && Flag_50h == 1  )
                            {
                 count_7ms ++ ;
              
                               if(count_7ms == 100)
                               {
                                   count_7ms = 0 ;
                              
                                 if(V_Fan_PIN == 1 )
                                     {
                                     
                                        En_598_PIN = 1 ; 
                                       // break ;
                                      }
                               }
                            }
           else 
           {
             En_598_PIN = 1 ;  
           }
         
         
        // En_598_PIN = 1 ; 
    }
}

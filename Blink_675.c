
#ifndef _XTAL_FREQ
   #define _XTAL_FREQ 4000000  // 4MHZ crystal
#endif


//__CONFIG(CP_OFF & BOREN_ON & IOSCFS_4MHZ & MCLRE_OFF & WDTE_OFF & PWRTE_OFF & FOSC_INTOSCIO);


// CONFIG
#pragma config FOSC = INTRCIO   // Oscillator Selection bits (INTOSC oscillator: I/O function on GP4/OSC2/CLKOUT pin, I/O function on GP5/OSC1/CLKIN)
#pragma config WDTE = ON        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF      // Power-Up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // GP3/MCLR pin function select (GP3/MCLR pin function is MCLR)
#pragma config BOREN = ON       // Brown-out Detect Enable bit (BOD enabled)
#pragma config CP = OFF         // Code Protection bit (Program Memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)


#include <xc.h>
#include <stdint.h>

#define MAJOR_NUMBER      1u
#define MINOR_NUMBER      0u







void main(void) {
        GPIO0=0x00;                        // make all GPIO port output
    TRISIO=0x00;                     // TRISIO direction as output
    ADCON0=0x00;                // Internal ADC OFF
    ANSEL=0x00;                  // All Analog selections pins are assigned as
    

  
  while(1)
  {
     
          GPIO5 = 1;                      // Make GPIO0 port high
        __delay_ms(500); 
        GPIO5 = 0;                     // Make GPIO0 port low
        __delay_ms(500);
      
  }
}

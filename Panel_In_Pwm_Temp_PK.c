



//
/*
    //Setting Timer2
    //**************************************************
      // ????? ????? 2
    T2CON = 0x07;  // ????? ????? 2 ?? ????????? 1:128
    PR2 = 250;  // ????? ????? ????? 2
    TMR2IF = 0;  // ??? ???? ??? ???? ????? 2
    TMR2IE = 1;  // ???? ???? ???? ????? 2
    TMR2ON = 1;  // ???? ???? ????? 2
    //******************************************************************
    
     // ??????? ?????
   
    OSCCON1 = 0x60;  // ????? ?????? ????? ?? 32 ???????
    TRISCbits.TRISC0 = 0;  // ????? ??? RB0 ?? ????? ?????
    LATCbits.LATC0 = 0;  // ????? ????? ????? ?? ???
        TRISAbits.TRISA4 = 1;  // ????? ??? RA4 ?? ????? ????? (T1G)
    
    // ????? ????? 1
     // ????? ????? 1
    T1GCONbits.T1GSS = 0b00;  // ?????? ??? T1G ?? ????? ???? ?????? Gate
    //T1GCONbits.T1GGO = 1;     // ???? ???? Gate ????? 1
    T1GCONbits.T1GGO_nDONE = 1 ;  // ???? ???? Gate ????? 1
    T1GCONbits.T1GSPM = 0;    // ???? ?? ????
    T1GCONbits.T1GTM = 0;     // ???? ?????
    T1GCONbits.T1GPOL = 0;    // ????? ????
    T1GCONbits.TMR1GE = 1;    // ???? ???? Gate ????? 1
    T1CON = 0x31;  // ????? ????? 1 ?? ????????? 1:8
    TMR1H = 0;  // ???? ?????
    TMR1L = 0;
    TMR1IF = 0;  // ??? ???? ??? ???? ????? 1
    TMR1IE = 1;  // ???? ???? ???? ????? 1
    PEIE = 1;  // ???? ???? ???????? ?????
    GIE = 1;  // ???? ???? ???????? ?????
    INTCONbits.GIE = 1 ; 
    INTCONbits.PEIE = 1 ;
    PIE1bits.TMR1IE = 1 ;
    PIE1bits.TMR1GIE = 1 ;

*/
//
#include <xc.h>
#include <stdint.h>

#define _XTAL_FREQ 24000000     

#pragma config FEXTOSC = HS     // FEXTOSC External Oscillator mode Selection bits (HS (crystal oscillator) above 4 MHz)
#pragma config RSTOSC = EXT1X   // Power-up default value for COSC bits (EXTOSC operating per FEXTOSC bits )
#pragma config CLKOUTEN = OFF   // Clock Out Enable bit (CLKOUT function is disabled; I/O or oscillator function on OSC2)
#pragma config CSWEN = ON       // Clock Switch Enable bit (Writing to NOSC and NDIV is allowed)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)

// CONFIG2
#pragma config MCLRE = OFF      // Master Clear Enable bit (MCLR/VPP pin function is digital input; MCLR internally disabled; Weak pull-up under control of port pin's WPU control bit.)
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


// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>







    // Master Clear Enable bit (MCLR/VPP pin function is MCLR; Weak pull-up enabled)

#define tm1637_dio_pin LATAbits.LATA1
#define tm1637_clk_pin LATAbits.LATA0
#define tm1637_dio_tris TRISAbits.TRISA1
#define tm1637_clk_tris TRISAbits.TRISA0


// Set the TM1637 module data and clock pins:
#define trisConfiguration 0b00110000; // This config ONLY TM1637 GP4/5 pins are inputs, TM1637 module pullups will take high
#define tm1637dio TRISAbits.TRISA1                 // Set the i/o ports names for TM1637 data and clock here
#define tm1637dioTrisBit 1            // This is the bit shift to set TRIS for GP4
#define tm1637clk TRISAbits.TRISA0
#define tm1637clkTrisBit 0

//Variables:

const uint8_t tm1637ByteSetData = 0x40;        // 0x40 [01000000] = Indicate command to display data
const uint8_t tm1637ByteSetAddr = 0xC0;        // 0xC0 [11000000] = Start address write out all display bytes 
const uint8_t tm1637ByteSetOn = 0x88;          // 0x88 [10001000] = Display ON, plus brightness
const uint8_t tm1637ByteSetOff = 0x80;         // 0x80 [10000000] = Display OFF 
const uint8_t tm1637MaxDigits = 4;
const uint8_t tm1637RightDigit = tm1637MaxDigits - 1;
                                               // Used to output the segment data for numbers 0..9 :
const uint8_t tm1637DisplayNumtoSeg[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};
uint8_t tm1637Brightness = 5;                           // Range 0 to 7
uint8_t tm1637Data[] = {0, 0, 0, 0};   //Digit numeric data to display,array elements are for digits 0..3
uint8_t decimalPointPos = 99;          //Flag for decimal point (digits counted from left),if > MaxDigits dp off
uint8_t zeroBlanking = 1;              //If set true blanks leading zeros

//Function prototypes:
void initialise(void);
void tm1637StartCondition(void);
void tm1637StopCondition(void);
uint8_t tm1637ByteWrite(uint8_t bWrite);
void tm1637UpdateDisplay(void);
void tm1637DisplayOn(void);
void tm1637DisplayOff(void);
uint8_t getDigits(uint16_t number);   //Extracts decimal digits from integer, populates tm1637Data array


    
  
      

unsigned int frequency = 0;  // ????? ?????? ???? ????? ??????
float Freq = 0;  // ????? ?????? ???? ????? ??????
  unsigned int timerValue;
void __interrupt() ISR() {

//    if (TMR1IF  ){
//        
//       // unsigned int pwm_period = (TMR1H << 8) | TMR1L;
//        //frequency =pwm_period ;// _XTAL_FREQ / (4 * pwm_period); 
//       // frequency = (TMR1H << 8) | TMR1L;
//          TMR1IF = 0;
//               //TMR1H = 0;  // ???? ?????
//        //TMR1L = 0;
//    }
//    
//    if (TMR0IF  ){
//          TMR0IF = 0;
//           // TMR1GIF = 0;
//    //T1CONbits.TMR1ON = 0 ;
//    
//     // unsigned int pwm_period = (TMR1H << 8) | TMR1L;
//       // frequency =pwm_period ;// _XTAL_FREQ / (4 * pwm_period);    
//
//      //TMR1H = 0;  // ???? ?????
//       // TMR1L = 0;
//        
//        
//          TMR0H = 0;  // ???? ?????
//        TMR0L = 0;
//    //T1CONbits.TMR1ON = 1 ;
//   //LATCbits.LATC0 = ~LATCbits.LATC0;
//    }
//   
    if (TMR1IF)
    {
       
       TMR1IF = 0 ; 
    }
    if (TMR1GIF)
    {
      
        
     TMR1GIF = 0 ;   
     
//      LATCbits.LATC0 = ~LATCbits.LATC0;
      
    // TMR1IF = 0 ; 
      timerValue  = ((TMR1H << 8) | TMR1L)  ;
      // ????? ????? ????? ?? float
   // Freq = (float)timerValue;
     // Freq = (Freq * 1.8) * 2  ;
     // Freq =  Freq * 0.000001; 
      //Freq = 1 /  Freq ; 
     // frequency = (int)Freq;
      frequency = 253600 / timerValue ;
      
     // T1GCON |= T1GCONbits.T1GGO_nDONE;
                TMR1H = 0;  // ???? ?????
        TMR1L = 0;
    }
//    if (TMR2IF) {  // ????? ???? ????? 2
//        TMR2IF = 0;  // ??? ???? ??? ????
//        //LATCbits.LATC4 = ~LATCbits.LATC4;  // ????? ????? ??? RC0
//    }
//    
 
    
}




void main(void)
{

    initialise();  
     // ??????? ?????
  
    OSCCON1bits.NOSC = 0b011; // ?????? ????????? ?????
    OSCCON1bits.NDIV = 0b0000; // ???? ????? ??????
    OSCENbits.EXTOEN = 1; // ???? ???? ????????? ?????
    OSCFRQbits.HFFRQ = 0b110;


    PEIE = 1;  // ???? ???? ???????? ?????
    GIE = 1;  // ???? ???? ???????? ?????
 
        //Setting Timer2
    //**************************************************
      // ????? ????? 2
//    T2CON = 0x09;  // ????? ????? 2 ?? ????????? 1:128
//    PR2 = 700;  // ????? ????? ????? 2
//    TMR2IF = 0;  // ??? ???? ??? ???? ????? 2
//    TMR2IE = 1;  // ???? ???? ???? ????? 2
//    TMR2ON = 1;  // ???? ???? ????? 2
//    
   
     ANSELAbits.ANSA0 = 0;
      ANSELAbits.ANSA1 = 0;
     TRISAbits.TRISA0 = 1;
      TRISAbits.TRISA1 = 1;
      
      
      
      TRISCbits.TRISC0 = 0;
      TRISCbits.TRISC5 = 0;
      
    
    //Setting Timer1
    //***************************************************
      // ??????? ?????
   
    OSCCON1 = 0x60;  // ????? ?????? ????? ?? 32 ???????
   // TRISCbits.TRISC0 = 0;  // ????? ??? RB0 ?? ????? ?????
    //LATCbits.LATC0 = 0;  // ????? ????? ????? ?? ???
    //TRISAbits.TRISA4 = 1;  // ????? ??? RA4 ?? ????? ????? (T1G)
    //ANSELAbits.ANSA4 = 0 ;
    
      TRISAbits.TRISA2 = 1; // ????? ???? RA2 ?? ????? ????? (T1G)
    ANSELAbits.ANSA2 = 0; // ??????? ???? ?????? ???? RA2
    
    
    // ????? ????? 1
     // ????? ????? 1
   // T1GCONbits.T1GSS = 0b00;  // ?????? ??? T1G ?? ????? ???? ?????? Gate
    //T1GCONbits.T1GSS0 = 0 ;
   // T1GCONbits.T1GSS1 = 0 ;
    
    
      T1GCONbits.T1GSS0 = 0; // ????? ??? ????? ????? 1 ?? RA2
    T1GCONbits.T1GSS1 = 0;
    
    T1GPPS = 0x02; // ????? ????? ????? 1 ?? ??? A2
    
    //T1GCONbits.T1GGO = 1;     // ???? ???? Gate ????? 1
    T1GCONbits.T1GGO_nDONE = 1 ;  // ???? ???? Gate ????? 1
    T1GCONbits.T1GSPM = 0;    // ???? ?? ????
    T1GCONbits.T1GTM = 0;     // ???? ?????
    T1GCONbits.T1GPOL = 0;    // ????? ????
    T1GCONbits.TMR1GE = 1;    // ???? ???? Gate ????? 1
   T1CON = 0x31;  // ????? ????? 1 ?? ????????? 1:8
   
  //T1CONbits.TMR1CS = 0b01; // ?????? ???? ????? ???? ????? 1
//T1CONbits.T1CKPS = 0b00; // ????? ??????????????? ?? 1:1
//T1GCONbits.TMR1GE = 0;   // ??????? ???? ??? ????? 1
//T1CONbits.TMR1ON = 1;    // ???? ???? ????? 1

    TMR1H = 0;  // ???? ?????
    TMR1L = 0;
    TMR1IF = 0;  // ??? ???? ??? ???? ????? 1
    TMR1IE = 1;  // ???? ???? ???? ????? 1
//
//    INTCONbits.GIE = 1 ; 
//    INTCONbits.PEIE = 1 ;
//    PIE1bits.TMR1IE = 1 ;
 
    PIE1bits.TMR1GIE = 1 ; 
    
    
  
    // ????? ????? 0 ???? ????? ???? ?? ?? ?????
//    T0CON0bits.T0EN = 1 ;
//   T0CON1 = 0x07; // ??????????????? 1:256
//    TMR0 = 0;          // ???? ???? ????? 0
//    TMR0IE = 1;        // ???? ???? ???? ????? 0  
//    
    
    
    
    
    
    
    
    
    
    //*****************************************************
    
    
  uint16_t displayedInt=0;  //Beware 65K limit if larger than 4 digit display,consider using uint32_t
  uint16_t ctr = 0;

  
    
 
   
    
    
    
  __delay_ms(100);

  getDigits(displayedInt);
  tm1637UpdateDisplay();
  
    // ????? ????? PWM
    unsigned int dutyCycle = 127;  // ????? ????? Duty Cycle (50%)
    
 
    
  while(1)
    {
//     LATCbits.LATC5 = 1;
//       __delay_ms(3000);
//       LATCbits.LATC5 = 0;
//       __delay_ms(1000);
      
     // LATCbits.LATC0 = ~LATCbits.LATC0;
      __delay_ms(500);
 displayedInt = frequency ;
      
            if (displayedInt >= 270) { // 77 DARAGE
            LATCbits.LATC0 = 1;  // ???? ???? ??
            LATCbits.LATC5 = 1;  // ???? ???? ??
        } else if (displayedInt <= 255) { // 71 DARAGE
            LATCbits.LATC0 = 0;  // ????? ???? ??
            LATCbits.LATC5 = 0;  // ????? ???? ??
       
        }  

  
     
           
      if (getDigits(displayedInt))
      { 

        tm1637UpdateDisplay();
      }
    }
}

/*********************************************************************************************
 tm1637UpdateDisplay()
 Publish the tm1637Data array to the display
*********************************************************************************************/
void tm1637UpdateDisplay()
{   
    uint8_t tm1637DigitSegs = 0;
    uint8_t ctr;
    uint8_t stopBlanking = !zeroBlanking;            // Allow blanking of leading zeros if flag set
            
    // Write 0x40 [01000000] to indicate command to display data - [Write data to display register]:
    tm1637StartCondition();
    tm1637ByteWrite(tm1637ByteSetData);
    tm1637StopCondition();

    // Specify the display address 0xC0 [11000000] then write out all 4 bytes:
    tm1637StartCondition();
    tm1637ByteWrite(tm1637ByteSetAddr);
    for (ctr = 0; ctr < tm1637MaxDigits; ctr ++)
    {
        tm1637DigitSegs = tm1637DisplayNumtoSeg[tm1637Data[ctr]];
        if (!stopBlanking && (tm1637Data[ctr]==0))  // Blank leading zeros if stop blanking flag not set
            {
               if (ctr < tm1637RightDigit)          // Never blank the rightmost digit
                  tm1637DigitSegs = 0;              // Segments set 0x00 gives blanked display numeral
            }
        else
        {
           stopBlanking = 1;                    // Stop blanking if have reached a non-zero digit
           if (ctr==decimalPointPos)            // Flag for presence of decimal point, digits 0..3
           {                                    // No dp display if decimalPointPos is set > Maxdigits
               tm1637DigitSegs |= 0b10000000;   // High bit of segment data is decimal point, set to display
           }
        }
        tm1637ByteWrite(tm1637DigitSegs);       // Finally write out the segment data for each digit
    }
    tm1637StopCondition();

    // Write 0x80 [10001000] - Display ON, plus brightness
    tm1637StartCondition();
    tm1637ByteWrite((tm1637ByteSetOn + tm1637Brightness));
    tm1637StopCondition();
}


/*********************************************************************************************
 tm1637DisplayOn()
 Send display on command
*********************************************************************************************/
void tm1637DisplayOn(void)
{
    tm1637StartCondition();
    tm1637ByteWrite((tm1637ByteSetOn + tm1637Brightness));
    tm1637StopCondition();
}


/*********************************************************************************************
 tm1637DisplayOff()
 Send display off command
*********************************************************************************************/
void tm1637DisplayOff(void)
{
    tm1637StartCondition();
    tm1637ByteWrite(tm1637ByteSetOff);
    tm1637StopCondition();
}

/*********************************************************************************************
 tm1637StartCondition()
 Send the start condition
*********************************************************************************************/
void tm1637StartCondition(void) 
{
   // TRISA &= ~(1<<tm1637dioTrisBit);  //Clear data tris bit
    tm1637_dio_pin = 0 ;
    tm1637dio = 0;                     //Data output set low
    __delay_us(100);
}


/*********************************************************************************************
 tm1637StopCondition()
 Send the stop condition
*********************************************************************************************/
void tm1637StopCondition() 
{
    //TRISA &= ~(1<<tm1637dioTrisBit);   // Clear data tris bit
    tm1637_dio_pin = 0 ;
    tm1637dio = 0;                      // Data low
    __delay_us(100);
   // TRISA |= 1<<tm1637clkTrisBit;      // Set tris to release clk
    tm1637_clk_pin = 1 ;
    //tm1637clk = 1;
    __delay_us(100);
    // Release data
   // TRISA |= 1<<tm1637dioTrisBit;      // Set tris to release data
    tm1637_dio_pin = 1 ;
    __delay_us(100);
}


/*********************************************************************************************
 tm1637ByteWrite(char bWrite)
 Write one byte
*********************************************************************************************/
uint8_t tm1637ByteWrite(uint8_t bWrite) {
    for (uint8_t i = 0; i < 8; i++) {
        // Clock low
       // TRISA &= ~(1<<tm1637clkTrisBit);   // Clear clk tris bit
        tm1637_clk_pin = 0 ;
        tm1637clk = 0;
        __delay_us(100);
        
        // Test bit of byte, data high or low:
        if ((bWrite & 0x01) > 0) {
           // TRISA |= 1<<tm1637dioTrisBit;      // Set data tris 
            tm1637_dio_pin = 1 ;
        } else {
           // TRISA &= ~(1<<tm1637dioTrisBit);   // Clear data tris bit
            tm1637_dio_pin = 0 ;
            tm1637dio = 0;
        }
        __delay_us(100);

        // Shift bits to the left:
        bWrite = (bWrite >> 1);
       // TRISA |= 1<<tm1637clkTrisBit;      // Set tris so clk goes high
        tm1637_clk_pin = 1 ;
        __delay_us(100);
    }

    // Wait for ack, send clock low:
   // TRISA &= ~(1<<tm1637clkTrisBit);      // Clear clk tris bit
    tm1637_clk_pin = 0 ;
    tm1637clk = 0;
   // TRISA |= 1<<tm1637dioTrisBit;         // Set data tris, makes input
    tm1637_dio_pin = 1 ;
    tm1637dio = 0;
    __delay_us(100);
    
   // TRISA |= 1<<tm1637clkTrisBit;         // Set tris so clk goes high
    tm1637_clk_pin = 1 ;
    __delay_us(100);
    uint8_t tm1637ack = tm1637dio;
    if (!tm1637ack)
    {
       // TRISA &= ~(1<<tm1637dioTrisBit);  // Clear data tris bit
        tm1637_dio_pin = 0 ;
        tm1637dio = 0;
    }
    __delay_us(100);
   // TRISA &= ~(1<<tm1637clkTrisBit);      // Clear clk tris bit, set clock low
    tm1637_clk_pin = 0 ;
    tm1637clk = 0;
    __delay_us(100);

    return 1;
}


/*********************************************************************************************
  Function called once only to initialise variables and
  setup the PIC registers
*********************************************************************************************/
void initialise()
{
 
    // ????? ??????? ?? ????? ?????
    tm1637_dio_tris = 0;
    tm1637_clk_tris = 0;
    
 
    CM1CON0 = 0x00;  // ??????? ???? ???????????
    CM2CON0 = 0x00;
 
    // old timer/interrupt/pullup setup was here
    
    
      // ???? ???? ?????????? ?????? ?????
    //WPUA0 = 1;
    //WPUA1 = 1;
    //OPTION_REGbits.nWPUEN = 0;  // ???? ???? ?????????? ??????
    
    
    
     // ????? ?????? ?? ????? ?????
    //TRISA5 = 1;  // RA5 ?? ????? ????? (???? ??????)
   // TRISA4 = 1;  // RA4 ?? ????? ????? (???? ????)
    
}


/*************************************************************************************************
 getDigits extracts decimal digit numbers from an integer for the display, note max displayed value is 
 9999 for 4 digit display, truncation of larger numbers. Larger displays: note maximum 65K as coded with 
 16 bit parameter - probable need to declare number as uint32_t if coding for a 6 digit display  
 ************************************************************************************************/

uint8_t getDigits(uint16_t number)
{ 
    int8_t ctr = (tm1637RightDigit);            // Start processing for the rightmost displayed digit
    for (uint8_t ctr2 = 0; ctr2 < tm1637MaxDigits; ctr2++)
    {
        tm1637Data[ctr2]=0;      //Initialise the display data array with 0s
    }
    while(number > 0)            //Do if number greater than 0, ie. until all number's digits processed
    {
        if (ctr >= 0)
        {
           uint16_t modulus = number % 10;      // Split last digit from number
           tm1637Data[ctr] = (uint8_t)modulus;  // Update display character array
           number = number / 10;                // Divide number by 10
           ctr --;                              // Decrement digit counter to process number from right to left
        }
        else
        {
           number = 0;                          // Stop processing if have exceeded display's no of digits
        }
    }
    return 1;
}

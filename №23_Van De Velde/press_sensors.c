/*****************************************************
Chip type               : ATtiny13A
******************************************************/

#include <tiny13a.h>
#include <delay.h>

unsigned char cycle=0;
unsigned char up=0;
// Timer 0 overflow interrupt service routine
interrupt [TIM0_OVF] void timer0_ovf_isr(void)
    {
        if (PINB.3==1)
        {
            mode = 1;
        };
        if (PINB.3==0)&&(~PINB.4)
        {
            mode = 1;
        };
        if (PINB.4==1)
        {
            mode = 2;
            delay_ms(1000);
            mode = 3;
            up=1;
        };
        if (up==1)&&(~PINB.3)
        {
            mode = 3;    
        };
        if (up==1)&&(PINB.3)
        {
            mode = 2;
            up=0;    
        };               
    }
 
void start (void)
    {
        switch (mode)
        {
            case 1:
				PORTB.0 = 1;
				PORTB.1 = 0;
			case 2:
				PORTB.0 = 0;
				PORTB.1 = 0;
			case 3:
				PORTB.0 = 0;
				PORTB.1 = 1;
			case 4:
				PORTB.0 = 0;
				PORTB.1 = 0;
                cycle=0;
            break;
       
            default:
        };
 
        /*PORTB.0=1;
        delay_ms(100);
        PORTB.0=0;
        delay_ms(30);
        PORTB.1=1;
        delay_ms(60); 
        PORTB.1=0;   */  
    }
 
void main(void)
{
// Declare your local variables here

// Crystal Oscillator division factor: 1
/*#pragma optsize-
CLKPR=0x80;
CLKPR=0x00;
#ifdef _OPTIMIZE_SIZE_
#pragma optsize+
#endif
*/
// Input/Output Ports initialization
// Port B initialization
// Func5=In Func4=In Func3=In Func2=In Func1=Out Func0=Out 
// State5=T State4=T State3=T State2=T State1=0 State0=0 
PORTB=0x00;
DDRB=0x03;

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: 7,813 kHz
// Mode: Normal top=0xFF

TCCR0A=0x00;
TCCR0B=0x05;


// Timer/Counter 0 Interrupt(s) initialization
TIMSK0=0x02;


#asm("sei")

while (1)
      {
            if (PINB.2==1)
            {
                delay_ms(20);
                if (PINB.2==1)
                {
                   cycle=1; 
                };    
            };            
            
            if (cycle==1)
            {
                start();
            }
      }
}


/*****************************************************
Chip type               : ATtiny13A
FUSE BITS: low: 7A high: FB     9.6MHz 2.7V without CKDIV 
******************************************************/

#include <tiny13a.h>
#include <delay.h>

//unsigned char stop;

// Timer 0 overflow interrupt service routine
/*interrupt [TIM0_OVF] void timer0_ovf_isr(void)
    {
        
    }
    */
void on (void)
    {
        PORTB.0=1;
        delay_ms(20000);
        PORTB.0=0;
        delay_ms(1000); 
        PORTB.1=1;
        delay_ms(5000); 
        PORTB.1=0;     
    }
 
void main(void)
{
// Declare your local variables here

// Crystal Oscillator division factor: 1
#pragma optsize-
CLKPR=0x80;
CLKPR=0x00;
#ifdef _OPTIMIZE_SIZE_
#pragma optsize+
#endif

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

//TCCR0A=0x00;
//TCCR0B=0x05;


// Timer/Counter 0 Interrupt(s) initialization
//TIMSK0=0x02;


//#asm("sei")

while (1)
      {
            if (PINB.4==0)
            {
                delay_ms(100);
                if (PINB.4==0)
                {
                    if (PINB.2==0)
                    {
                        delay_ms(50);
                        if (PINB.2==0)
                        {
                            on(); 
                        };    
                    };
                };
            }; 
      }
}


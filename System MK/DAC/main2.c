#include "Header.h"

#define SIGNAL_DELAY 80

#define SIGNAL_DELAY1 157600
/// Можно определить маску для работы с нужными битами
#define DIG_OUT_MASK  ((1<<PD5)|(1<<PD6))

void init_DAC( void )
{  ///////////////////////////
  DDRB |= (1<<PB5)|(1<<PB4)|(1<<PB3)|(1<<PB2);
  PORTB = (1<<PB5)|(1<<PB4)|(1<<PB3)|(1<<PB2);

}

void CLK( void )
{
  char  temp, tem1;
  temp = ~PORTD;
  temp &= DIG_OUT_MASK;
  tem1 =  PORTD & (~DIG_OUT_MASK  );
  temp |= tem1 ;
  PORTD = temp;
}

void write_DAC( u_int data )
{
  char  temp, tem1;
  temp = ~PORTD;
  temp &= DIG_OUT_MASK;
  tem1 =  PORTD & (~DIG_OUT_MASK  );
  temp |= tem1 ;
  PORTD = temp;
}

void main( void )
{
  /// включим подтяжку на всех выводах МК
   PORTB = 0xFF;
   PORTC = 0xFF;
   PORTD = 0xFF;
  ///////////////////////////
  DDRD |= (1<<PD5)|(1<<PD6);
  PORTD = (1<<PD5)|(0<<PD6);
  DDRB |= (1<<PB0);
  PORTB = (1<<PB0);

/// основной цикл
while(1){

  for(int i=0; i<10 ; i++){
     PORTB = (0<<PB0);
     CLK();

     __delay_cycles(SIGNAL_DELAY);

     CLK();

     __delay_cycles(SIGNAL_DELAY);
     __delay_cycles(SIGNAL_DELAY);
  }

    PORTB = (1<<PB0);

     __delay_cycles(SIGNAL_DELAY1);

}

}







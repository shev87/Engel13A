#include "Header.h"

/// Можно определить маску для работы с нужными битами
#define DIG_OUT_MASK  ((1<<PD5)|(1<<PD6)|(1<<PD7))


// Процедура настройки таймера 0
void init_Timer_0(void)
{
  TCCR0 = (1<<CS02)|(1<<CS00);  // Timer Clock = system clock / 1024
// сбросим флаг переполнения если установлен
  TIFR  = 1<<TOV0;		// Clear TOV0 / Clear pending interrupts
// разрешаем прерывания от события переполнение таймера 0
  TIMSK = 1<<TOIE0;             // Enable Timer 0 Overflow Interrupt
}


// процедура прерывания
/// формирует меандр на PD5 и PD7 период = 2*system_clock/1024/356
#pragma vector=TIMER0_OVF_vect
__interrupt void Timer_0_ovfEVENT(void)
{
  PORTD ^= ((1<<PD5)|(1<<PD7));
}

void main( void )
{
  /// включим подтяжку на всех выводах МК
   PORTB = 0xFF;
   PORTC = 0xFF;
   PORTD = 0xFF;

  /// определим направление - ВЫХОД
  DDRD |= DIG_OUT_MASK;
  /// предустановка бит порта - теперь они работают как источник 20мА
  /// напряжение 5В
  PORTD |= DIG_OUT_MASK;

  // Процедура настройки таймера 0
  init_Timer_0();

  /// разрешаем прерывания
  _SEI();

  ///////////////////////////
  /// основной цикл
  while(1){
    /// встроленная функция эквиваелент команды nop
    /// ничего не делаем
    _NOP();
  }
}

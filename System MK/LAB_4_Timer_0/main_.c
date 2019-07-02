#include "Header.h"

/// ����� ���������� ����� ��� ������ � ������� ������
#define DIG_OUT_MASK  ((1<<PD5)|(1<<PD6)|(1<<PD7))


// ��������� ��������� ������� 0
void init_Timer_0(void)
{
  TCCR0 = (1<<CS02)|(1<<CS00);  // Timer Clock = system clock / 1024
// ������� ���� ������������ ���� ����������
  TIFR  = 1<<TOV0;		// Clear TOV0 / Clear pending interrupts
// ��������� ���������� �� ������� ������������ ������� 0
  TIMSK = 1<<TOIE0;             // Enable Timer 0 Overflow Interrupt
}


// ��������� ����������
/// ��������� ������ �� PD5 � PD7 ������ = 2*system_clock/1024/356
#pragma vector=TIMER0_OVF_vect
__interrupt void Timer_0_ovfEVENT(void)
{
  PORTD ^= ((1<<PD5)|(1<<PD7));
}

void main( void )
{
  /// ������� �������� �� ���� ������� ��
   PORTB = 0xFF;
   PORTC = 0xFF;
   PORTD = 0xFF;

  /// ��������� ����������� - �����
  DDRD |= DIG_OUT_MASK;
  /// ������������� ��� ����� - ������ ��� �������� ��� �������� 20��
  /// ���������� 5�
  PORTD |= DIG_OUT_MASK;

  // ��������� ��������� ������� 0
  init_Timer_0();

  /// ��������� ����������
  _SEI();

  ///////////////////////////
  /// �������� ����
  while(1){
    /// ����������� ������� ����������� ������� nop
    /// ������ �� ������
    _NOP();
  }
}

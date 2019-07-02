#include "timers.h"
#include "INDIKATE.h"

//// ��������� � ����������� �������� 1 ��� ���������� ����������������
/// �������� � ������ FAST_PWM 
/// TOP - � �������� ICR  ��������� � OCR1A
void Init_TimerT1(void)
{
  /// ��������� ����� ������ ������ ��1� 
  /// � ��� ���
   TCCR1A = (1<<COM1A1)|(0<<COM1A0) /// ����� ������ ������ OC1A
             /// ����� ��1� ��� ��������� ���������
          | (0<<WGM10)|(1<<WGM11);
   TCCR1B = (1<<WGM13)|(1<<WGM12);  /// ����� fast PWM 
   /// ���������� �������� ���
   ICR1   = PWM_TOP_VAL;   /// TOP - �� ���� �������
   OCR1A  = 0;             /// �������� ��� - 0
   TCNT1  = 0;
   TCCR1B |= (1<<CS10);    /// ��������� ������   
}
/// �������� ������� ��������/��������� ��������������� 
///#define TURN_OFF_HI_VOLT  TCCR1B &= ~(7<<CS10);   TCNT1 = 0;          

//// ��������� � ���������� �������� 0 ��� ������� ��������� 
//// ���������� ���������
/// � ��������� � ������ ������� �� �������� �����

///////////////////////////////
/// ������� ��� ���������� ��������� � ����������
#define MOSFET_ON_ChargeCAP PORTB |= (1<<PB0);
#define MOSFET_OFF          PORTB &= ~(1<<PB0);
#define TRIAK_ON_IGNITION   PORTC |= ((1<<PC2)|(1<<PC3));
#define TRIAK_OFF           PORTC &= ~((1<<PC2)|(1<<PC3));

///////////////////////////////
/// �������� �� ������ ������� 0 � ���������� INT0
/// � ������ ���������� ��������� � ��������
void Init_Timer0_and_PORTS(void)
{
  /// �������� ������
  /// PB0 - ���������� ���������
  /// PB1 - ���������� ����������������
  PORTB &= ~((1<<PB1)|(1<<PB0));  /// �������� ���������� ���������������
  DDRB |= (1<<PB0)|(1<<PB1);      /// �������� ����������� �����
  /// P�2, P�3 - ���������� ����������
  TRIAK_OFF;
  DDRC |= ((1<<PC2)|(1<<PC3));
  PORTC &= ~(1<<PC0);  /// ��������� �������� � ������������� ������
  /// �������� ���������� �� INT0
  ///The rising edge of INT0 generates an interrupt request.
  MCUCR |= (1<<ISC01)|(1<<ISC00);
  GICR  |= (1<<INT0);  /// ��������� ���������� �� INT0
  
  Stop_T0;             /// ����� ������� 0
  TCNT0 = 0;
}

/// ��������� ����� ����� ����� �����
/// ��������� ������ �� ������ ����/64 
/// � ����� ����� 300 ���
#define _TIME_400mks   0xCE
#define _TIME_600mks   0xB6
/// ����� ����� 600 ���
#define _TIME_800mks   0x9C
/// ����� ��� ���������� ���������� �������� 2ms
#define _TIME_1ms       0x80
#define _TIME_2ms       0x00


/// ��������� �� � - ���������� ������� ������������ ������� 0
FPTR_vv   Timer0_Checker;
/// ��� ������� ��������� �� ��������� Timer0_Checker
/// ����� ��� � ������� �� ���������

/// ���������� INT0 ���������� ������������ �����...
#pragma vector = INT0_vect
__interrupt void ON_Start_Ignition(void)
{
  TRIAK_ON_IGNITION;  /// ������� ��������
  GICR &= ~(1<<INT0);  /// �������� ���������� �� INT0
  /// ��������� ���������� ��� ������� 0 - Timer0_Checker
  Timer0_Checker = &ON_End_Ignition_Time;   
  Stop_T0;            /// ����� ����� ������� � �������
  /// ��������� ������ 0 �� ������������ ��������� �����
  Start_T0(_TIME_600mks);
}

/// 1 - ���������� ����� ��������� ...
void ON_End_Ignition_Time(void)
{
/// ���� ������ �� ��������� - �������
  if((TIFR&(1<<TOV0)) == 0) return;
  Stop_T0;              /// ����� ����� ������� � �������
  TRIAK_OFF;   /// ��������� ��������
/// ��������� ������ ��������� ���������� 2
  Timer0_Checker = &ON_End_PAUSE_Time;   
/// ��������� ����� �� �������� ��������
  Start_T0(_TIME_400mks);
}

/// 2 - ���������� ����� ����� �������� ���������
/// �������� �������
/// ��� ��������� RC ������� 3RC = 0,8�� �� 2�� ���������!!!!
void ON_End_PAUSE_Time(void)
{
/// ���� ������ �� ��������� - �������
  if((TIFR&(1<<TOV0)) == 0) return;
  Stop_T0;              /// ����� ����� ������� � �������
/// ��������� ������� - � �������� �������
  MOSFET_ON_ChargeCAP;
  Timer0_Checker = &ON_End_PAUSE_2NEW_PULSE;   
/// ��������� ����� �� ����� �������
  Start_T0(_TIME_2ms);
}

/// 3 - ���������� ���������� �� INT0
/// ��� ����������� ������� �������� ���������
void ON_End_PAUSE_2NEW_PULSE(void)
{
/// ���� ������ �� ��������� - �������
  if((TIFR&(1<<TOV0)) == 0) return;
  Stop_T0;              /// ����� ����� ������� � �������
  /// ������ 2 �� ���������� �� 400��� - �������� ��������
  /// ��� �����. ���������
  MOSFET_OFF;   /// 1 �������� ���������� ������ !!!!!!
  Start_T0(_TIME_400mks);
  Timer0_Checker = &ON_ENABLE_NEW_PULSE;   
}

/// 4 - ������������ ������� ���������, �����, �������� �������
/// �������� ��������, ������, �������� ����� �������
void ON_ENABLE_NEW_PULSE(void)
{
  Timer0_Checker = 0; /// ����� ����������� ������� � 0
  GIFR = 1<<INTF0;    /// ������� ���� �� INT0
  GICR |= (1<<INT0);  /// �������� ���������� �� INT0
}


/// ����� 
/***********************************************************************/



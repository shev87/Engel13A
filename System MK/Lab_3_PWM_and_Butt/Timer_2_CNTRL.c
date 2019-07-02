#include "Timer_2_CNTRL.h"

//// ��� �� ������������ �������� �������� �������
//// ����� ������������ � ������������� �������
//// �������� 1,8,32,64,128,256,1024

//// ���������� ����� �� ���� ������ �������� ��
/// ������������ �������� �������� �������
/// ����� ������������ �� ������ ���� ����� 1

/// ����� ������������� ������� ���
/// Noverflow (1) = Fquarz*TIME_SETTED/(CountVAL*Kprescaler)
/// ������
/// Kprescaler >=  Fquarz*TIME_SETTED/CountVAL
/// ��� CountVAL - ������� �������� T2 = 256
/// ����� ���� �� ���������� Kprescaler
/// �������� ����������� � ������� ���������
/// ������������ ��� COMPARE_VAL = Fquarz*TIME_SETTED/Kprescaler


//// ����� �������� ��� ������������
#if (TIME_INTERVAL*SYSTEM_CLOCK/25600000U) < 1
#define OCR2VAL		(TIME_INTERVAL*SYSTEM_CLOCK/100000U/1)
#define TIMER_2_START_MASK		0x01

//// ����� �������� ���� ����������� �������� ����� 8
#elif (TIME_INTERVAL*SYSTEM_CLOCK/25600000U/8) < 1
#define OCR2VAL		(TIME_INTERVAL*SYSTEM_CLOCK/100000U/8)
#define TIMER_2_START_MASK		0x02

//// ����� �������� ���� ����������� �������� ����� 32
#elif (TIME_INTERVAL*SYSTEM_CLOCK/25600000U/32) < 1
#define OCR2VAL		(TIME_INTERVAL*SYSTEM_CLOCK/100000U/32)
#define TIMER_2_START_MASK		0x03

//// ����� �������� ���� ����������� �������� ����� 64
#elif (TIME_INTERVAL*SYSTEM_CLOCK/25600000U/64) < 1
#define OCR2VAL		(TIME_INTERVAL*SYSTEM_CLOCK/100000U/64)
#define TIMER_2_START_MASK		0x04

//// ����� �������� ���� ����������� �������� ����� 128
#elif (TIME_INTERVAL*SYSTEM_CLOCK/25600000U/128) < 1
#define OCR2VAL		(TIME_INTERVAL*SYSTEM_CLOCK/100000U/128)
#define TIMER_2_START_MASK		0x05

//// ����� �������� ���� ����������� �������� ����� 256
#elif (TIME_INTERVAL*SYSTEM_CLOCK/25600000U/256) < 1
#define OCR2VAL		(TIME_INTERVAL*SYSTEM_CLOCK/100000U/256)
#define TIMER_2_START_MASK		0x06

//// ����� �������� ���� ����������� �������� ����� 1024
#elif (TIME_INTERVAL*SYSTEM_CLOCK/25600000U/1024) < 1
#define OCR2VAL		(TIME_INTERVAL*SYSTEM_CLOCK/100000U/1024)
#define TIMER_2_START_MASK		0x07

//// ������ ��������	
#else
#error "�������� ����� ������������ -TIME_INTERVAL- �2 ������� ������"
#define OCR2VAL				0x00
#define TIMER_2_START_MASK		0x00

#endif
///////////////////////////////
/// �� ������ ���� ����������� �����
/// OCR2VAL � TIMER_2_START_MASK
/// ������� ��������� ������������ ������� 2 ���
/// ������������ ��������� ���������
/// ������� ��� ���� �������� �� ����� ����� ��������� �������
/// � � ������ ����������� �� 1 ��������� �������� ��������
/// � �� 1024 � 8��� ����� ���� 128���

#define TIMER_2_START	TCCR2 |= TIMER_2_START_MASK;
#define TIMER_2_STOP	TCCR2 &= ~0x07;


//// ��������� ������� 2 �� ��������� ���������� ���������
/// �� ����� ������ ����� ���������� 20�� ���������
void Timer2_INIT(void)
{
    TIMER_2_STOP; 	/// �� ������ ������		
    TCCR2 = (1<<WGM21); /// ����� ������ ���� �� �������� ���������
    OCR2 = (char)OCR2VAL; /// �������� ������������� ��������� TIME_INTERVAL
    TCNT2 = 0;
}
//// ����� ����� ���������� ���������
//// ������ �� ������ �������� �������� �������
u_char Timer2_CHECK(void)
{
  if(TIFR&(1<<OCF2)){
     TIFR = (1<<OCF2); /// ������� ����
     return 1;
  }
  return 0;
}
//// ������ �������
void Timer2_START(void)
{
	TIMER_2_START;
}
//// ������� �������
void Timer2_STOP(void)
{
	TIMER_2_STOP;
}

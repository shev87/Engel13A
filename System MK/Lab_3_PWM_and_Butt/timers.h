#ifndef _TIMERS_H_
#define _TIMERS_H_

#include "types.h"
/// ��������� �� � - ���������� ������� ������������ ������� 0
extern FPTR_vv   Timer0_Checker;

/////////////////////////////////////////////
/// ��������� �������� ��� ����
/// ������ ��� ����� 127 �����
#define PWM_TOP_VAL       0x7F
/// ������� ������ ��� ������� ����� �� ��������
/// ��� ��������� �������� 270�
#define PWM_UP_VAL        50

/// ������� ������ ��� ��� ��������� �������� 240�
///#define PWM_UP_VAL        (PWM_TOP_VAL/3)
/// ������ ������ ���
#define PWM_LOW_VAL       (PWM_UP_VAL/20)
/// 10% �� ������� ������� ���
#define PWM_10pers_VAL    (PWM_UP_VAL/10)
/// 30% �� ������� ������� ���
#define PWM_30pers_VAL    (PWM_UP_VAL/3)

//// ��������� � ����������� �������� 1 ��� ���������� ����������������
/// �������� � ������ FAST_PWM 
/// TOP - � �������� ICR  ��������� � OCR1A
extern void Init_TimerT1(void);
/// �������� �� ������ ������� 0 � ���������� INT0
/// � ������ ���������� ��������� � ��������
extern void Init_Timer0_and_PORTS(void);

/// �������� ������� ��������/��������� ��������������� 
#define TURN_OFF_HI_VOLT  OCR1A  = 0;
/// ��� ������� ��������� �� ��������� Timer0_Checker
/// ����� ��� � ������� �� ���������

/// 1 - ���������� ����� ��������� ...
extern void ON_End_Ignition_Time(void);
/// 2 - ���������� ����� ����� �������� ���������
extern void ON_End_PAUSE_Time(void);
/// 3 - ���������� ���������� �� INT0
/// ��� ����������� ������� �������� ���������
extern void ON_End_PAUSE_2NEW_PULSE(void);
/// 4 - ������������ ������� ���������, �����, �������� �������
/// �������� ��������, ������, �������� ����� �������
extern void ON_ENABLE_NEW_PULSE(void);


/// ������� ������� 0 � ����� �����
#define Stop_T0   {TCCR0 = 0; TIFR = (1<<TOV0);}
/// ������ ������� 0 �� �������� �����
/// ��������� ������ �� ������ ����/64 
#define Start_T0(Time)  {TCNT0 = Time; TCCR0 = 3;}


#endif /// _TIMERS_H_







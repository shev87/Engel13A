#ifndef _TIMER1_H_
#define _TIMER1_H_

#include "Header.h"
/// ��������� �� � - ���������� ������� ������������ ������� 0
extern FPTR_vv   Timer0_Checker;

/////////////////////////////////////////////
/// ��������� �������� ��� ����
/// ������ ���
#define PWM_TOP_VAL       0x3FF
/// ������� ������ ���
#define PWM_UP_VAL        0x3FF


//// ��������� � ����������� �������� 1
/// �������� � ������ FAST_PWM
/// TOP - � �������� ICR  ��������� � OCR1A
extern void Init_TimerT1(void);


#endif /// _TIMERS_H_







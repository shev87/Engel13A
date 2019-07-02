#ifndef Timer_2_CNTRL_H
#define Timer_2_CNTRL_H

#include "Header.h"
/// ��������� ����� ������� ����� �������� � �������� ���
/// ����� �������� 100��� �������� 10*10���....
#define TIME_INTERVAL		10

//// ��������� ������� 2 �� ��������� ���������� ���������
extern void Timer2_INIT(void);
//// ����� ����� ���������� ���������
//// ������ �� ������ �������� �������� �������
extern u_char Timer2_CHECK(void);
//// ������ �������
extern void Timer2_START(void);
//// ������� �������
extern void Timer2_STOP(void);

#endif  ///Timer_2_CNTRL_H

#ifndef _SHow_FUN_H_
#define _SHow_FUN_H_

#include "Header.h"

#define   PORT_INI_SHOW DDRB    // ����� ���� ����������� ��� ������ ����� ���
#define   PORT_SHOW     PORTB   // � ����� ���� ���������� ���� ���
#define   PIN_SHOW      PB0     // � ����� ����� ����� ���������� ���� ���

/// ������� ���� ��� ��������� ����������
extern void show_init(void);

//// ������� ������� �� ����� ��������
//// ��� �� ���������� ��� �������������
extern void show_result(unsigned int VAL);

#endif /// _SHow_FUN_H_


#ifndef _INDIKATE_H
#define _INDIKATE_H

#include "Header.h"

//////////////////////////////////////////////////
// ������ ��� ��������� � ���������� ���� � �����
#define SET_I_BIT    (LEDPORT |= (1<<LED))
#define CLR_I_BIT    (LEDPORT &= ~(1<<LED))

/////////////////////////////////////////////////////
/// ����� ��������� ����������
#define LED_IS_OFF        0
#define LED_1SHORT        1
#define LED_2SHORT        2
#define LED_3SHORT        3
#define LED_FASTBLINK     4
#define LED_IS_ON         5
/// ���� � ��� �������� �� ���� ������� ����������
#define LED_1SHORT_SH     6
#define LED_2SHORT_SH     7
#define LED_SLOWBLINK     8

//////////////////////////////////////////////////
//// ��������� ��������� ��������� ����� ������
extern void InitIndikate(void);
////////////////////////////////////
/// � ���������� ����� ��������� ��� ����� ������ LED
/// ��� ���������� ������� ������ ��������� - ���� ��
/// ������������ === /// ����� ��������� ����������
extern void Set_INDIK_VAL(char VAL);
/// � ������� ������� ����� ���������
extern char Get_INDIK_VAL(void);
/// ��������� ��������� �������� ������ ������
extern void Indikate( void );

#endif



#ifndef _DAC_iface_
#define _DAC_iface_

#include "Header.h"

/// ���������� �������� ��������� � �����
#define NUM_CLK_PULSES	12

/// ���� ������� CLK
#define _CLK_bit  (1<<PB5)

/// ������ CS
#define _CS_bit   (1<<PB2)
#define SET_CS  PORTD |= _CS_bit;
#define CLR_CS  PORTD &= ~_CS_bit;

/// ������ SDI
#define _SDI_bit (1<<PB3)
#define SET_SDI  PORTB |= _SDI_bit;
#define CLR_SDI  PORTB &= ~_SDI_bit;
/// ������ LOAD
#define _LOAD_bit (1<<PB3)
#define SET_LOAD  PORTB |= _LOAD_bit;
#define CLR_LOAD  PORTB &= ~_LOAD_bit;



/// ��������� ���������� ��� ������ � ���
extern void Init_DAC_Iface(void);

/// ������ ������ � ���
extern void DAC_Write(int DATA);

#endif  ///_DAC_iface_


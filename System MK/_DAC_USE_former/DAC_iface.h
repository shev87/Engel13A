#ifndef _DAC_iface_
#define _DAC_iface_

#include "Header.h"

/// количество тактовых импульсов в пачке
#define NUM_CLK_PULSES	12

/// биты сигнала CLK
#define _CLK_bit  (1<<PB5)

/// сигнал CS
#define _CS_bit   (1<<PB2)
#define SET_CS  PORTD |= _CS_bit;
#define CLR_CS  PORTD &= ~_CS_bit;

/// сигнал SDI
#define _SDI_bit (1<<PB3)
#define SET_SDI  PORTB |= _SDI_bit;
#define CLR_SDI  PORTB &= ~_SDI_bit;
/// сигнал LOAD
#define _LOAD_bit (1<<PB3)
#define SET_LOAD  PORTB |= _LOAD_bit;
#define CLR_LOAD  PORTB &= ~_LOAD_bit;



/// настройка интерфейса для работы с ЦАП
extern void Init_DAC_Iface(void);

/// запись данных в ЦАП
extern void DAC_Write(int DATA);

#endif  ///_DAC_iface_


#ifndef _SHow_FUN_H_
#define _SHow_FUN_H_

#include "Header.h"

#define   PORT_INI_SHOW DDRB    // какой порт настраивать для показа битов АЦП
#define   PORT_SHOW     PORTB   // в какой порт показывать биты АЦП
#define   PIN_SHOW      PB0     // в какой ножку порта показывать биты АЦП

/// готовит порт для индикации результата
extern void show_init(void);

//// функция выводит на ножку значение
//// что бы посмотреть его осциллографом
extern void show_result(unsigned int VAL);

#endif /// _SHow_FUN_H_


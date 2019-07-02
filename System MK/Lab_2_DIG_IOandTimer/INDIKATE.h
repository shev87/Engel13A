#ifndef _INDIKATE_H
#define _INDIKATE_H

#include "Header.h"

//////////////////////////////////////////////////
// макрос для включения и выключения бита в порту
#define SET_I_BIT    (LEDPORT |= (1<<LED))
#define CLR_I_BIT    (LEDPORT &= ~(1<<LED))

/////////////////////////////////////////////////////
/// режим индикации светодиода
#define LED_IS_OFF        0
#define LED_1SHORT        1
#define LED_2SHORT        2
#define LED_3SHORT        3
#define LED_FASTBLINK     4
#define LED_IS_ON         5
/// один и два моргания на фоне гоящего светодиода
#define LED_1SHORT_SH     6
#define LED_2SHORT_SH     7
#define LED_SLOWBLINK     8

//////////////////////////////////////////////////
//// процедура настройка индикация режим работы
extern void InitIndikate(void);
////////////////////////////////////
/// ф установить режим индикации как будет гореть LED
/// для установвки другого режима индикации - один из
/// определенных === /// режим индикации светодиода
extern void Set_INDIK_VAL(char VAL);
/// ф считать текущий режим индикации
extern char Get_INDIK_VAL(void);
/// процедура индикации текущего режима работы
extern void Indikate( void );

#endif



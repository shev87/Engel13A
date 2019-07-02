#ifndef Timer_2_CNTRL_H
#define Timer_2_CNTRL_H

#include "Header.h"
/// определим время которое хотим получить в десятках мкс
/// хотим получить 100мкс интервал 10*10мкс....
#define TIME_INTERVAL		10

//// настройка таймера 2 на генерацию временного интервала
extern void Timer2_INIT(void);
//// опрос флага временного интервала
//// вернет да прошел заданный интервал времени
extern u_char Timer2_CHECK(void);
//// запуск таймера
extern void Timer2_START(void);
//// останов таймера
extern void Timer2_STOP(void);

#endif  ///Timer_2_CNTRL_H

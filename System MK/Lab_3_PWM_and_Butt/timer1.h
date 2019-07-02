#ifndef _TIMER1_H_
#define _TIMER1_H_

#include "Header.h"
/// указатель на ф - обработчик события переполнение таймера 0
extern FPTR_vv   Timer0_Checker;

/////////////////////////////////////////////
/// Определим значение для ШИМА
/// период ШИМ
#define PWM_TOP_VAL       0x3FF
/// верхний предел ШИМ
#define PWM_UP_VAL        0x3FF


//// Настройка и управлением таймером 1
/// работает в режиме FAST_PWM
/// TOP - в регистре ICR  сравнение в OCR1A
extern void Init_TimerT1(void);


#endif /// _TIMERS_H_







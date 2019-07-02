#ifndef _TIMERS_H_
#define _TIMERS_H_

#include "types.h"
/// указатель на ф - обработчик события переполнение таймера 0
extern FPTR_vv   Timer0_Checker;

/////////////////////////////////////////////
/// Определим значение для ШИМА
/// период ШИМ всего 127 тиков
#define PWM_TOP_VAL       0x7F
/// верхний предел ШИМ пробуем дойти до половины
/// под нагрузкой получаем 270В
#define PWM_UP_VAL        50

/// верхний предел ШИМ под нагрузкой получаем 240В
///#define PWM_UP_VAL        (PWM_TOP_VAL/3)
/// нижний предел ШИМ
#define PWM_LOW_VAL       (PWM_UP_VAL/20)
/// 10% от верхний предела ШИМ
#define PWM_10pers_VAL    (PWM_UP_VAL/10)
/// 30% от верхний предела ШИМ
#define PWM_30pers_VAL    (PWM_UP_VAL/3)

//// Настройка и управлением таймером 1 для управления преобразователем
/// работает в режиме FAST_PWM 
/// TOP - в регистре ICR  сравнение в OCR1A
extern void Init_TimerT1(void);
/// настрока на работу таймера 0 и прерывания INT0
/// и портов управления симистора и полевика
extern void Init_Timer0_and_PORTS(void);

/// доступны функции включить/выключить преобразователь 
#define TURN_OFF_HI_VOLT  OCR1A  = 0;
/// Эти функции выполняем по указателю Timer0_Checker
/// будет две ф которые мы выполняем

/// 1 - отработали время зажигания ...
extern void ON_End_Ignition_Time(void);
/// 2 - отработана пауза после закрытия симистора
extern void ON_End_PAUSE_Time(void);
/// 3 - разрешение прерываний от INT0
/// для ограничения частоты входящих импульсов
extern void ON_End_PAUSE_2NEW_PULSE(void);
/// 4 - сформировали импульс жажигания, паузу, зарядный импульс
/// защитный интервал, теперь, разрешим новый импульс
extern void ON_ENABLE_NEW_PULSE(void);


/// Останов Таймера 0 и сброс флага
#define Stop_T0   {TCCR0 = 0; TIFR = (1<<TOV0);}
/// запуск таймера 0 на заданное время
/// запускаем таймер на чатоте карц/64 
#define Start_T0(Time)  {TCNT0 = Time; TCCR0 = 3;}


#endif /// _TIMERS_H_







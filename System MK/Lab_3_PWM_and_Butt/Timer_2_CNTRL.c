#include "Timer_2_CNTRL.h"

//// что бы сформировать заданный интервал времени
//// нужно определиться с коэффициентом деления
//// возможно 1,8,32,64,128,256,1024

//// желательно чтобы за один прогон счетчика мы
/// сформировали заданный интервал поэотму
/// число переполнений не должно быть более 1

/// число переполнениий считаем так
/// Noverflow (1) = Fquarz*TIME_SETTED/(CountVAL*Kprescaler)
/// отсюда
/// Kprescaler >=  Fquarz*TIME_SETTED/CountVAL
/// где CountVAL - емкость счетчика T2 = 256
/// после того ка определили Kprescaler
/// значение загружаемое в регистр сравнения
/// определиться так COMPARE_VAL = Fquarz*TIME_SETTED/Kprescaler


//// можно получить без предделителя
#if (TIME_INTERVAL*SYSTEM_CLOCK/25600000U) < 1
#define OCR2VAL		(TIME_INTERVAL*SYSTEM_CLOCK/100000U/1)
#define TIMER_2_START_MASK		0x01

//// можно получить если коэффициент делитель реван 8
#elif (TIME_INTERVAL*SYSTEM_CLOCK/25600000U/8) < 1
#define OCR2VAL		(TIME_INTERVAL*SYSTEM_CLOCK/100000U/8)
#define TIMER_2_START_MASK		0x02

//// можно получить если коэффициент делитель реван 32
#elif (TIME_INTERVAL*SYSTEM_CLOCK/25600000U/32) < 1
#define OCR2VAL		(TIME_INTERVAL*SYSTEM_CLOCK/100000U/32)
#define TIMER_2_START_MASK		0x03

//// можно получить если коэффициент делитель реван 64
#elif (TIME_INTERVAL*SYSTEM_CLOCK/25600000U/64) < 1
#define OCR2VAL		(TIME_INTERVAL*SYSTEM_CLOCK/100000U/64)
#define TIMER_2_START_MASK		0x04

//// можно получить если коэффициент делитель реван 128
#elif (TIME_INTERVAL*SYSTEM_CLOCK/25600000U/128) < 1
#define OCR2VAL		(TIME_INTERVAL*SYSTEM_CLOCK/100000U/128)
#define TIMER_2_START_MASK		0x05

//// можно получить если коэффициент делитель реван 256
#elif (TIME_INTERVAL*SYSTEM_CLOCK/25600000U/256) < 1
#define OCR2VAL		(TIME_INTERVAL*SYSTEM_CLOCK/100000U/256)
#define TIMER_2_START_MASK		0x06

//// можно получить если коэффициент делитель реван 1024
#elif (TIME_INTERVAL*SYSTEM_CLOCK/25600000U/1024) < 1
#define OCR2VAL		(TIME_INTERVAL*SYSTEM_CLOCK/100000U/1024)
#define TIMER_2_START_MASK		0x07

//// нельзя получить	
#else
#error "ЗАДАННОЕ ВРЕМЯ ПЕРЕПОЛНЕНИЯ -TIME_INTERVAL- Т2 СЛИШКОМ ВЕЛИКО"
#define OCR2VAL				0x00
#define TIMER_2_START_MASK		0x00

#endif
///////////////////////////////
/// На выходе этой конструкции имеем
/// OCR2VAL и TIMER_2_START_MASK
/// которые определят конфигурацию таймера 2 для
/// формирования заданного интервала
/// понятно что этот интервал не точно равен заданному времени
/// а с учетом погрешности до 1 тактового импульса счетчика
/// и на 1024 и 8МГц может быть 128мкс

#define TIMER_2_START	TCCR2 |= TIMER_2_START_MASK;
#define TIMER_2_STOP	TCCR2 &= ~0x07;


//// настройка таймера 2 на генерацию временного интервала
/// на опрос кнопок будет достаточно 20мс интервала
void Timer2_INIT(void)
{
    TIMER_2_STOP; 	/// на всякий случай		
    TCCR2 = (1<<WGM21); /// режим работы счет до величины записаной
    OCR2 = (char)OCR2VAL; /// значение соответствует интервалу TIME_INTERVAL
    TCNT2 = 0;
}
//// опрос флага временного интервала
//// вернет да прошел заданный интервал времени
u_char Timer2_CHECK(void)
{
  if(TIFR&(1<<OCF2)){
     TIFR = (1<<OCF2); /// сбросим флаг
     return 1;
  }
  return 0;
}
//// запуск таймера
void Timer2_START(void)
{
	TIMER_2_START;
}
//// останов таймера
void Timer2_STOP(void)
{
	TIMER_2_STOP;
}

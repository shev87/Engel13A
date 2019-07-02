#include "INDIKATE.h"


////////////////////////////////////
// переменные для индикации режима работы
char IndikateVALUE;
////////////////////////////////////
/// ф установить режим индикации как будет гореть LED
void Set_INDIK_VAL(char VAL)
{
  IndikateVALUE = VAL;
}
/// ф считать текущий режим индикации
char Get_INDIK_VAL(void)
{
  return IndikateVALUE;
}

////////////////////////////////////
// массив для идикации состояний контроллера
flash char IND_ARR[9] = { 0x00, 0x01, 0x05, 0x15, 0x55, 0xFF, 0x7F, 0x5F, 0xF0 };
//////////////////////////////////////////////////
/// функция индицирует количеством вспышек текущий режим работы
/// передаем на вход номер режима
/// если ррежим равен INIT_MOD - просто включим светодиод
void IndikateFN (char x)
{
static char loc_val = 0, mask = 0;
char tmp;
 if(mask == 0){
    mask = 0x80; // если прошли весь байт начнем сначала
    tmp = IND_ARR[x];
    if(loc_val != tmp) // изменили режим индикации
       loc_val = tmp;
 }
// работа
 if(loc_val & mask) // если 1 зажигаем светодиод
        SET_I_BIT;
 else   CLR_I_BIT;  // если 0 тушим светодиод
 mask >>= 1;
}
/// процедура индикации текущего режима работы
void Indikate( void )
{
  IndikateFN(IndikateVALUE);
}

//////////////////////////////////////////////////
//// процедура индикация режим работы
void InitIndikate(void)
{
 LED_DIR_PORT |= (1<<LED); // настроим вывод управления LED
 CLR_I_BIT;
 IndikateVALUE = LED_IS_OFF;
}

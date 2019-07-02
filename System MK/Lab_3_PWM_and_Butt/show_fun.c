#include "SHow_FUN.h"


///// определимся сфункциями
//// настройка
 /// готовит порт для индикации результата на
void show_init(void)
{
  PORT_INI_SHOW  |= (1<<PIN_SHOW);   // настроили порт
  PORT_SHOW      |= (1<<PIN_SHOW);  // бит равен 1
}

//// ф. выводит на вывод значение измеренное АЦП
//// что бы посмотреть его Осциллографом
void show_result( unsigned int VAL)
{
 char ctmp;
 unsigned int MASK = 0x01;
  ctmp = 0xF;
  //// выводим синхробит бит равен 0
  PORT_SHOW |= (1<<PIN_SHOW);
  while(--ctmp){
     _NOP();
  }
  //// выводим начинаем с младшего бита 10 бит
  ctmp = 10;
  do{
     /////делаем опорные точки чтобы увидеть бит
     PORT_SHOW |= (1<<PIN_SHOW);
     PORT_SHOW &= ~(1<<PIN_SHOW); // бит равен 0

     if(VAL&MASK){//// бит равен 1
        PORT_SHOW |= (1<<PIN_SHOW);
     }else{ //// бит равен 0
        PORT_SHOW &= ~(1<<PIN_SHOW); // бит равен 0
     }
     ////  пауза
     _NOP();
     _NOP();
     _NOP();
     /// передвигаем Маску
     MASK <<= 1;
  }while(ctmp--);
 PORT_SHOW |= (1<<PIN_SHOW); // бит равен 1
}

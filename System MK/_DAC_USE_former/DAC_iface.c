#include "DAC_iface.h"

/// настройка интерфейса для работы с ЦАП
void Init_DAC_Iface(void)
{
  DDRB = (_LOAD_bit|_CS_bit|_SDI_bit|_CLK_bit);
}


/// формирователь одного периода сигнала CLK _/-
void CLK_SIGNAL(void)
{
  PORTB &= ~_CLK_bit;
  PORTB |= _CLK_bit;
}

/// запись данных в ЦАП DAC7611
void DAC_Write(int DATA)
{
int MASK = 0x0800;

  CLR_CS;  /// начало - CS = 0

  while(1){/// в цикле на количество тактовых импульсов
      /// установим или сбросим бит данных
      if( MASK&DATA ){
          SET_SDI; /// бит данных равен 1
      }else{
          CLR_SDI; /// бит данных равен 0
      }
      /// формируем сигнал CLK
      CLK_SIGNAL();/// формирователь одного периода сигнала CLK \_/-\
      MASK >>= 1;
      if(MASK == 0)
         break;
  } /// конец цикла

  SET_CS; /// завершим - CS = 1

  /// сформируем сигнал LD в DAC7611
  CLR_LOAD;
  SET_LOAD;
}

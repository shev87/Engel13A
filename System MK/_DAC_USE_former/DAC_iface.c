#include "DAC_iface.h"

/// ��������� ���������� ��� ������ � ���
void Init_DAC_Iface(void)
{
  DDRB = (_LOAD_bit|_CS_bit|_SDI_bit|_CLK_bit);
}


/// ������������� ������ ������� ������� CLK _/-
void CLK_SIGNAL(void)
{
  PORTB &= ~_CLK_bit;
  PORTB |= _CLK_bit;
}

/// ������ ������ � ��� DAC7611
void DAC_Write(int DATA)
{
int MASK = 0x0800;

  CLR_CS;  /// ������ - CS = 0

  while(1){/// � ����� �� ���������� �������� ���������
      /// ��������� ��� ������� ��� ������
      if( MASK&DATA ){
          SET_SDI; /// ��� ������ ����� 1
      }else{
          CLR_SDI; /// ��� ������ ����� 0
      }
      /// ��������� ������ CLK
      CLK_SIGNAL();/// ������������� ������ ������� ������� CLK \_/-\
      MASK >>= 1;
      if(MASK == 0)
         break;
  } /// ����� �����

  SET_CS; /// �������� - CS = 1

  /// ���������� ������ LD � DAC7611
  CLR_LOAD;
  SET_LOAD;
}

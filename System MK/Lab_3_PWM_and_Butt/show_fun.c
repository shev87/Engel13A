#include "SHow_FUN.h"


///// ����������� ����������
//// ���������
 /// ������� ���� ��� ��������� ���������� ��
void show_init(void)
{
  PORT_INI_SHOW  |= (1<<PIN_SHOW);   // ��������� ����
  PORT_SHOW      |= (1<<PIN_SHOW);  // ��� ����� 1
}

//// �. ������� �� ����� �������� ���������� ���
//// ��� �� ���������� ��� �������������
void show_result( unsigned int VAL)
{
 char ctmp;
 unsigned int MASK = 0x01;
  ctmp = 0xF;
  //// ������� ��������� ��� ����� 0
  PORT_SHOW |= (1<<PIN_SHOW);
  while(--ctmp){
     _NOP();
  }
  //// ������� �������� � �������� ���� 10 ���
  ctmp = 10;
  do{
     /////������ ������� ����� ����� ������� ���
     PORT_SHOW |= (1<<PIN_SHOW);
     PORT_SHOW &= ~(1<<PIN_SHOW); // ��� ����� 0

     if(VAL&MASK){//// ��� ����� 1
        PORT_SHOW |= (1<<PIN_SHOW);
     }else{ //// ��� ����� 0
        PORT_SHOW &= ~(1<<PIN_SHOW); // ��� ����� 0
     }
     ////  �����
     _NOP();
     _NOP();
     _NOP();
     /// ����������� �����
     MASK <<= 1;
  }while(ctmp--);
 PORT_SHOW |= (1<<PIN_SHOW); // ��� ����� 1
}

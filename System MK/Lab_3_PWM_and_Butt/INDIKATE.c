#include "INDIKATE.h"


////////////////////////////////////
// ���������� ��� ��������� ������ ������
char IndikateVALUE;
////////////////////////////////////
/// � ���������� ����� ��������� ��� ����� ������ LED
void Set_INDIK_VAL(char VAL)
{
  IndikateVALUE = VAL;
}
/// � ������� ������� ����� ���������
char Get_INDIK_VAL(void)
{
  return IndikateVALUE;
}

////////////////////////////////////
// ������ ��� �������� ��������� �����������
flash char IND_ARR[9] = { 0x00, 0x01, 0x05, 0x15, 0x55, 0xFF, 0x7F, 0x5F, 0xF0 };
//////////////////////////////////////////////////
/// ������� ���������� ����������� ������� ������� ����� ������
/// �������� �� ���� ����� ������
/// ���� ������ ����� INIT_MOD - ������ ������� ���������
void IndikateFN (char x)
{
static char loc_val = 0, mask = 0;
char tmp;
 if(mask == 0){
    mask = 0x80; // ���� ������ ���� ���� ������ �������
    tmp = IND_ARR[x];
    if(loc_val != tmp) // �������� ����� ���������
       loc_val = tmp;
 }
// ������
 if(loc_val & mask) // ���� 1 �������� ���������
        SET_I_BIT;
 else   CLR_I_BIT;  // ���� 0 ����� ���������
 mask >>= 1;
}
/// ��������� ��������� �������� ������ ������
void Indikate( void )
{
  IndikateFN(IndikateVALUE);
}

//////////////////////////////////////////////////
//// ��������� ��������� ����� ������
void InitIndikate(void)
{
 LED_DIR_PORT |= (1<<LED); // �������� ����� ���������� LED
 CLR_I_BIT;
 IndikateVALUE = LED_IS_OFF;
}

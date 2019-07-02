#include "Kbrd.h"

static u_char flags = 0;
static u_char Countr_SW1 = 0;
static u_char Countr_SW2 = 0;

#define SHORTPRS	10
#define LONGPRS		140

#define SW1_SHORTPRS	0x01
#define SW1_LONGPRS	0x02
#define SW2_SHORTPRS	0x04
#define SW2_LONGPRS	0x06

/// ����� �� ������� ���������� ������ SW1
#define Butt_SW1_BIT 	(1<<PC2)
/// ����� �� ������� ���������� ������ SW2
#define Butt_SW2_BIT 	(1<<PC3)
/// ����� ��� ������
#define Butt_MASK     (Butt_SW2_BIT|Butt_SW1_BIT)
/// ���� �� ������� ����� ������
#define Butt_SW_PORT 	PINC



/// ������� ��� ������
///#define ButtBIT 	(1<<PD2)
///#define ButtPORT 	PIND

#define CHK_NOTPRS	((Butt_SW_PORT&Butt_MASK) == Butt_MASK)
#define CHK_Butt_SW1	((Butt_SW_PORT&Butt_SW1_BIT) == 0)
#define CHK_Butt_SW2	((Butt_SW_PORT&Butt_SW2_BIT) == 0)

// ��������� ������ ������
void ChkKbrd(void)
{
  if(CHK_Butt_SW1){ /// SW1 ������ ������
     if(Countr_SW1 < 0xF0) Countr_SW1++;	
  }
  if(CHK_Butt_SW2){ /// SW2 ������ ������
     if(Countr_SW2 < 0xF0) Countr_SW2++;	
  }
  if(CHK_NOTPRS){
/// ���� �� ������ �� ���� ������
  	if(Countr_SW1){ /// ���� ������� SW1
	     flags = 0;
             if(Countr_SW1 >= LONGPRS){
		flags |= SW1_LONGPRS;
	     }
	     else if(Countr_SW1 >= SHORTPRS){
		flags |= SW1_SHORTPRS;
	     }
	     Countr_SW1 = 0;
  	}
  	if(Countr_SW2){ /// ���� ������� SW2
             if(Countr_SW2 >= LONGPRS){
		flags |= SW2_LONGPRS;
	     }
	     else if(Countr_SW2 >= SHORTPRS){
		flags |= SW2_SHORTPRS;
	     }
	     Countr_SW2 = 0;
  	}
  }
}
//���������� ��� ������� ������
//����� ���� ��������, �������, �� ����������, ��������,
u_char GetPrsCode(void)
{
u_char temp;
u_char res = 0;
   temp = SREG;
   _CLI();
   res = flags;
   flags = 0;
   SREG = temp;

   if(res == 0){ // ������ �� ��������
	return 0;
   }else if(res == SW1_SHORTPRS){ // �������� ������� SW1
	return LEFTSHORT;
   }else if(res == SW1_LONGPRS){ // ������� ������� SW1
	return LEFTLONG;
   }else if(res == SW2_SHORTPRS){ // �������� ������� SW2
	return RIGHTSHORT;
   }else if(res == SW2_LONGPRS){ // ������� ������� SW2
	return RIGHTLONG;
   }
   return TWOKEYPRS;
}


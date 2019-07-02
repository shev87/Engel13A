#ifndef _COMPILER_H_
#define _COMPILER_H_


#ifdef __cplusplus
extern "C" {
#endif
//// device
#include <iom8.h>

#include <comp_a90.h>
#include <inavr.h>
#include <stdio.h>
//#include <stdlib.h>
#include <string.h>
/// ��������� ���� ������� �� ���������� ��� ���� ��� ������� ���
#include "types.h"


////////////////////////////////////////////////
//// ��� ������� ������� ��������� ����� ����������
/// ��������� ��� ��������� ���������
/// ��� � ����
    #define LED      		PB7
    #define LEDPORT   		PORTB
    #define LED_DIR_PORT   	DDRB


//////////////////////////////////////////////////
/// ��������� ������� ������
///#define SYSTEM_CLOCK    9214857L
#define SYSTEM_CLOCK    8000000L

/////////////////////////////////////////////////////////
//// ������ ��������� �������� �������� UBRR ��� ��������
//// �������� ������
#define UBRR_VAL(x)     ((SYSTEM_CLOCK/16/(x))-1)
/// ���������� �������� ������ UART
#define _UART_BAUD 	    (UBRR_VAL(19200U))
////////////////////////////////////////////////////////


#ifdef __cplusplus
}
#endif

/*@{*/

#endif


/**************************************************************
 **             - __low_level_init.c -
 **
 **     Special initializations that are performed before
 **     segment initialization. It is also possible to
 **     completely block the normal segment initialization.
 **
 **     Used with iccAVR.
 **
 **     $Revision: 1.2 $
 **
 **************************************************************/
#include <inavr.h>

//// ��������� ��� ��� �����...
//// �������� ������������ � ������� ��������
#include "Header.h"

extern void *__RSTACK_in_external_ram;

/**************************************************************
 **
 ** How to implement a low-level initialization function in C
 ** =========================================================
 **
 ** 1) Only use local auto variables.
 ** 2) Don't use global or static variables.
 ** 3) Don't use global or static objects (EC++ only).
 ** 4) Don't use agregate initializers, e.g. struct a b = {1};
 ** 5) Don't call any library functions (function calls that
 **    the compiler generates, e.g. to do integer math, are OK).
 ** 6) Setup the RSTACK as is appropriate! See code below.
 **
 **************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
char __low_level_init()
{
  /* Uncomment the statement below if the RSTACK */
  /* segment has been placed in external SRAM!   */

  /* __require(__RSTACK_in_external_ram); */

  /* If the low-level initialization routine is  */
  /* written in assembler, the line above should */
  /* be written as:                              */
  /*     EXTERN  __RSTACK_in_external_ram        */
  /*     REQUIRE __RSTACK_in_external_ram        */

  /* Add your custom setup here. */
  ////////////////////////////////////////
  /// �������� ����� ��� ������
   PORTB = 0xFF;
   PORTC = 0xFF;
   PORTD = 0xFF;

  /* Return 1 to indicate that normal segment */
  /* initialization should be performed. If   */
  /* normal segment initialization should not */
  /* be performed, return 0.                  */
  return 1;
}
#ifdef __cplusplus
}
#endif


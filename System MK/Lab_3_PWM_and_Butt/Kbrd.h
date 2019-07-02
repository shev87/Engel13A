#include "Header.h"
//extern "C"{
//////////////////////////////////////////////
///  Ќќѕ и
// возвращает текущее значение кнопки нажата/отпущена
extern void ChkKbrd(void);
//возвращает код нажати€ кнопки
#define	LEFTSHORT	1
#define	LEFTLONG	2
#define	RIGHTSHORT	3
#define	RIGHTLONG	4
#define	TWOKEYPRS	5
// может быть короткое, длинное, не нажималось, замкнута,
extern u_char GetPrsCode(void);

//}


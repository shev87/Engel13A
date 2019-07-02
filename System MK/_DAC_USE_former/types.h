#ifndef _SYS_TYPES_H_
#define _SYS_TYPES_H_


/*! \brief Unsigned 8-bit value. */
typedef unsigned char      u_char;
/*! \brief Unsigned 16-bit value. */
typedef unsigned short     u_short;
/*! \brief Unsigned 16-bit value. */
typedef unsigned int       u_int;
/*! \brief Unsigned 32-bit value */
typedef unsigned long      u_long;
/*! \brief Void pointer */
typedef void * HANDLE;

// указатель на ф типа void (void)
typedef void (*FPTR_vv)(void);

#define  TRUE              1
#define  FALSE             0

#define  SUCCESS           0
#define  FAILED            1

#define  DEFAULT_BYTE      0xFF
#define  DEFAULT_WORD      0xFFFF
#define  DEFAULT_LONG      0xFFFFFFFFUL


#endif

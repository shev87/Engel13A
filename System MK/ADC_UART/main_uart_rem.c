/*! \file *******************************************************************
*
* По  материалам application notes адаптируем на mega8
*
* AppNote           : AVR121 - Enhancing ADC resolution by oversampling
*
* Description       : Example of how to use oversampling to increase the resolution.
*                     10-bit result is written to UART after each conversion
*                     16-bit result are written to UART after 4096 10-bit samples
*
****************************************************************************/
#include "Header.h"
#include "FLOAT2ASCII.h"

// Global variables
float accumulator       = 0;          //!< Accumulating 10-bit samples
float result            = 0;          //!< ASCII variable
float Vin               = 0;          //!< 16-bit result
short temp              = 0;          //!< последнее измеренное значение ADC
short samples           = 0;	      //!< Counting 10-bit samples
/// длина буффера строки для передачи ПК
#define BUFF_LEN  128
/// буффер в который записываем нужную информацию для передачи ПК
char Str_Buff[BUFF_LEN];


// Function prototypes
void send(unsigned char result);
void write_ascii(char *Ptr2Str);
void init_adc(void);
void init_uart(void);
void init_counter(void);
void vin(void);
void write_10bit(void);
void write_16bit(void);
void oversampled(void);
void write_space(void);

//! ADC interrupt routine
#pragma vector=ADC_vect
__interrupt void ADCinterrupt(void)
{
  temp = ADC;
  accumulator += ADC;
  samples++;
}

//! Enables ADC, Interrupt enabled, ADC-clock=125kHz, VREF=AVCC
void init_adc(void)
{
  ADCSR = (1<<ADEN)|(1<<ADIE)|(1<<ADSC)|(1<<ADFR)|(1<<ADPS2)|(1<<ADPS1);
  ADMUX = (0<<REFS1)|(1<<REFS0); /// 11 - 2,56В 01 - AVCC
  __enable_interrupt();
}

/*! \brief Initiates the UART, 19.2kbps @ 8MHz cpu-clk.,
     enables transmitter, 8 data, 1 stop, no parity
     transmitting 8 LSB */
void init_uart(void)
{
   /// Set baud rate
   UBRRH = (unsigned char)(_UART_BAUD>>8);
   UBRRL = (unsigned char)_UART_BAUD;
   /// Enable Receiver and Transmitter
   UCSRB = (1<<TXEN);
   /// Set frame format: 8data, 1stop bit
   UCSRC = (1<<URSEL)|(0<<USBS)|(3<<UCSZ0);
}

//! Waits for empty transmit buffer, puts data into buffer and send data
void send(unsigned char symbol)
{
  while (!(UCSRA & (1<<UDRE)));	
  UDR = symbol;         	             					
}

//! Fast PWM, Clk / 64, Clear OC2 on compare match, 50% duty cycle
void init_counter(void)
{
  DDRD  = (1<<PD7);
  TCCR2 = (1<<WGM20)|(1<<WGM21)|(1<<COM21)|(1<<CS22);
  OCR2  = 128;
}

////////////////////////////////////////
/// передаем строку в ПК
/// строка всегда завершается 0 что бы определить конец строки
void write_ascii(char *Ptr2Str)
{
  char* In_BufPtr = Ptr2Str;  /// указатель на текущий символ для передачи
  char countr = 0;  /// счетчик переданных символов

  /// если выходим за пределы буффера - конец передачи
  while ( countr < BUFF_LEN )
  {
    char symb = *In_BufPtr++;
    if(symb == 0) break;  /// встретили конец строки завершаем передачу
    send(symb);           /// передаем очередной байт из буффера
    countr++;
  }
  send('\r');             /// Send return
  send('\n');             /// Send newline
}

//! Calculating 16-bit result
void vin(void)
{
  Vin = (accumulator/65536)*5.0;	     // VREF = 4.910
}

//// подготовка данных для передачи ПК в буффере
/// в буффер записываем код ADC и вычисленное значение
void write_data_2Buffer(void)
{
  /// заполним буффер символами '_'
  memset(Str_Buff, '_', BUFF_LEN);
  Str_Buff[0] = 'A';
  Str_Buff[1] = 'D';
  Str_Buff[2] = 'C';
  Str_Buff[3] = '=';
  /// запишет 8 байт в буффер начиная с 5 байта
  BSD_FP((float)temp, &Str_Buff[4]);
  /// (4+8 = 12)
  Str_Buff[12] = ' ';
  Str_Buff[13] = 'a';
  Str_Buff[14] = 'c';
  Str_Buff[15] = 'c';
  Str_Buff[16] = '=';
  /// запишет 8 байт в буффер начиная с 17 байта
  BSD_FP(Vin, &Str_Buff[17]);
  Str_Buff[25] = 0;  // конец строки
}

/*! \brief Compensate errors, scaling result, round up,
    increase averaged result */
void oversampled(void)
{
  u_int itmp;
  __disable_interrupt();
  accumulator += 0;       // Offset error compensation, 5150 = (69*4096)/64*/
  itmp=(int)accumulator%64;
  accumulator/=64;
  if(itmp>=32)
    {
      accumulator += 1;   //  Rounding up
    }
  ///accumulator *= 0.9993;     // Gain error compensation*/

  vin();
  samples     = 0;			
  accumulator = 0;			
  //// подготовка данных для передачи ПК в буффере
  /// в буффер записываем код ADC и вычисленное значение
  write_data_2Buffer();
  /// передаем строку в ПК
  /// строка всегда завершается 0 что бы определить конец строки
  write_ascii(Str_Buff);
  __enable_interrupt();
}

void main( void )
{
  init_uart();
  init_adc();
  //init_counter();

  while(1)
  {
    if(samples>4095)
      {
        oversampled();
      }
  }
}


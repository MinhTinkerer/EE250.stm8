/* SERIAL.H file
 * 
 * SCHLOTTERBECK Guillaume
 * PERARD Doriane
 *
 * 10/04/2031
*/

#ifndef SERIAL_H
#define SERIAL_H

#include "common.h"

// en ASCII
#define KEY_ENTER 0x0D
#define CR 0x0D
#define LF 0x0A

#define Serial_RXNE() (UART2->SR & UART2_SR_RXNE)

// modes pour l'UART
typedef enum {
    RO = UART2_CR2_REN,
    WO = UART2_CR2_TEN,
    RW = UART2_CR2_REN | UART2_CR2_TEN
} MODE;


extern void Serial_init(MODE);

extern void Serial_enableRI(char);


extern char Serial_Getchar(void);
extern void Serial_Putchar(char);

extern void Serial_Putstring(char* );


#endif// !SERIAL_H




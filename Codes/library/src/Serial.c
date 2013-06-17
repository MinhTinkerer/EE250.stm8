/**
    \file Serial.c
    \brief Fonctions utiles a l'utilisation de l'UART2
    \author SCHLOTTERBECK Guillaume, PERARD Doriane
    \version 1.0
    \date 10/04/2013
	
	Maj : Alex Nodet, 17/06/2013
**/

#include "../include/Serial.h"

void Serial_init(MODE mode) {

    UART2->CR1 = 0x00;    /* 1 start bit, 8 data, no parity */
    UART2->CR3 = UART2->CR3 & ~UART2_CR3_STOP;    /* 1 stop bit */
    
    /* page 321
    fmaster=2MHz
    UART_DIV=2MHZ/9600=208d=0x00D0
    BRR1=0x0D et BRR2=0x00 */
    UART2->BRR2=0x00;
    UART2->BRR1=0x0D;
    
    /* transmitter enable */
    UART2->CR2 |= (char)mode;

}

void Serial_enableRI(char b) {
    if (b != 0) {
        /* on active l'IT de reception */
        UART2->CR2 |= UART2_CR2_RIEN;
		_asm("RIM\n");
    }
    else {
        /* on desactive l'IT de reception */
        UART2->CR2 &= ~UART2_CR2_RIEN;
    }
}

char Serial_Getchar(void) {
    while( (UART2->SR & UART2_SR_RXNE) != UART2_SR_RXNE );
    return UART2->DR;
}

void Serial_Putchar(char c) {
    while ( (UART2->SR & UART2_SR_TXE) != UART2_SR_TXE);
    UART2->DR = c;
}

void Serial_Putstring(char* s) {
    char i=0;
    while ( s[i] != '\0' ) {
        Serial_Putchar( s[i] );
        i++;
    }
}

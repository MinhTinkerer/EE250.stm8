/**
    \file TIL321.c
    \brief Fonctions utiles a l'utilisation du TIL321
    \author SCHLOTTERBECK Guillaume, PERARD Doriane
    \version 1.0
    \date 10/04/2013
	
	Maj : Alex Nodet, 17/06/2013
**/

#include "../include/TIL321.h"

void TIL321_init(void) {
    GPIOB->DDR = OUTPUT;
    
}

void TIL321_print(char i) {
    char NUMBERS[] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xF6};
    char ERROR = 0x9E;
    
    GPIOB->ODR = (i<=9 && i>=0)? NUMBERS[ i%10 ] : ERROR;
}

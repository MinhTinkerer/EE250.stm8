/* TIL321.C file
 * 
 * SCHLOTTERBECK Guillaume
 * PERARD Doriane
 *
 * 10/04/2031
*/

#include "../include/TIL321.h"

void TIL321_init(void) {
    GPIOB->DDR = OUTPUT;
    
}

void TIL321_print(char i) {
    char NUMBERS[] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xF6};
    char ERROR = 0x9E;
    
    GPIOB->ODR = (i<=9 && i>=0)? NUMBERS[ i%10 ] : ERROR;
}

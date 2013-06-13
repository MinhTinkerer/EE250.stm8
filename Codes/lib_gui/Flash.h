/* Flash.H file
 * 
 * SCHLOTTERBECK Guillaume
 * PERARD Doriane
 *
 * 10/04/2031
*/

#ifndef FLASH_H
#define FLASH_H

#include "_stdint.h"

extern void FLASH_init(void);

extern uint32_t FLASH_write(uint32_t addr, char *data, uint32_t size);
extern uint32_t FLASH_read(uint32_t addr, char *data, uint32_t size);



#endif




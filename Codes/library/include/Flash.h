/**
    \file Flash.h
    \brief Prototypes utiles a l'utilisation de l'EEPROM
    \author SCHLOTTERBECK Guillaume, PERARD Doriane
    \version 1.0
    \date 10/04/2013
	
	Maj : Alex Nodet, 17/06/2013
**/

#ifndef FLASH_H
#define FLASH_H

#include "_stdint.h"
#include "stm8s.h"
#include "stm8s_flash.h"

#define FLASH_ADDR_MIN FLASH_DATA_START_PHYSICAL_ADDRESS
#define FLASH_ADDR_MAX FLASH_DATA_END_PHYSICAL_ADDRESS


extern void FLASH_init(void);

extern uint32_t FLASH_write(uint32_t addr, char *data, uint32_t size);
extern uint32_t FLASH_read(uint32_t addr, char *buffer, uint32_t size);



#endif	/* !FLASH_H */





#include "../include/Flash.h"


void FLASH_init(void) {
    FLASH_DeInit();
    FLASH_SetProgrammingTime(FLASH_PROGRAMTIME_STANDARD);
}

/**
    \fn uint32_t FLASH_write(uint32_t addr, char *data, uint32_t size)
    \brief Ecrit dans l'EEPROM
    \param uint32_t addr
        l'adresse de debut
    \param char * data
        Le pointeur sur la premiere donnee
    \param uint32_t size
        Le nombre d'octet a ecrire
    \return uint32_t
        Le nombre de donnee ecrite
    
**/
uint32_t FLASH_write(uint32_t addr, char *data, uint32_t size) {
    uint32_t i = 0;
    FLASH_Unlock(FLASH_MEMTYPE_DATA);
    
    while( size ) {
        FLASH_ProgramByte(addr+i, data[i] );
        i++;
        size--;
    }
    
    FLASH_Lock(FLASH_MEMTYPE_DATA);
    
    return (i);
}


/**
    \fn uint32_t FLASH_read(uint32_t addr, char *data, uint32_t size)
    \brief Lit dans l'EEPROM
    \param uint32_t addr
        l'adresse de debut
    \param char * buffer
        Le buffer de destination
    \param uint32_t size
        Le nombre d'octet a lire
        \attention Le buffer doit etre suffisament grand
        
    \return uint32_t
        Le nombre de donnee lu
    
**/
uint32_t FLASH_read(uint32_t addr, char *buffer, uint32_t size) {
    uint32_t i = 0;
    
    while( size ){
        buffer[i] = FLASH_ReadByte(addr+i);
        i++;
        size--;
    }
    
    return i;
}





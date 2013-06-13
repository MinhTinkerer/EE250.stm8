



#include <stm8s.h>
#include <Flash.h>


void FLASH_init(void) {
	FLASH_DeInit();
	FLASH_SetProgrammingTime(FLASH_PROGRAMTIME_STANDARD);
}


void FLASH_putString(uint32_t addr, char* s) {
    FLASH_Unlock(FLASH_MEMTYPE_DATA);
	
	while( *s ) {
		FLASH_ProgramByte(addr+i, *(s++));
		i++;
	}
	FLASH_ProgramByte(addr+i, '\0');
    
    FLASH_Lock(FLASH_MEMTYPE_DATA);
}

char* FLASH_readString(u32 addr, char* buffer, int bufsize) {
	u32 i = 0;
	
	while(i < bufsize){
		buffer[i] = FLASH_ReadByte(addr+i);
		i++;
	}
	
	return buffer;
}





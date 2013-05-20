/*
 *	Fichier : main_flash.c
 *	Auteur : Alex&Guillaume
 *	Date : 05/05/13
 *	Description : Ecrit ou lit dans la memoire de donnees
 */

#include <stm8s.h>
#include <stm8s_flash.h>
#include <lib_stm8.h>

#define ADDRESS_OFFSET 0x000000
#define ADDRESS_CHAINE FLASH_DATA_START_PHYSICAL_ADDRESS+ADDRESS_OFFSET

#define BUFFER_SIZE 32

void FLASH_Putstring(u32 addr, char* s) {
	u32 i = 0;
	while(s[i]) {
		FLASH_ProgramByte(addr+i, s[i]);
		i++;
	}
	FLASH_ProgramByte(addr+i, '\0');
}

char* FLASH_Readstring(u32 addr, char* buffer, int bufsize) {
	u32 i = 0;
	
	while(i < bufsize){
		buffer[i] = FLASH_ReadByte(addr+i);
		i++;
	}
	
	return buffer;
}

main() {
	char c;
	u8 buffer[BUFFER_SIZE] = {0};

	UART2_init();
	
	FLASH_DeInit();
	FLASH_Unlock(FLASH_MEMTYPE_DATA);
	FLASH_SetProgrammingTime(FLASH_PROGRAMTIME_STANDARD);

	FLASH_Putstring(ADDRESS_CHAINE, "Texte 1");

	while(1) {
		UART2_Putstring("Bienvenue dans le programme d'edition de l'EEPROM.\r\n");
		UART2_Putstring("R to read, W to write.\r\n");
		c = UART2_GetChar();
		switch(c) {
			case 'R':
			case 'r':
				UART2_Putstring("Valeur : ");
				UART2_Putstring(FLASH_Readstring(ADDRESS_CHAINE, buffer, BUFFER_SIZE));
				UART2_Putstring("\r\n");
			break;
			case 'W':
			case 'w':
				UART2_Putstring("Ecriture de la chaine \"Le STM8 c'est biv !\" dans l'EEPROM du STM8\r\n");
				FLASH_Putstring(ADDRESS_CHAINE, "Le STM8 c'est biv !\r\n");
			break;
			default:
			break;
		}
	}
	
}
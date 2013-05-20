/*
 * Fichier : lib_stm8.c
 * Entete : lib_stm8.h
 * Auteur : Alex Nodet
 * Date : 08/05/2013
 */

#include <stm8s.h>
#include <stm8s_flash.h>

#include <lib_stm8.h>

void ITC_enableIT(void) {
	rim();
}

void UART2_init(void) {
	UART2->CR1 = UART2_ONESTARTBIT_EIGHTDATABITS_NOPARITY;
	UART2->CR3 = UART2->CR3 & ~UART2_CR3_STOP;
	
	UART2->BRR2 = UART2_BRR2_9600;
	UART2->BRR1 = UART2_BRR1_9600;
	
	UART2->CR2 |= UART2_CR2_TEN;
	UART2->CR2 |= UART2_CR2_REN;
}

void UART2_initITReceive(void) {
	UART2->CR2 |= UART2_CR2_RIEN;
}

char UART2_getChar(void) {
	while((UART2->SR & UART2_SR_RXNE) != UART2_SR_RXNE);
	return UART2->DR;
}

void UART2_putChar(char c) {
	while((UART2->SR & UART2_SR_TXE) != UART2_SR_TXE);
	UART2->DR = c;
}

void UART2_putString(char* s) {
	int i = 0;
	while(s[i]) {
		UART2_putChar(s[i]);
		i++;
	}
}

char UART2_RXNEFlag(void) {
	return (UART2->SR & UART2_SR_RXNE) == UART2_SR_RXNE;
}

void TIL321_init(void) {
	GPIOB->DDR = PB_ALL_OUT;				//Sortie
	GPIOB->CR1 = PB_ALL_PUSH_PULL;	//Push-pull
}

void TIL321_affiche(char c) {
	GPIOB->ODR = convertBCD2TIL(c);
}

void PortC_init(void) {
	GPIOC->DDR = PC_ALL_IN;
	GPIOC->CR1 = PC_ALL_PULLUP;
}

char PortC_IDR_filtre(void) {
	return GPIOC->IDR & PC_FILTRE_IDR;
}

int convertBCD2TIL(char c) {
	char caracteres[] = {	ZERO_TIL, UN_TIL, DEUX_TIL,	TROIS_TIL, QUATRE_TIL, CINQ_TIL, SIX_TIL, SEPT_TIL, HUIT_TIL, NEUF_TIL};
	
	if(c >= 0 && c < 10) {
		return caracteres[c];
	}
	else {
		return ERREUR_TIL;
	}
}

char* convertBCD2String(char c) {
	char* chaines[] = {"0\r\n", "1\r\n", "2\r\n", "3\r\n", "4\r\n", "5\r\n", "6\r\n", "7\r\n", "8\r\n", "9\r\n"};

	if(c >= 0 && c < 10) {
		return chaines[c];
 	}
	else {
		return "Erreur.\r\n";
	}
}

char num2ascii(char num) {
	return (num >= 0 && num < 10) ? (num + 0x30) : 'E';
}

char ascii2num(char ascii) {
	char n = ascii - 0x30;
	return (n >= 0 && n < 10) ? n : -1;
}

void LEDV_init(void) {
	GPIOD->DDR = GPIOD->DDR | GPIO_PIN_0;		//Sortie
	GPIOD->CR1 = GPIOD->CR1 & ~GPIO_PIN_0;	//Open Drain
}

void LEDV_etat(char c) {
	if(c == LEDV_ALLUME)
		GPIOD->ODR = GPIOD->ODR & ~GPIO_PIN_0;
	else
		GPIOD->ODR = GPIOD->ODR | GPIO_PIN_0;
}

void BP_init(char numero) {
	switch(numero) {
		case 1:
		GPIOD->DDR = GPIOD->DDR & ~GPIO_PIN_7;	//Entree
		GPIOD->CR1 = GPIOD->CR1 | GPIO_PIN_7;		//Pullup
		break;
		case 2:
		GPIOE->DDR = GPIOE->DDR & ~GPIO_PIN_7;	//Entree
		GPIOE->CR1 = GPIOE->CR1 | GPIO_PIN_7;		//Pullup
		break;
		default:
		break;
	}
}

char BP_etat(char numero) {
	switch(numero) {
		case 1:
		return (GPIOD->IDR | ~GPIO_PIN_7) == ~GPIO_PIN_7;
		case 2:
		return (GPIOE->IDR | ~GPIO_PIN_7) == ~GPIO_PIN_7;
		default:
		return BP_INACTIF;
	}
}

void BP_enableIT(char numero) {
	switch(numero) {
		case 1:
		GPIOD->CR2 = GPIOD->CR2 | GPIO_PIN_7;		//enable interrupt
		break;
		case 2:
		GPIOE->CR2 = GPIOE->CR2 | GPIO_PIN_7;		//enable interrupt
		break;
		default:
		break;
	}
}

void FLASH_init(void) {
	FLASH_DeInit();
	FLASH_SetProgrammingTime(FLASH_PROGRAMTIME_STANDARD);
}

void FLASH_unlockEEPROM(void) {
	FLASH_Unlock(FLASH_MEMTYPE_DATA);
}

void FLASH_lockEEPROM(void) {
	FLASH_Lock(FLASH_MEMTYPE_DATA);
}

void FLASH_putString(u32 addr, char* s) {
	u32 i = 0;
	while(s[i]) {
		FLASH_ProgramByte(addr+i, s[i]);
		i++;
	}
	FLASH_ProgramByte(addr+i, '\0');
}

char* FLASH_readString(u32 addr, char* buffer, int bufsize) {
	u32 i = 0;
	
	while(i < bufsize){
		buffer[i] = FLASH_ReadByte(addr+i);
		i++;
	}
	
	return buffer;
}


#ifndef LIB_STM8
#define LIB_STM8

/*
 * Fichier : lib_stm8.h
 * Auteur : Alex Nodet
 * Date : 08/05/2013
 */

#define UART2_ONESTARTBIT_EIGHTDATABITS_NOPARITY 0x00
#define UART2_BRR1_9600 0x0D
#define UART2_BRR2_9600 0x00

#define TOUCHE_ENTREE 0x0D

#define ZERO_TIL 0xFC
#define UN_TIL 0x60
#define DEUX_TIL 0xDA
#define TROIS_TIL 0xF2
#define QUATRE_TIL 0x66
#define CINQ_TIL 0xB6
#define SIX_TIL 0xBE
#define SEPT_TIL 0xE0
#define HUIT_TIL 0xFE
#define NEUF_TIL 0xF6
#define ERREUR_TIL 0x9E

#define PC_FILTRE_IDR 0x1E
#define PC_ALL_IN 0x00
#define PC_ALL_PULLUP 0xFF

#define LEDV_ALLUME 1
#define LEDV_ETEINT 0
#define LEDV_PERIODE 1000
#define LEDV_PAS 50

#define BP_ACTIF 1
#define BP_INACTIF 0

#define PB_ALL_OUT 0xFF
#define PB_ALL_PUSH_PULL 0xFF

#define TIM4_ARR 156
#define TIM4_PERIODE 10

void ITC_enableIT(void);

void UART2_init(void);
void UART2_initITReceive(void);
char UART2_getChar(void);
void UART2_putChar(char c);
void UART2_putString(char* s);
char UART2_RXNEFlag(void);

void TIL321_init(void);
void TIL321_affiche(char c);

void PortC_init(void);
char PortC_IDR_filtre(void);

int convertBCD2TIL(char c);
char* convertBCD2String(char c);

char num2ascii(char num);
char ascii2num(char ascii);

void LEDV_init(void);
void LEDV_etat(char c);

void BP_init(char numero);
char BP_etat(char numero);
void BP_enableIT(char numero);

void FLASH_init(void);
void FLASH_unlockEEPROM(void);
void FLASH_lockEEPROM(void);
void FLASH_putString(u32 addr, char* s);
char* FLASH_readString(u32 addr, char* buffer, int bufsize);

#endif //!LIB_STM8
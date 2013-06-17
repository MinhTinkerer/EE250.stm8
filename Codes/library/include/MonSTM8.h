/**
    \file MonSTM8.h
    \brief Prototypes utiles au STM8
    \author SCHLOTTERBECK Guillaume, PERARD Doriane
    \version 1.0
    \date 10/04/2013
	
	Maj : Alex Nodet, 17/06/2013
**/

#ifndef MONSTM8_H
#define MONSTM8_H

#include "stm8s.h"
#include "stm8s_exti.h"
#include "common.h"
#include "Serial.h"
#include "TIL321.h"
#include "Tim4.h"
#include "Flash.h"


/* SI i est un chiffre, 
       ALORS convertir en ASCII
   SINON
       renvoyer 'E'  */
#define num2ASCII(i) ((i<=9 && i>=0) ? i+0x30 : 'E')

#define ASCII2num(i) ((i<='9' && i>='0')? i-0x30 : -1)


extern void BP1_init(void);
extern void BP2_init(void);
extern void CLEF_init(void);
extern void GLED_init(void);

extern char BP1_actif(void); 
extern char BP2_actif(void); 
extern void BPs_IT_enable(char);

extern char CLEF_values(void);
extern char GLED_stat(void);
extern void GLED_enable(char);


#endif	/* !MONSTM8_H */

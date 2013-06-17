/**
    \file Tim4.h
    \brief Prototypes utiles a l'utilisation du Timer4
    \author SCHLOTTERBECK Guillaume, PERARD Doriane
    \version 1.0
    \date 10/04/2013
	
	Maj : Alex Nodet, 17/06/2013
**/

#ifndef TIM4_H
#define TIM4_H

#include "common.h"
#include "stm8s_tim4.h"



/**
  * @brief periode : 10ms. génére TIM4 update interruption
  *
  */
extern void Tim4_init(void);


extern void Tim4_ClearITBit(void);

extern void Tim4_Start(void);

extern void Tim4_Stop(void);



#endif	/* !TIM4_H */

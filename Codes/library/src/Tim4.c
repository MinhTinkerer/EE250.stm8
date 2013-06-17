/**
    \file Tim4.c
    \brief Fonctions utiles a l'utilisation du Timer4
    \author SCHLOTTERBECK Guillaume, PERARD Doriane
    \version 1.0
    \date 10/04/2013
	
	Maj : Alex Nodet, 17/06/2013
**/

#include "../include/Tim4.h"


void Tim4_init(void) {
    
    /* reset all registers */
    TIM4_DeInit();
    
    /* 10ms */
    TIM4_TimeBaseInit(TIM4_PRESCALER_128, 156);
    
    /* interrupt config */
    TIM4_ITConfig(TIM4_FLAG_UPDATE, ENABLE);
    
    /* source d'IT : quand on atteint la valeur. */
    // TIM4_UpdateRequestConfig(TIM4_UPDATESOURCE_GLOBAL); //TIM4_UPDATESOURCE_REGULAR
    
    /* tourne en boucle */
    TIM4_SelectOnePulseMode(TIM4_OPMODE_REPETITIVE);
    
    // TIM4_ARR manuel
    // TIM4_ARRPreloadConfig(DISABLE);
    
}



void Tim4_ClearITBit(void) {
    TIM4_ClearITPendingBit(TIM4_IT_UPDATE);
    
}


void Tim4_Start(void) {
    TIM4_Cmd(ENABLE);

}

void Tim4_Stop(void) {
    TIM4_Cmd(DISABLE);

}

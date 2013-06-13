/* MONSTM8.C file
 * 
 * SCHLOTTERBECK Guillaume
 * PERARD Doriane
 *
 * 10/04/2031
*/

#include "../include/MonSTM8.h"

void BP1_init() {
    // Le bouton 1
    SET(GPIOD->DDR, GPIO_PIN_7, INPUT);
    SET(GPIOD->CR1, GPIO_PIN_7, FLOATING);
    
    // GPIOD->DDR |= CONF(GPIO_PIN_7, INPUT);
    // GPIOD->CR1 |= CONF(GPIO_PIN_7, FLOATING);
}

void BP2_init() {
    // Le bouton 2
    SET(GPIOE->DDR, GPIO_PIN_7, INPUT);
    SET(GPIOE->CR1, GPIO_PIN_7, FLOATING);
    
    // GPIOE->DDR |= CONF(GPIO_PIN_7, INPUT);
    // GPIOE->CR1 |= CONF(GPIO_PIN_7, FLOATING);
}

void BPs_IT_enable(char b) {
    if ( b != 0) {
        SET(GPIOD->CR2, GPIO_PIN_7, ENABLE); // BP1
        SET(GPIOE->CR2, GPIO_PIN_7, ENABLE); // BP2
        
        // GPIOD->CR2 |= CONF(GPIO_PIN_7, ENABLE); // BP1
        // GPIOE->CR2 |= CONF(GPIO_PIN_7, ENABLE); // BP2
        
        EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOD, EXTI_SENSITIVITY_RISE_ONLY); // BP1
        EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOE, EXTI_SENSITIVITY_RISE_ONLY); // BP2
        
                    // EXTI_SENSITIVITY_FALL_LOW  : Interrupt on Falling edge and Low level
                    // EXTI_SENSITIVITY_RISE_ONLY : Interrupt on Rising edge only
                    // EXTI_SENSITIVITY_FALL_ONLY : Interrupt on Falling edge only
                    // EXTI_SENSITIVITY_RISE_FALL : Interrupt on Rising and Falling edges
        
    }
    else {
        SET(GPIOD->CR2, GPIO_PIN_7, DISABLE); // BP1
        SET(GPIOE->CR2, GPIO_PIN_7, DISABLE); // BP2
    
        // GPIOD->CR2 |= CONF(GPIO_PIN_7, DISABLE); // BP1
        // GPIOE->CR2 |= CONF(GPIO_PIN_7, DISABLE); // BP2
    }
}

void CLEF_init() {
    // les clefs
    SET(GPIOC->DDR, ALL, INPUT);
    SET(GPIOC->CR1, ALL, PULLUP);  
    
    // GPIOC->DDR |= CONF(ALL, INPUT);
    // GPIOC->CR1 |= CONF(ALL, PULLUP);    
}

void GLED_init() {
    SET(GPIOD->DDR, GPIO_PIN_0, OUTPUT); 
    SET(GPIOD->CR1, GPIO_PIN_0, OPENDRAIN);

    // GPIOD->DDR |= CONF(GPIO_PIN_0, OUTPUT); 
    // GPIOD->CR1 |= CONF(GPIO_PIN_0, OPENDRAIN);
}


char BP1_actif() {
    return !(GPIOD->IDR & GPIO_PIN_7);
}
 
char BP2_actif() {
    return !(GPIOE->IDR & GPIO_PIN_7);
} 

char CLEF_values() {
    return GPIOC->IDR;
}

char GLED_stat() {
    return (~GPIOD->ODR) & GPIO_PIN_0;
}

void GLED_enable(char v) {
    if ( v != 0 ) {
        // Allumer la LED
        GPIOD->ODR = GPIOD->ODR & ~GPIO_PIN_0;
    }
    else {
        // eteindre la LED
        GPIOD->ODR = GPIOD->ODR | GPIO_PIN_0;
    }
}





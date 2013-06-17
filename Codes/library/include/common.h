/**
    \file common.h
    \brief Definie des macro standards
    \author SCHLOTTERBECK Guillaume, PERARD Doriane
    \version 1.0
    \date 10/04/2013
	
	Maj : Alex Nodet, 17/06/2013
**/

#ifndef COMMON_H
#define COMMON_H

#include "stm8s.h"


#define RESET 0x00
#define INPUT 0x00
#define OUTPUT 0xFF
#define ALL 0xFF


#define OPENDRAIN 0x00
#define PUSHPULL 0xFF

#define FLOATING 0x00
#define PULLUP 0xFF

#define CONF(PIN, MODE) ( MODE & PIN )
#define SET(DEST, PIN, VAL) ( DEST = (VAL) ? (DEST | (PIN)) : (DEST & (~(PIN))) )


#define DISABLE 0
#define ENABLE 1


#endif	/* !COMMON_H */

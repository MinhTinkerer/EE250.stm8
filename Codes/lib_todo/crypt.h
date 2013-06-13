/**
 * \file crypt.h
 * \brief Fonctions de cryptage
 * \author Alex NODET
 * \version 0.1
 * \date 13 juin 2013
 */

 #ifndef CRYPT_H
#define CRYPT_H

#include "_stdint.h"

typedef uint16_t CRYPT_Key;

uint8_t CryptData(uint8_t* unsecureData, uint8_t len, CRYPT_Key key);
uint8_t UncryptData(uint8_t* secureData, uint8_t len, CRYPT_Key key);

#endif CRYPT_H
/**
 * \file crypt.c
 * \brief Implementation des fonctions de crypt.h
 * \author Alex NODET
 * \version 0.1
 * \date 13 juin 2013
 */

 #include "crypt.h"

/**
 * \fn uint8_t CryptData(uint8_t* unsecureData, uint8_t len, CRYPT_Key key)
 * \brief Remplace les donnees d'un buffer par leur valeur chiffree.
 *
 * \param unsecureData Pointeur sur le buffer a chiffrer.
 * \param len Taille du buffer.
 * \param key Clef de chiffrement.
 * \return Codes d'erreur.
 */
uint8_t CryptData(uint8_t* unsecureData, uint8_t len, CRYPT_Key key) {
	/* #TODORIANE */
	return 0;
}

/**
 * \fn uint8_t UncryptData(uint8_t* secureData, uint8_t len, CRYPT_Key key)
 * \brief Remplace les donnees d'un buffer par leur valeur dechiffree.
 *
 * \param secureData Pointeur sur le buffer a dechiffrer.
 * \param len Taille du buffer.
 * \param key Clef de chiffrement.
 * \return Codes d'erreur.
 */
uint8_t UncryptData(uint8_t* secureData, uint8_t len, CRYPT_Key key) {
	/* #TODORIANE */
	return 0;
}
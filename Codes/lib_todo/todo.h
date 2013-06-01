/**
 * \file todo.h
 * \brief Prototypes de la bibliotheque TODO
 * \author Alex NODET
 * \version 0.1
 * \date 3 juin 2013
 */

#ifndef TODO_H
#define TODO_H

/**
 * \def TODO_MAXDATALENGTH
 * \brief Donne le nombre maximal d'octets de donnees contenues dans un paquet TODO
 */
#define TODO_MAXDATALENGTH 0xFF

/**
 * \def TODO_ADDRMASK
 * \brief Masque permettant de recuperer les bits formant ADDR_SRC dans le paquet
 */
#define TODO_ADDRMASK 0xFE

/**
 * \def TODO_CRMASK
* \brief Masque permettant de recuperer le bit CR du paquet */
#define TODO_CRMASK 0x01

/**
 * \struct TODO_Packet todo.h
 * \brief Decrit le paquet TODO
 */
typedef struct {
	u8 addr;	/*!< Adresse source et bit de chiffrement */
	u8 length;	/*!< Nombre d'octets de donnees */
	u8 *data;	/*!< Pointeur sur le premier octet de donnees */
} TODO_Packet;

void TODO_DeInit(void);
void TODO_Init(u8 addr);

TODO_Packet* TODO_CreatePacket(const u8 *data, u8 len);
TODO_Packet* TODO_CreateSecurePacket(const u8 *data, u8 len, u8 key);

TODO_Packet* TODO_ExtractPacket(const u8 *buff, u8 len);
void TODO_UncryptPacket(TODO_Packet* securePacket, u8 key);
u8 TODO_IsPacketSecured(TODO_Packet* packet);

u8 TODO_Send(const TODO_Packet* packet);
u8 TODO_Recv(u8 buffer*, u8 len);

#endif
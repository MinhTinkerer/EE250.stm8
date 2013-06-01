/**
 * \file todo.h
 * \brief Interface utilisateur du protocole TODO pour le STM8
 * \author Alex NODET
 * \version 0.1
 * \date 3 juin 2013
 */

#ifndef TODO_H
#define TODO_H

#include "stm8s.h"
#include "stm8s_i2c.h"


/**
 * \def TODO_MAXDATALENGTH
 * \brief Donne le nombre maximal d'octets de donnees contenues dans un paquet TODO.
 */
#define TODO_MAXDATALENGTH 0xFF

/**
 * \def TODO_ADDRMASK
 * \brief Masque permettant de recuperer les bits formant ADDR_SRC dans un paquet TODO.
 */
#define TODO_ADDRMASK 0xFE

/**
 * \def TODO_CRMASK
 * \brief Masque permettant de recuperer le bit CR d'un paquet TODO.
 */
#define TODO_CRMASK 0x01

/**
 * \def TODO_ADDROFFSET
 * \brief Localisation de ADDR_SRC par rapport au debut d'un paquet TODO.
 */
#define TODO_ADDROFFSET 0x00

/**
 * \def TODO_LENGTHOFFSET
 * \brief Localisation de LENGTH par rapport au debut d'un paquet TODO.
 */
#define TODO_LENGTHOFFSET 0x01

/**
 * \def TODO_DATAOFFSET
 * \brief Localisation de DATA par rapport au debut d'un paquet TODO.
 */
#define TODO_DATAOFFSET 0x03

/**
 * \enum TODO_ErrorType
 * \brief Codes d'erreur
 */
typedef enum {
	NoError,			/*!< Pas d'erreur */
	PacketIsEmpty,		/*!< Le paquet ne contient pas de donnees */
	NoPacket,			/*!< Le pointeur sur paquet passe en parametre est nul */
	NullParameter,		/*!< Le second parametre est nul */
	BadDataAllocation,	/*!< Erreur d'allocation memoire */
	ReceptBufferIsNull	/*!< Le pointeur du buffer de reception est nul */
} TODO_ErrorType;

/**
 * \enum TODO_PacketState
 * \brief Etat du paquet : PacketSecured si le paquet est chiffre, PacketUnsecured sinon.
 */
typedef enum {
	PacketUnsecured,	/*!< Le bit CR du paquet indique que les donnees ne sont pas chiffrees */
	PacketSecured		/*!< Le bit CR du paquet indique que les donnees sont chiffrees */
} TODO_PacketState;

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

TODO_ErrorType TODO_FillPacket(TODO_Packet* packet, const u8 *data, u8 len);
TODO_ErrorType TODO_FillSecurePacket(TODO_Packet* packet, const u8 *unsecureData, u8 len, u8 key);

TODO_ErrorType TODO_ExtractPacket(TODO_Packet* packet, const u8 *buff);
TODO_ErrorType TODO_UncryptPacket(TODO_Packet* securePacket, u8 key);
TODO_ErrorType TODO_IsPacketSecured(TODO_Packet* packet, TODO_PacketState* state);

TODO_ErrorType TODO_Send(const TODO_Packet* packet, u8 destAddress);
TODO_ErrorType TODO_Recv(u8 *buffer);

#endif
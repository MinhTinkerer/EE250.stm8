/**
 * \file todo.h
 * \brief Interface utilisateur du protocole TODO pour le STM8S105C6.
 * \author Alex NODET
 * \version 0.1
 * \date 3 juin 2013
 */

#ifndef TODO_H
#define TODO_H

#include "_stdint.h"
#include "stm8s.h"
#include "stm8s_i2c.h"


/**
 * \def TODO_MAXDATALENGTH
 * \brief Donne le nombre maximal d'octets de donnees contenues dans un paquet TODO.
 */
#define TODO_MAXDATALENGTH 0xFF

#define TODO_MAXPACKETLENGTH TODO_MAXDATALENGTH+3

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
	NoError,			/*!< Pas d'erreur. */
	PacketIsEmpty,		/*!< Le paquet ne contient pas de donnees. */
	NoPacket,			/*!< Le pointeur sur paquet passe en parametre est nul. */
	NullParameter,		/*!< Le second parametre est nul. */
	BadDataAllocation,	/*!< Erreur d'allocation memoire. */
	ReceptBufferIsNull,	/*!< Le pointeur du buffer de reception est nul. */
	BadSizedPacket,		/*!< Le champ length du TODO_Packet ne correspond pas au nombre de donnees contenues. */
} TODO_ErrorType;

/**
 * \enum TODO_PacketState
 * \brief Etat du paquet : PacketSecured si le paquet est chiffre, PacketUnsecured sinon.
 */
typedef enum {
	PacketUnsecured,	/*!< Le bit CR du paquet indique que les donnees ne sont pas chiffrees. */
	PacketSecured		/*!< Le bit CR du paquet indique que les donnees sont chiffrees. */
} TODO_PacketState;

typedef enum {
	NewPacket = 0x01,
	DataOverflow = 0x02
} TODO_Flag;

typedef uint8_t TODO_Addr;
typedef uint16_t TODO_Key;

/**
 * \struct TODO_Packet todo.h
 * \brief Decrit le paquet TODO.
 */
typedef struct {
	TODO_Addr addr;		/*!< Adresse source et bit de chiffrement. */
	uint8_t length;		/*!< Nombre d'octets de donnees. */
	uint8_t *data;		/*!< Pointeur sur le premier octet de donnees. */
	// uint8_t secured;		/*!< bit. */
} TODO_Packet;


extern void TODO_Init(TODO_Addr addr, TODO_Key key);
extern void TODO_ChangeKey(TODO_Key newKey);
extern void TODO_Close(void);

extern TODO_Packet* TODO_CreatePacket(const uint8_t *data, u8 len);
extern void TODO_FreePacket(TODO_Packet* packet);

extern TODO_ErrorType TODO_Send(TODO_Addr destAddress, const uint8_t* datas, size_t size);
extern TODO_ErrorType TODO_SendSecure(TODO_Addr destAddress, uint8_t* datas, size_t size);
extern TODO_ErrorType TODO_SendPacket(TODO_Addr destAddress, const TODO_Packet* packet);
extern TODO_ErrorType TODO_SendSecurePacket(TODO_Addr destAddress, TODO_Packet* packet);

extern uint8_t TODO_NewPacketPresent(void);
extern @interrupt void TODO_ITHandler(void);

extern TODO_Packet* TODO_Recv(void);


#endif
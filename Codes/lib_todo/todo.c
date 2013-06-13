/**
 * \file todo.c
 * \brief Implementation des fonctions de todo.h
 * \author Alex NODET
 * \version 0.1
 * \date 3 juin 2013
 */

#include "todo.h"


typedef struct TODO_ReceivedRawBuffer TODO_ReceivedRawBuffer;
struct TODO_ReceivedRawBuffer {
	uint8_t *rawBuffer;
	TODO_ReceivedRawBuffer *next;
};

typedef TODO_ReceivedRawBuffer* TODO_RawBufferFile;


static uint8_t *receptBuffer;
static uint8_t dataCursor;
static uint8_t todoFlags;
static TODO_RawBufferFile receivedPackets = NULL;


/**
 * \fn void TODO_Init(TODO_Addr addr)
 * \brief Initialise le module I2C selon les specifications de TODO.
 *
 * Initialise le module I2C en adressage 7bits et configure les registres selon les specifications de TODO.
 *
 * \attention Le module I2C sera configure en mode standard, a 100kHz. De plus l'acquittement sera fait sur l'octet courant.
 *
 * \param addr Adresse TODO de ce STM8 sur le reseau.
 */
void TODO_Init(TODO_Addr addr) {
	I2C_Init(I2C_MAX_STANDARD_FREQ, (uint16_t)(addr), I2C_DUTYCYCLE_2, I2C_ACK_CURR, I2C_ADDMODE_7BIT, I2C_MAX_INPUT_FREQ);
}

/**
 * \fn void TODO_Close(void)
 * \brief Applique aux registres I2C leurs parametres par defaut.
 */
void TODO_Close(void) {
	I2C_DeInit();
}


/**
 * \fn TODO_ErrorType TODO_FillPacket(TODO_Packet* packet, const uint_8 *data, uint_8 len)
 * \brief Remplit un paquet TODO.
 *
 * Remplit un paquet TODO a partir des donnees et taille des donnees indiques. 
 * L'adresse source utilisee est celle indiquee a TODO_Init. 
 * Positionne le bit de poids faible du membre addr de packet a 0.
 *
 * Si data ou len est nul, le paquet sera valide mais sera vide.
 * Un paquet vide a les proprietes suivantes :
 * 		- addr = 0
 * 		- len = 0
 * 		- data = NULL
 *
 * \attention Les donnees sont incluses telles quelles dans le paquet. Utilisez TODO_FillSecurePacket pour chiffrer les donnees.
 *
 * \param packet Pointeur sur le paquet a remplir.
 * \param data Pointeur sur le premier octet de donnees.
 * \param len Nombre d'octets de donnees.
 * \return NoPacket si packet est nul, PacketIsEmpty si data ou len est nul, BadDataAllocation s'il y a erreur d'allocation du buffer de donnees du paquet, NoError sinon.
 */
TODO_ErrorType TODO_FillPacket(TODO_Packet* packet, const uint_8 *data, uint_8 len) {
	int i = 0;
	
	if(packet == NULL) {
		return NoPacket;
	}
	
	if(data == NULL || len == 0) {
		packet->addr = 0;
		packet->len = 0;
		packet->data = NULL;
		return PacketIsEmpty;
	}

	packet->addr = I2C->OARL & (u8)(~TODO_CRMASK);
	packet->len = len;
	
	packet->data = (u8*)malloc(len * sizeof(u8));
	if(packet->data == NULL) {
		return BadDataAllocation;
	}
	
	for(i = 0; i < len; i++) {
		packet->data[i] = data[i];
	}
	
	return NoError;
}

/**
 * \fn TODO_ErrorType TODO_FillSecurePacket(TODO_Packet* packet, const uint_8 *unsecureData, uint_8 len, TODO_Key key)
 * \brief Remplit un paquet TODO chiffre.
 *
 * Remplit un paquet TODO a partir des donnees et taille des donnees indiques.
 * L'adresse source utilisee est celle indiquee a TODO_Init.
 * Chiffre les donnees grace a la clef de chiffrement passee en parametre.
 * Positionne le bit de poids faible du membre addr de packet a 1.
 *
 * Si data ou len est nul, le paquet sera valide mais sera vide.
 * Un paquet vide a les proprietes suivantes :
 * 		- addr = 0
 * 		- len = 0
 * 		- data = NULL
 *
 * \param packet Pointeur sur le paquet a remplir.
 * \param unsecureData Pointeur sur le premier octet de donnees a chiffrer.
 * \param len Nombre d'octets de donnees.
 * \param key Clef de chiffrement a utiliser pour chiffrer les donnees pointees par data.
 * \return Codes d'erreur.
 */
TODO_ErrorType TODO_FillSecurePacket(TODO_Packet* packet, const uint_8 *unsecureData, uint_8 len, TODO_Key key) {
	/* #TODORIANE */
}

/**
 * \fn TODO_ErrorType TODO_ExtractPacket(TODO_Packet* packet, const uint8_t *buff)
 * \brief Reconnait un paquet TODO dans un buffer.
 *
 * Reconnait les membres d'une structure TODO_Packet dans un buffer de reception et les utilise pour remplir packet.
 * \attention L'adresse source reconnue ici n'a aucun lien avec celle indiquee par TODO_Init.
 *
 * \param packet Pointeur sur le paquet a remplir.
 * \param buff Pointeur sur le buffer.
 * \return NoPacket si packet est nul, NullParameter si buff est nul, PacketIsEmpty si le paquet ne contient pas de donnees, BadDataAllocation s'il y a erreur d'allocation du buffer de donnees du paquet, NoError sinon.
 */
TODO_ErrorType TODO_ExtractPacket(TODO_Packet* packet, const uint8_t *buff) {
	int i = 0;
	
	if(packet == NULL) {
		return NoPacket;
	}

	if(buff == NULL) {
		return NullParameter;
	}

	packet->len = buff[TODO_LENGTHOFFSET];
	
	if(packet->len == 0) {
		packet->addr = 0;
		packet->data = NULL;
		return PacketIsEmpty;
	}
	
	packet->addr = buff[TODO_ADDROFFSET];

	packet->data = (uint8_t*)malloc(packet->len * sizeof(uint8_t));
	if(packet->data == NULL) {
		return BadDataAllocation;
	}
	
	for(i = 0; i < packet->len; i++) {
		packet->data[i] = buff[TODO_DATAOFFSET + i];
	}
	
	return NoError;
}

/**
 * \fn static TODO_ErrorType TODO_CryptPacket(TODO_Packet* unsecurePacket, TODO_Key key)
 * \brief Remplace les donnees d'un paquet par leur valeur dechiffree.
 *
 * \param packet Pointeur sur le paquet a dechiffrer.
 * \param key Clef de chiffrement utilisee pour dechiffrer les donnees.
 * \return Codes d'erreur.
 */
static TODO_ErrorType TODO_CryptPacket(TODO_Packet* unsecurePacket, TODO_Key key) {
	/* #TODORIANE */
}

/**
 * \fn static TODO_ErrorType TODO_UncryptPacket(TODO_Packet* securePacket, TODO_Key key)
 * \brief Remplace les donnees d'un paquet par leur valeur dechiffree.
 *
 * \param packet Pointeur sur le paquet a dechiffrer.
 * \param key Clef de chiffrement utilisee pour dechiffrer les donnees.
 * \return Codes d'erreur.
 */
static TODO_ErrorType TODO_UncryptPacket(TODO_Packet* securePacket, TODO_Key key) {
	/* #TODORIANE */
}

/**
 * \fn static TODO_PacketState TODO_IsPacketSecured(const TODO_Packet* packet)
 * \brief Indique si les donnees du paquet sont chiffrees ou non en se basant sur le bit CR.
 *
 * \param packet Pointeur sur le paquet.
 * \param state Pointeur sur la variable d'etat a modifier.
 * \return NoPacket si packet est nul, NullParameter si state est nul, NoError sinon.
 */
static TODO_PacketState TODO_IsPacketSecured(const TODO_Packet* packet) {
	if(packet == NULL) {
		return NoPacket;
	}
	
	if(state == NULL) {
		return NullParameter;
	}
	
	if((packet->addr & TODO_CRMASK) == TODO_CRMASK) {
		*state = PacketSecured;
	}
	else {
		*state = PacketUnsecured;
	}
	
	return NoError;
}

/**
 * \fn TODO_ErrorType TODO_Send(const TODO_Packet* packet, u8 destAddress)
 * \brief Envoie un paquet TODO sur le bus I2C.
 *
 * \attention Methode bloquante jusqu'a ce que le paquet soit entierement envoye.
 *
 * \param packet Paquet a envoyer.
 * \param destAddress Adresse du destinataire.
 * \return NoPacket si packet est nul, NoError sinon.
 */
TODO_ErrorType TODO_Send(const TODO_Packet* packet, u8 destAddress) {
	int i = 0;
	
	if(packet == NULL) {
		return NoPacket;
	}
	
	I2C_GenerateSTART(ENABLE);
	
	while(I2C_GetFlagStatus(I2C_FLAG_TXEMPTY) == RESET);
	I2C_Send7bitAddress(destAddress & TODO_ADDRMASK, I2C_DIRECTION_TX);
	
	while(I2C_GetFlagStatus(I2C_FLAG_TXEMPTY) == RESET);
	I2C_SendData(packet->addr);
	
	while(I2C_GetFlagStatus(I2C_FLAG_TXEMPTY) == RESET);
	I2C_SendData(packet->len);
	
	while(I2C_GetFlagStatus(I2C_FLAG_TXEMPTY) == RESET);
	I2C_SendData(0x00);
	
	for(i = 0; i < packet->len; i++) {
		while(I2C_GetFlagStatus(I2C_FLAG_TXEMPTY) == RESET);
		I2C_SendData(packet->data[i]);
	}
	
	I2C_GenerateSTOP(ENABLE);
	
	return NoError;
}

/**
 * \fn TODO_ErrorType TODO_Recv(u8 *buffer)
 * \brief Recoit un paquet TODO depuis le bus I2C.
 *
 * Recoit des donnees structurees selon le protocole TODO depuis le bus I2C et les place dans un buffer de reception.
 *
 * \attention Methode bloquante tant que le paquet n'a pas ete entierement recu.
 *
 * \param buffer Pointeur sur le buffer de reception.
 * \return ReceptBufferIsNull si buffer est nul, NoError sinon.
 */
TODO_ErrorType TODO_Recv(u8 *buffer) {
	int i = 0;
	
	if(buffer == NULL) {
		return ReceptBufferIsNull;
	}
	
	while(I2C_GetFlagStatus(I2C_FLAG_RXNOTEMPTY) == RESET);
	buffer[TODO_ADDROFFSET] = I2C_ReceiveData();
	
	while(I2C_GetFlagStatus(I2C_FLAG_RXNOTEMPTY) == RESET);
	buffer[TODO_LENGTHOFFSET] = I2C_ReceiveData();
	
	while(I2C_GetFlagStatus(I2C_FLAG_RXNOTEMPTY) == RESET);
	buffer[TODO_LENGTHOFFSET + 1] = 0x00;
	
	for(i = 0; i < buffer[TODO_LENGTHOFFSET]; i++) {
		while(I2C_GetFlagStatus(I2C_FLAG_RXNOTEMPTY) == RESET);
		buffer[TODO_DATAOFFSET + i] = I2C_ReceiveData();
	}
	
	return NoError;
}
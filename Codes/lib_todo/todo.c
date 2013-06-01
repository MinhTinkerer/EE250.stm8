/**
 * \file todo.c
 * \brief Implementation des fonctions de todo.h
 * \author Alex NODET
 * \version 0.1
 * \date 3 juin 2013
 */

#include "todo.h"

/**
 * \fn void TODO_DeInit(void)
 * \brief Applique aux registres I2C leurs parametres par defaut.
 */
void TODO_DeInit(void) {
	I2C_DeInit();
}

/**
 * \fn void TODO_Init(u8 addr)
 * \brief Initialise le module I2C selon les specifications de TODO.
 *
 * Initialise le module I2C en adressage 7bits et configure les registres selon les specifications de TODO.
 *
 * \attention Le module I2C sera configure en mode standard, a 100kHz. De plus l'acquittement sera fait sur l'octet courant.
 *
 * \param addr Adresse TODO de ce STM8 sur le reseau.
 */
void TODO_Init(u8 addr) {
	I2C_Init(I2C_MAX_STANDARD_FREQ, (u16)(addr), I2C_DUTYCYCLE_2, I2C_ACK_CURR, I2C_ADDMODE_7BIT, I2C_MAX_INPUT_FREQ);
}

/**
 * \fn TODO_ErrorType TODO_FillPacket(TODO_Packet* packet, const u8 *data, u8 len)
 * \brief Remplit un paquet TODO.
 *
 * Remplit un paquet TODO a partir des donnees et taille des donnees indiques. 
 * L'adresse source utilisee est celle indiquee a TODO_Init. 
 * Positionne le bit de poids faible du membre addr de packet a 0.
 *
 * Si data ou len est nul, le paquet sera valide et ne contiendra pas de donnees. 
 *
 * \attention Les donnees sont incluses telles quelles dans le paquet. Utilisez TODO_FillSecurePacket pour chiffrer les donnees.
 *
 * \param packet Pointeur sur le paquet a remplir.
 * \param data Pointeur sur le premier octet de donnees.
 * \param len Nombre d'octets de donnees.
 * \return NoPacket si packet est nul, PacketIsEmpty si data ou len est nul, BadDataAllocation s'il y a erreur d'allocation du buffer de donnees du paquet, NoError sinon.
 */
TODO_ErrorType TODO_FillPacket(TODO_Packet* packet, const u8 *data, u8 len) {
	int i = 0;
	
	if(packet == NULL) {
		return NoPacket;
	}

	packet->addr = I2C->OARL & (u8)(~TODO_CRMASK);
	
	if(data == NULL || len == 0) {
		packet->len = 0;
		packet->data = NULL;
		return PacketIsEmpty;
	}

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
 * \fn TODO_ErrorType TODO_FillSecurePacket(TODO_Packet* packet, const u8 *unsecureData, u8 len, u8 key)
 * \brief Remplit un paquet TODO chiffre.
 *
 * Remplit un paquet TODO a partir des donnees et taille des donnees indiques.
 * L'adresse source utilisee est celle indiquee a TODO_Init.
 * Chiffre les donnees grace a la clef de chiffrement passee en parametre.
 * Positionne le bit de poids faible du membre addr de packet a 1.
 *
 * Si data ou len est nul, le paquet sera valide et ne contiendra pas de donnees.
 *
 * \param packet Pointeur sur le paquet a remplir.
 * \param unsecureData Pointeur sur le premier octet de donnees a chiffrer.
 * \param len Nombre d'octets de donnees.
 * \param key Clef de chiffrement a utiliser pour chiffrer les donnees pointees par data.
 * \return Codes d'erreur.
 */
TODO_ErrorType TODO_FillSecurePacket(TODO_Packet* packet, const u8 *unsecureData, u8 len, u8 key) {
	/* #TODORIANE */
}

/**
 * \fn TODO_ErrorType TODO_ExtractPacket(TODO_Packet* packet, const u8 *buff)
 * \brief Reconnait un paquet TODO dans un buffer.
 *
 * Reconnait les membres d'une structure TODO_Packet dans un buffer de reception et les utilise pour remplir packet.
 * \attention L'adresse source reconnue ici n'a aucun lien avec celle indiquee par TODO_Init.
 *
 * \param packet Pointeur sur le paquet a remplir.
 * \param buff Pointeur sur le buffer.
 * \return NoPacket si packet est nul, NullParameter si buff est nul, PacketIsEmpty si le paquet ne contient pas de donnees, BadDataAllocation s'il y a erreur d'allocation du buffer de donnees du paquet, NoError sinon.
 */
TODO_ErrorType TODO_ExtractPacket(TODO_Packet* packet, const u8 *buff) {
	int i = 0;
	
	if(packet == NULL) {
		return NoPacket;
	}

	if(buff == NULL) {
		return NullParameter;
	}

	packet->addr = buff[TODO_ADDROFFSET];	
	packet->len = buff[TODO_LENGTHOFFSET];
	
	if(packet->len == 0) {
		packet->data = NULL;
		return PacketIsEmpty;
	}

	packet->data = (u8*)malloc(packet->len * sizeof(u8));
	if(packet->data == NULL) {
		return BadDataAllocation;
	}
	
	for(i = 0; i < packet->len; i++) {
		packet->data[i] = buff[TODO_DATAOFFSET + i];
	}
	
	return NoError;
}

/**
 * \fn TODO_ErrorType TODO_UncryptPacket(TODO_Packet* securePacket, u8 key)
 * \brief Remplace les donnees d'un paquet par leur valeur dechiffree.
 *
 * \param packet Pointeur sur le paquet a dechiffrer.
 * \param key Clef de chiffrement utilisee pour dechiffrer les donnees.
 * \return Codes d'erreur.
 */
TODO_ErrorType TODO_UncryptPacket(TODO_Packet* securePacket, u8 key) {
	/* #TODORIANE */
}

/**
 * \fn TODO_ErrorType TODO_IsPacketSecured(TODO_Packet* packet, TODO_PacketState* state)
 * \brief Indique si les donnees du paquet sont chiffrees ou non en se basant sur le bit CR.
 *
 * \param packet Pointeur sur le paquet.
 * \param state Pointeur sur la variable d'etat a modifier.
 * \return NoPacket si packet est nul, NullParameter si state est nul, NoError sinon.
 */
TODO_ErrorType TODO_IsPacketSecured(TODO_Packet* packet, TODO_PacketState* state) {
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
 * \attention Methode bloquante tant que les octets de donnees n'ont pas tous ete recus.
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
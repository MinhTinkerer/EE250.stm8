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


static CRYPT_Key internKey;
static uint8_t *receptBuffer;
static uint8_t dataCursor;
static uint8_t todoFlags;
static TODO_RawBufferFile receivedPackets = NULL;


/**
 * \fn void TODO_Init(TODO_Addr addr, TODO_Key key)
 * \brief Initialise le module I2C selon les specifications de TODO.
 *
 * Initialise le module I2C en adressage 7bits et configure les registres selon les specifications de TODO.
 *
 * \attention Le module I2C sera configure en mode standard, a 100kHz. De plus l'acquittement sera fait sur l'octet courant.
 *
 * \param addr Adresse TODO de ce STM8 sur le reseau.
 */
void TODO_Init(TODO_Addr addr, TODO_Key key) {
	internKey = key;
	I2C_Init(I2C_MAX_STANDARD_FREQ, (uint16_t)(addr), I2C_DUTYCYCLE_2, I2C_ACK_CURR, I2C_ADDMODE_7BIT, I2C_MAX_INPUT_FREQ);
}

/**
 * \fn void TODO_ChangeKey(TODO_Key newKey)
 * \brief Change la clef de chiffrement.
 */
void TODO_ChangeKey(TODO_Key newKey) {
	internKey = key;
}

/**
 * \fn void TODO_Close(void)
 * \brief Applique aux registres I2C leurs parametres par defaut.
 */
void TODO_Close(void) {
	I2C_DeInit();
}


TODO_Packet* TODO_CreatePacket(const uint8_t *data, u8 len) {
	return NULL;
}

void TODO_FreePacket(TODO_Packet* packet) {

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
uint8_t TODO_Send(TODO_Addr destAddress, const uint8_t* datas, size_t size) {
	int i = 0;
	
	if(datas == NULL) {
		return 0;
	}
	
	I2C_GenerateSTART(ENABLE);
	
	while(I2C_GetFlagStatus(I2C_FLAG_TXEMPTY) == RESET);
	I2C_Send7bitAddress(destAddress & TODO_ADDRMASK, I2C_DIRECTION_TX);
	
	while(I2C_GetFlagStatus(I2C_FLAG_TXEMPTY) == RESET);
	I2C_SendData(datas[0]);
	
	while(I2C_GetFlagStatus(I2C_FLAG_TXEMPTY) == RESET);
	I2C_SendData(datas[1]);
	
	while(I2C_GetFlagStatus(I2C_FLAG_TXEMPTY) == RESET);
	I2C_SendData(0x00);
	
	for(i = 0; i < packet->len; i++) {
		while(I2C_GetFlagStatus(I2C_FLAG_TXEMPTY) == RESET);
		I2C_SendData(datas[TODO_DATAOFFSET+i]);
	}
	
	I2C_GenerateSTOP(ENABLE);
	
	return i+1;
}

uint8_t TODO_SendSecure(TODO_Addr destAddress, uint8_t* datas, size_t size) {
	CryptData(datas, size, internKey);
	TODO_Send(destAddress, datas, size);
}

uint8_t TODO_SendPacket(TODO_Addr destAddress, const TODO_Packet* packet) {
	int i = 0;
	
	if(packet == NULL) {
		return 0;
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
	
	return i+1;
}

uint8_t TODO_SendSecurePacket(TODO_Addr destAddress, TODO_Packet* packet) {
	CryptData(packet->data, packet->length, internKey);
	TODO_SendPacket(destAddress, packet);
}


uint8_t TODO_NewPacketPresent(void) {
	if(TODO_GetFlagState(DataOverflow)) {
		dataCursor = 0;
		TODO_ClearFlag(DataOverflow);
		return (uint8_t)0;	/* on ignore le paquet car il est plus grand que ce que prevoit le protocole */
	}
	
	if(TODO_GetFlagState(NewTODOPacket)) {
		if(receptBuffer[TODO_LENGTHOFFSET] != dataCursor) {
			return (uint8_t)0;	/* on ignore le paquet car il n'annonce pas le bon nombre d'octets de donnees */
		}
		
		addRawPacket(receptBuffer);
		
		assert( receptBuffer = (uint8_t*)malloc( TODO_MAXPACKETLENGTH * sizeof(uint8_t) ) );

		dataCursor = 0;
		TODO_ClearFlag(NewTODOPacket);
		
		return (uint8_t)1;
	}
	
	return (uint8_t)0;
}

@interrupt void TODO_ITHandler(void) {
	/* S'il y a un octet a lire */
	if(I2C_GetITStatus(I2C_ITPENDINGBIT_RXNOTEMPTY)) {
		
		if(receivedPackets != NULL) {
		
			if(dataCursor < TODO_MAXPACKETLENGTH) {
				/* On met l'octet recu dans le buffer de donnees, */
				/* celui ci sera redirigé dans l'octet d'addresse ou de taille si besoin. */
				receptBuffer[dataCursor] = I2C_ReceiveData();
			}
			dataCursor++;
		}
		
		I2C_ClearITPendingBit(I2C_ITPENDINGBIT_RXNOTEMPTY);
	}

	/* Si le bit STOP est detecte */
	if(I2C_GetITStatus(I2C_ITPENDINGBIT_STOPDETECTION)) {
	
		if(dataCursor <= TODO_MAXPACKETLENGTH) {
			/* Si c'est le dernier octet recu, on leve NewPacket */
			todoFlags |= NewPacket;
		}
		else(dataCursor > TODO_MAXPACKETLENGTH) {
			/* Si le curseur du buffer du reception depasse la taille maximum d'un paquet, on leve DataOverflow */
			todoFlags |= DataOverflow;
		}
		
		I2C_ClearITPendingBit(I2C_ITPENDINGBIT_STOPDETECTION);
	}
}


TODO_Packet* TODO_Recv(void) {
	if(receivedPackets == NULL) {
		return NULL;
	}
	
	TODO_Packet *packet;
	assert( packet = (TODO_Packet*)malloc(sizeof(TODO_Packet)) );
	
	TODO_ReceivedRawBuffer* bufferRecu = defileRawBuffer();
	packet->addr = bufferRecu->rawBuffer[0];
	packet->length = bufferRecu->rawBuffer[1];
	packet->data = bufferRecu->rawBuffer[3];
	
	free(bufferRecu);
	
	return packet;
}


static FlagStatus TODO_GetFlagState(TODO_Flag flag) {
	if((todoFlags & flag) == flag) {
		return SET;
	}
	
	return RESET;
}

static void TODO_ClearFlag(TODO_Flag flag) {
	todoFlags &= (uint8_t)(~flag);
}



static void addRawBuffer(uint8_t* buf) {
	TODO_RawBufferFile tete = receivedPackets;
	TODO_ReceivedRawBuffer* nouveauPaquet = NULL;
	
	assert( nouveauPaquet = (TODO_ReceivedRawBuffer*)malloc( sizeof(TODO_ReceivedRawBuffer) ) );

	nouveauPaquet->rawBuffer = buf;
	nouveauPaquet->next = NULL;
	
	if(tete == NULL) {
		tete = nouveauPaquet;
	}
	else {
		while(tete != NULL && tete->next != NULL) {
			tete = tete->next;
		}
		tete->next = nouveauPaquet;
	}
}

static TODO_ReceivedRawBuffer* defileRawBuffer(void) {
	TODO_ReceivedRawBuffer *tete = receivedPackets;
	if(tete != NULL) {
		receivedPackets = receivedPackets->next;
		tete->next = NULL;
		return tete;
	}
	
	return NULL;
}

static void freeRawBufferFile(TODO_RawBufferFile tete) {
	if(tete != NULL) {
		if(tete->next != NULL) {
			freeRawBufferFile(tete->next);
		}
		free(tete->rawBuffer);
		free(tete);
	}
}


/**
 * \fn static TODO_PacketState TODO_IsPacketSecured(const TODO_Packet* packet)
 * \brief Indique si les donnees du paquet sont chiffrees ou non en se basant sur le bit CR.
 *
 * \param packet Pointeur sur le paquet.
 * \param state Pointeur sur la variable d'etat a modifier.
 * \return NoPacket si packet est nul, NullParameter si state est nul, NoError sinon.
 */
static TODO_ErrorType TODO_IsPacketSecured(const TODO_Packet* packet) {
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
TODO_ErrorType tRecv(u8 *buffer) {
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
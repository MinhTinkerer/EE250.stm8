/**
 * \file todo.c
 * \brief 
 * \author Alex NODET
 * \version 0.1
 * \date 3 juin 2013
 */

 #include <todo.h>

/**
 * \fn void TODO_DeInit(void)
 * \brief Applique aux registres I2C leurs parametres par defaut.
 */
void TODO_DeInit(void);

/**
 * \fn void TODO_Init(u8 addr)
 * \brief Initialise le module I2C selon les specifications de TODO.
 *
 * Initialise le module I2C en adressage 7bits et configure les registres selon les specifications de TODO.
 *
 * \attention Le module I2C sera configuré en mode standard, a 100kHz. De plus l'acquittement sera fait sur l'octet courant.
 *
 * \param addr Adresse TODO de ce STM8 sur le reseau.
 */
void TODO_Init(u8 addr);

/**
 * \fn TODO_ErrorType TODO_FillPacket(TODO_Packet* packet, const u8 *data, u8 len)
 * \brief Remplit un paquet TODO.
 *
 * Remplit un paquet TODO a partir des donnees et taille des donnees indiques. 
 * L'adresse source utilisee est celle indiquee a TODO_Init. 
 * Positionne le bit de poids faible du membre addr de packet a 0.
 *
 * \attention Les donnees sont incluses telles quelles dans le paquet. Utilisez TODO_FillSecurePacket pour chiffrer les donnees.
 *
 * \param packet Pointeur sur le paquet a remplir.
 * \param data Pointeur sur le premier octet de donnees.
 * \param len Nombre d'octets de donnees.
 * \return Un code d'erreur.
 */
TODO_ErrorType TODO_FillPacket(TODO_Packet* packet, const u8 *data, u8 len);

/**
 * \fn TODO_ErrorType TODO_FillSecurePacket(TODO_Packet* packet, const u8 *data, u8 len, u8 key)
 * \brief Remplit un paquet TODO chiffre.
 *
 * Remplit un paquet TODO a partir des donnees et taille des donnees indiques. 
 * L'adresse source utilisee est celle indiquee a TODO_Init. 
 * Chiffre les donnees grace a la clef de chiffrement passee en parametre.
 * Positionne le bit de poids faible du membre addr de packet a 1.
 *
 * \param packet Pointeur sur le paquet a remplir.
 * \param data Pointeur sur le premier octet de donnees.
 * \param len Nombre d'octets de donnees.
 * \param key Clef de chiffrement a utiliser pour chiffrer les donnees pointees par data.
 * \return Un code d'erreur.
 */
TODO_ErrorType TODO_FillSecurePacket(TODO_Packet* packet, const u8 *data, u8 len, u8 key);

/**
 * \fn TODO_ErrorType TODO_ExtractPacket(TODO_Packet* packet, const u8 *buff, u8 len)
 * \brief Reconnait un paquet TODO dans un buffer.
 *
 * Reconnait les membres d'une structure TODO_Packet dans un buffer de reception et les utilise pour remplir packet.
 * \attention L'adresse source reconnue ici n'a aucun lien avec celle indiquee par TODO_Init.
 *
 * \param packet Pointeur sur le paquet a remplir.
 * \param buff Pointeur sur le buffer.
 * \param len Nombre d'octets de donnees a reconnaitre.
 * \return Un code d'erreur.
 */
TODO_ErrorType TODO_ExtractPacket(TODO_Packet* packet, const u8 *buff, u8 len);

/**
 * \fn void TODO_UncryptPacket(TODO_Packet* securePacket, u8 key)
 * \brief Remplace les donnees d'un paquet par leur valeur dechiffree.
 *
 * \param packet Pointeur sur le paquet a dechiffrer.
 * \param key Clef de chiffrement utilisee pour dechiffrer les donnees.
 */
void TODO_UncryptPacket(TODO_Packet* securePacket, u8 key);

/**
 * \fn TODO_PacketState TODO_IsPacketSecured(TODO_Packet* packet)
 * \brief Indique si les donnees du paquet sont chiffrees ou non en se basant sur le bit CR.
 *
 * \param packet Pointeur sur le paquet.
 * \return PacketSecured si le paquet est chiffre, PacketUnsecured sinon.
 */
TODO_PacketState TODO_IsPacketSecured(TODO_Packet* packet);

/**
 * \fn TODO_ErrorType TODO_Send(const TODO_Packet* packet)
 * \brief Envoie un paquet TODO sur le bus I2C.
 *
 * \param packet Paquet a envoyer.
 * \return Un code d'erreur.
 */
TODO_ErrorType TODO_Send(const TODO_Packet* packet);

/**
 * \fn TODO_ErrorType TODO_Recv(u8 buffer*, u8 len)
 * \brief Recoit un paquet TODO depuis le bus I2C.
 *
 * Recoit des donnees structurees selon le protocole TODO depuis le bus I2C et les place dans un buffer de reception.
 *
 * \attention Methode bloquante tant que les len octets de donnees n'ont pas ete recus.
 *
 * \param buffer Pointeur sur le buffer de reception.
 * \param len Nombre d'octets de donnees a lire.
 * \return Un code d'erreur.
 */
TODO_ErrorType TODO_Recv(u8 buffer*, u8 len);

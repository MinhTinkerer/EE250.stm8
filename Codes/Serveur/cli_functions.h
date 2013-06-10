/**
    \file cli_functions.h
    \brief 
    \author SCHLOTTERBECK Guillaume
    \version 1.0
    \date 10/06/2013
**/


#ifndef CLI_FUNCTIONS_H
#define CLI_FUNCTIONS_H




/**
    \fn extern int _puts(char *);
    \brief Fonction de sortie de la CLI
    \par char *
        La chaine de caractere a envoyer
    \return int
        Le nombre de caractere envoye
    
    \attention
        Vous devez definir cette fonction.
**/
extern int _puts(char *);



/**
    \def CLIf_nbrCmd
    \brief Le nombre de commande
**/
#define CLIf_nbrCmd 1


int hl(char *);



#endif




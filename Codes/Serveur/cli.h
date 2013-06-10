/**
    \file cli.h
    \brief 
    \author SCHLOTTERBECK Guillaume
    \version 1.0
    \date 10/06/2013
**/

#ifndef CLI_H
#define CLI_H


#include <string.h>
#include "_stdint.h"


#include"cli_functions.h"



#define MAXNAME 16


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
    \struct CLI_Cmd
    \brief Une commande et sa fonction
*/
typedef struct {
    char name[MAXNAME]; /*!< Le nom de la commande */
    int (*func)(char *); /*!< Le pointeur de fonction */
} CLI_Cmd;




// UI to delete CLI_Cmds
extern void CLI_close();

// UI to exec commmand line (CL)
extern int CLI_runCL(char *);


#endif


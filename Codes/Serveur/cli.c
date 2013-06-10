/**
    \file cli.c
    \brief 
    \author SCHLOTTERBECK Guillaume
    \version 1.0
    \date 10/06/2013
**/


#include "cli.h"


/**
    \var CLI_Cmds *CLI_Package
    \brief Contient les commandes. global et static
**/
static CLI_Cmd CLI_Package[CLIf_nbrCmd] = {
    {"hello", hl}


};



/**
    \fn static struct CLI_Cmds *CLI_searchCmd(char *)
    \brief Cherche une commande dans #CLI_Package
    \param  char *
        La ligne de commande
    \retval int16_t
        L'index de la commande recherchee.
        Si il n'y a pas de commande correspondante, renvoi -1.
**/
static int16_t CLI_searchCmd(char *);





/**
    \fn int CLI_runCL(char *cmd)
    \brief Execute la commande passe en parametre
    \param  char*
        La ligne de commande
    \retval int
        La valeure renvoyer par la commande
**/
int CLI_runCL(char *cmd) {
    
    int16_t cl = -1;
    char *param = cmd;
    
    cl = CLI_searchCmd(cmd);
    if (cl == -1) {
        _puts("error: command not found\n");
        return (-1);
    }
    
    // cherche le debut des parametres
    while ( *param ) {
        if ( *param == ' ' ) {
            param++;
            break;
        }
        param++;
    }
    
    // l'execute
    return ((*(CLI_Package[cl]).func))(param);
}




int16_t CLI_searchCmd(char *cmd) {
    int n;
    int16_t cl = -1;
    char *p;
    
    // enleve les espaces au debut
    while ( (*cmd) == ' ' ) cmd++;
    
    
    // verifie que le champ est non vide
    if ( !cmd ) {
        return (-1);
    }
       
    // compte dans n le nombre de lettre dans le nom de la commande
    n = 0;
    for ( p = cmd ; (*p != '\0' && *p != ' ') ; p++) { 
        n++;
    }
    n = (n < MAXNAME) ? n : MAXNAME-1;
    
    // cherche une correspondance
    for ( cl=0 ; cl<CLIf_nbrCmd ; cl++ ) {
        if ( !strncmp( cmd, CLI_Package[cl].name, n ) )
            return (cl);
    }
    
    // command not found
    return (-1);
}



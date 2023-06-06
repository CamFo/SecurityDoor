/**
 * @file processusGestionPairing.h
 * @author Ilyes Gharmoul (ilyesdu2002@hotmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-05-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef PROCESSUSGGESTIONPAIRING_H
#define PROCESSUSGGESTIONPAIRING_H

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//pas de dependances materielles

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")


//INFORMATION PUBLIQUE:
//Definitions publiques:
#define PROCESSUSGGESTIONPAIRING_FINISHEDPAIRING 1
#define PROCESSUSGGESTIONPAIRING_ATTEMPTPAIRING 0
// Structure d'envoie et de réception
extern unsigned char processusGestionPairing_PairedState;

//Fonctions publiques:
void processusGestionPairing_initialise(void);

//Variables publiques:
//pas de variables publiques
#endif
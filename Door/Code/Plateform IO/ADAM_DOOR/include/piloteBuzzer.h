/**
 * @file piloteBuzzer.h
 * @author Ilyes Gharmoul (ilyesdu2002@hotmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-05-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef PILOTEBUZZER_H
#define PILOTEBUZZER_H

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define PILOTEBUZZER_BROCHE 24
//#define PILOTEBUZZER_ETAT_INITIAL_A_UN
//#define PILOTEBUZZER_ETAT_INITIAL_A_ZERO

//Dependances logicielles
//pas de dependances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
// pas de definitions publiques

//Fonctions publiques:

/**
 * @brief Fonction qui met a 5V la broche \ref PILOTEBUZZER_BROCHE du microcontrôleur 
 * 
 */
void piloteBuzzer_metAUn(void);
/**
 * @brief Fonction qui met a 0V la broche \ref PILOTEBUZZER_BROCHE du mirocontrôleur
 * 
 */
void piloteBuzzer_metAZero(void);
/**
 * @brief Fonciton qui met la broche \ref PILOTEBUZZER_BROCHE du mirocontrôleur
 *   au niveau passé en paramètre: 1 ou 0
 * 
 * @param Niveau 
 */
void piloteBuzzer_metA(unsigned char Niveau);
/**
 * @brief Fonction d'initialisation de la broche \ref piloteBUZZER_BROCHE
 *  du mirocontrôleur. Met la broche du microcontrôleur en sortie et assigne
 *  sa valeur initial selon la définition \ref PILOTEBUZZER_ETAT_INITIAL_A_ZERO
 *  ou \ref PILOTEBUZZER_ETAT_INITIAL_A_UN.
 * 
 */
void piloteBuzzer_initialise(void);

//Variables publiques:
//pas de variables publiques


#endif
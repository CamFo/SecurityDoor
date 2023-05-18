/**
 * @file piloteIOIR2.h
 * @author Ilyes Gharmoul (ilyesdu2002@hotmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-05-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef PILOTEIOIR2_H
#define PILOTEIOIR2_H

//MODULE: piloteIOIR2
//DESCRIPTION: pour permettre la commande d'une sortie en "push-pull" (teste avec ESP32)
// 2022-04-11, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define PILOTEIOIR2_BROCHE 26
//#define PILOTEIOIR2_ETAT_INITIAL_A_UN
//#define PILOTEIOIR2_ETAT_INITIAL_A_ZERO

//Dependances logicielles
//pas de dependances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
// pas de definitions publiques

//Fonctions publiques:

/**
 * @brief Fonction qui met a 5V la broche \ref PILOTEIOIR2_BROCHE du microcontrôleur 
 * 
 */
void piloteIOIR2_metAUn(void);
/**
 * @brief Fonction qui met a 0V la broche \ref PILOTEIOIR2_BROCHE du mirocontrôleur
 * 
 */
void piloteIOIR2_metAZero(void);
/**
 * @brief Fonciton qui met la broche \ref PILOTEIOIR2_BROCHE du mirocontrôleur
 *   au niveau passé en paramètre: 1 ou 0
 * 
 * @param Niveau 
 */
void piloteIOIR2_metA(unsigned char Niveau);
/**
 * @brief Fonction d'initialisation de la broche \ref piloteIOIR2_BROCHE
 *  du mirocontrôleur. Met la broche du microcontrôleur en sortie et assigne
 *  sa valeur initial selon la définition \ref PILOTEIOIR2_ETAT_INITIAL_A_ZERO
 *  ou \ref PILOTEIOIR2_ETAT_INITIAL_A_UN.
 * 
 */
void piloteIOIR2_initialise(void);

//Variables publiques:
//pas de variables publiques
#endif

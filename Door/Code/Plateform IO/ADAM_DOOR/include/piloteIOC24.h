/**
 * @file piloteIOC24.ino
 * @author Ilyes Gharmoul (ilyesdu2002@hotmail.com)
 * @brief Pilote qui contrôle la broche d'un microcontrôleur en utilisant
 *  la librairie Arduino. (digitalWrite et pinMode)
 * 
 * @version 0.1
 * @date 2022-11-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef PILOTEIOC24_H
#define PILOTEIOC24_H

//MODULE: piloteIOC24
//DESCRIPTION: pour permettre la commande d'une sortie en "push-pull" (teste avec ESP32)
// 2022-04-11, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define PILOTEIOC24_BROCHE 24
//#define PILOTEIOC24_ETAT_INITIAL_A_UN
//#define PILOTEIOC24_ETAT_INITIAL_A_ZERO

//Dependances logicielles
//pas de dependances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
// pas de definitions publiques

//Fonctions publiques:

/**
 * @brief Fonction qui met a 5V la broche \ref PILOTEIOC24_BROCHE du microcontrôleur 
 * 
 */
void piloteIOC24_metAUn(void);
/**
 * @brief Fonction qui met a 0V la broche \ref PILOTEIOC24_BROCHE du mirocontrôleur
 * 
 */
void piloteIOC24_metAZero(void);
/**
 * @brief Fonciton qui met la broche \ref PILOTEIOC24_BROCHE du mirocontrôleur
 *   au niveau passé en paramètre: 1 ou 0
 * 
 * @param Niveau 
 */
void piloteIOC24_metA(unsigned char Niveau);
/**
 * @brief Fonction d'initialisation de la broche \ref piloteIOC24_BROCHE
 *  du mirocontrôleur. Met la broche du microcontrôleur en sortie et assigne
 *  sa valeur initial selon la définition \ref PILOTEIOC24_ETAT_INITIAL_A_ZERO
 *  ou \ref PILOTEIOC24_ETAT_INITIAL_A_UN.
 * 
 */
void piloteIOC24_initialise(void);

//Variables publiques:
//pas de variables publiques
#endif

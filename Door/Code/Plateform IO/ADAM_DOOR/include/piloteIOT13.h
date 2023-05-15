/**
 * @file piloteIOT13.ino
 * @author CamFo Camille Fortin (camfortin2022@gmail.com)
 * @brief Pilote qui contrôle la broche d'un microcontrôleur en utilisant
 *  la librairie Arduino. (digitalWrite et pinMode)
 * 
 * @version 0.1
 * @date 2022-11-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef PILOTEIOT13_H
#define PILOTEIOT13_H

//MODULE: piloteIOT13
//DESCRIPTION: pour permettre la commande d'une sortie en "push-pull" (teste avec ESP32)
// 2022-04-11, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define PILOTEIOT13_BROCHE 13
//#define PILOTEIOT13_ETAT_INITIAL_A_UN
//#define PILOTEIOT13_ETAT_INITIAL_A_ZERO

//Dependances logicielles
//pas de dependances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
// pas de definitions publiques

//Fonctions publiques:

/**
 * @brief Fonction qui met a 5V la broche \ref PILOTEIOT13_BROCHE du microcontrôleur 
 * 
 */
void piloteIOT13_metAUn(void);
/**
 * @brief Fonction qui met a 0V la broche \ref PILOTEIOT13_BROCHE du mirocontrôleur
 * 
 */
void piloteIOT13_metAZero(void);
/**
 * @brief Fonciton qui met la broche \ref PILOTEIOT13_BROCHE du mirocontrôleur
 *   au niveau passé en paramètre: 1 ou 0
 * 
 * @param Niveau 
 */
void piloteIOT13_metA(unsigned char Niveau);
/**
 * @brief Fonction d'initialisation de la broche \ref PILOTEIOT13_BROCHE
 *  du mirocontrôleur. Met la broche du microcontrôleur en sortie et assigne
 *  sa valeur initial selon la définition \ref PILOTEIOT13_ETAT_INITIAL_A_ZERO
 *  ou \ref PILOTEIOT13_ETAT_INITIAL_A_UN.
 * 
 */
void piloteIOT13_initialise(void);

//Variables publiques:
//pas de variables publiques
#endif

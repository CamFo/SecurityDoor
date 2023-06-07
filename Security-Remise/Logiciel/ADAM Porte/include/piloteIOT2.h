/**
 * @file piloteIOT2.ino
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
#ifndef PILOTEIOT2_H
#define PILOTEIOT2_H

//MODULE: piloteIOT2
//DESCRIPTION: pour permettre la commande d'une sortie en "push-pull" (teste avec ESP32)
// 2022-04-11, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define PILOTEIOT2_BROCHE 2
//#define PILOTEIOT2_ETAT_INITIAL_A_UN
//#define PILOTEIOT2_ETAT_INITIAL_A_ZERO

//Dependances logicielles
//pas de dependances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
// pas de definitions publiques

//Fonctions publiques:

/**
 * @brief Fonction qui met a 5V la broche \ref PILOTEIOT2_BROCHE du microcontrôleur 
 * 
 */
void piloteIOT2_metAUn(void);
/**
 * @brief Fonction qui met a 0V la broche \ref PILOTEIOT2_BROCHE du mirocontrôleur
 * 
 */
void piloteIOT2_metAZero(void);
/**
 * @brief Fonciton qui met la broche \ref PILOTEIOT2_BROCHE du mirocontrôleur
 *   au niveau passé en paramètre: 1 ou 0
 * 
 * @param Niveau 
 */
void piloteIOT2_metA(unsigned char Niveau);
/**
 * @brief Fonction d'initialisation de la broche \ref PILOTEIOT2_BROCHE
 *  du mirocontrôleur. Met la broche du microcontrôleur en sortie et assigne
 *  sa valeur initial selon la définition \ref PILOTEIOT2_ETAT_INITIAL_A_ZERO
 *  ou \ref PILOTEIOT2_ETAT_INITIAL_A_UN.
 * 
 */
void piloteIOT2_initialise(void);

//Variables publiques:
//pas de variables publiques
#endif

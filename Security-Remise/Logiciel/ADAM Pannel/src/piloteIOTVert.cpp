/**
 * @file piloteIOTVert.ino
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
//piloteIOTVert:
//Historique: 
// 2021-04-07, Yves Roy, creation

//INCLUSIONS
#include <Arduino.h>
#include "main.h"
#include "piloteIOTVert.h"

//Definitions privees
//pas de definitions privees

//Declarations de fonctions privees:
//pas de fonctions privees

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
//pas de variables publiques

//Definitions de fonctions publiques:

/**
 * @brief Fonction qui met a 5V la broche \ref PILOTEIOTVERT_BROCHE du microcontrôleur 
 * 
 */
void piloteIOTVert_metAUn(void)
{
  digitalWrite(PILOTEIOTVERT_BROCHE, HIGH);
}
/**
 * @brief Fonction qui met a 0V la broche \ref PILOTEIOTVERT_BROCHE du mirocontrôleur
 * 
 */
void piloteIOTVert_metAZero(void)
{
  digitalWrite(PILOTEIOTVERT_BROCHE, LOW);
}
/**
 * @brief Fonciton qui met la broche \ref PILOTEIOTVERT_BROCHE du mirocontrôleur
 *   au niveau passé en paramètre: 1 ou 0
 * 
 * @param Niveau 
 */
void piloteIOTVert_metA(unsigned char Niveau)
{
  digitalWrite(PILOTEIOTVERT_BROCHE, Niveau);
}
/**
 * @brief Fonction d'initialisation de la broche \ref PILOTEIOTVERT_BROCHE
 *  du mirocontrôleur. Met la broche du microcontrôleur en sortie et assigne
 *  sa valeur initial selon la définition \ref PILOTEIOTVERT_ETAT_INITIAL_A_ZERO
 *  ou \ref PILOTEIOTVERT_ETAT_INITIAL_A_UN.
 * 
 */
void piloteIOTVert_initialise(void)
{
  pinMode(PILOTEIOTVERT_BROCHE,OUTPUT);

#ifdef PILOTEIOTVERT_ETAT_INITIAL_A_UN
	digitalWrite(PILOTEIOTVERT_BROCHE,HIGH);	
#endif

#ifdef PILOTEIOTVERT_ETAT_INITIAL_A_ZERO
	digitalWrite(PILOTEIOTVERT_BROCHE,LOW);
#endif
}

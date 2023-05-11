/**
 * @file piloteIOT14.ino
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
//piloteIOT14:
//Historique: 
// 2021-04-07, Yves Roy, creation

//INCLUSIONS
#include <Arduino.h>
#include "main.h"
#include "piloteIOT14.h"

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
 * @brief Fonction qui met a 5V la broche \ref PILOTEIOT14_BROCHE du microcontrôleur 
 * 
 */
void piloteIOT14_metAUn(void)
{
  digitalWrite(PILOTEIOT14_BROCHE, HIGH);
}
/**
 * @brief Fonction qui met a 0V la broche \ref PILOTEIOT14_BROCHE du mirocontrôleur
 * 
 */
void piloteIOT14_metAZero(void)
{
  digitalWrite(PILOTEIOT14_BROCHE, LOW);
}
/**
 * @brief Fonciton qui met la broche \ref PILOTEIOT14_BROCHE du mirocontrôleur
 *   au niveau passé en paramètre: 14 ou 0
 * 
 * @param Niveau 
 */
void piloteIOT14_metA(unsigned char Niveau)
{
  digitalWrite(PILOTEIOT14_BROCHE, Niveau);
}
/**
 * @brief Fonction d'initialisation de la broche \ref PILOTEIOT14_BROCHE
 *  du mirocontrôleur. Met la broche du microcontrôleur en sortie et assigne
 *  sa valeur initial selon la définition \ref PILOTEIOT14_ETAT_INITIAL_A_ZERO
 *  ou \ref PILOTEIOT14_ETAT_INITIAL_A_UN.
 * 
 */
void piloteIOT14_initialise(void)
{
  pinMode(PILOTEIOT14_BROCHE,OUTPUT);

#ifdef PILOTEIOT14_ETAT_INITIAL_A_UN
	digitalWrite(PILOTEIOT14_BROCHE,HIGH);	
#endif

#ifdef PILOTEIOT14_ETAT_INITIAL_A_ZERO
	digitalWrite(PILOTEIOT14_BROCHE,LOW);
#endif
}

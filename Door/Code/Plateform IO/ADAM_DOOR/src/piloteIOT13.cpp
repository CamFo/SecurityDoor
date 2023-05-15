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
//piloteIOT13:
//Historique: 
// 2021-04-07, Yves Roy, creation

//INCLUSIONS
#include <Arduino.h>
#include "main.h"
#include "piloteIOT13.h"

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
 * @brief Fonction qui met a 5V la broche \ref PILOTEIOT13_BROCHE du microcontrôleur 
 * 
 */
void piloteIOT13_metAUn(void)
{
  digitalWrite(PILOTEIOT13_BROCHE, HIGH);
}
/**
 * @brief Fonction qui met a 0V la broche \ref PILOTEIOT13_BROCHE du mirocontrôleur
 * 
 */
void piloteIOT13_metAZero(void)
{
  digitalWrite(PILOTEIOT13_BROCHE, LOW);
}
/**
 * @brief Fonciton qui met la broche \ref PILOTEIOT13_BROCHE du mirocontrôleur
 *   au niveau passé en paramètre: 1 ou 0
 * 
 * @param Niveau 
 */
void piloteIOT13_metA(unsigned char Niveau)
{
  digitalWrite(PILOTEIOT13_BROCHE, Niveau);
}
/**
 * @brief Fonction d'initialisation de la broche \ref PILOTEIOT13_BROCHE
 *  du mirocontrôleur. Met la broche du microcontrôleur en sortie et assigne
 *  sa valeur initial selon la définition \ref PILOTEIOT13_ETAT_INITIAL_A_ZERO
 *  ou \ref PILOTEIOT13_ETAT_INITIAL_A_UN.
 * 
 */
void piloteIOT13_initialise(void)
{
  pinMode(PILOTEIOT13_BROCHE,OUTPUT);

#ifdef PILOTEIOT13_ETAT_INITIAL_A_UN
	digitalWrite(PILOTEIOT13_BROCHE,HIGH);	
#endif

#ifdef PILOTEIOT13_ETAT_INITIAL_A_ZERO
	digitalWrite(PILOTEIOT13_BROCHE,LOW);
#endif
}

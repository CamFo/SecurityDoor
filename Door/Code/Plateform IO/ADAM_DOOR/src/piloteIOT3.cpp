/**
 * @file piloteIO3.cpp
 * @author Ilyes Gharmoul (ilyesdu2002@hotmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-05-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */
//piloteIOT3:
//Historique: 
// 2021-04-07, Yves Roy, creation

//INCLUSIONS
#include <Arduino.h>
#include "main.h"
#include "piloteIOT3.h"

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
 * @brief Fonction qui met a 5V la broche \ref piloteIOT3_BROCHE du microcontrôleur 
 * 
 */
void piloteIOT3_metAUn(void)
{
  digitalWrite(PILOTEIOT3_BROCHE, HIGH);
}
/**
 * @brief Fonction qui met a 0V la broche \ref piloteIOT3_BROCHE du mirocontrôleur
 * 
 */
void piloteIOT3_metAZero(void)
{
  digitalWrite(PILOTEIOT3_BROCHE, LOW);
}
/**
 * @brief Fonciton qui met la broche \ref piloteIOT3_BROCHE du mirocontrôleur
 *   au niveau passé en paramètre: 1 ou 0
 * 
 * @param Niveau 
 */
void piloteIOT3_metA(unsigned char Niveau)
{
  digitalWrite(PILOTEIOT3_BROCHE, Niveau);
}
/**
 * @brief Fonction d'initialisation de la broche \ref piloteIOT3_BROCHE
 *  du mirocontrôleur. Met la broche du microcontrôleur en sortie et assigne
 *  sa valeur initial selon la définition \ref piloteIOT3_ETAT_INITIAL_A_ZERO
 *  ou \ref piloteIOT3_ETAT_INITIAL_A_UN.
 * 
 */
void piloteIOT3_initialise(void)
{
  pinMode(PILOTEIOT3_BROCHE,OUTPUT);
  
#ifdef PILOTEIO3_ETAT_INPUT
  pinMode(PILOTEIOT3_BROCHE,INPUT);
#endif

#ifdef PILOTEIOT3_ETAT_INITIAL_A_UN
	digitalWrite(PILOTEIOT3_BROCHE,HIGH);	
#endif

#ifdef PILOTEIOT3_ETAT_INITIAL_A_ZERO
	digitalWrite(PILOTEIOT3_BROCHE,LOW);
#endif
}

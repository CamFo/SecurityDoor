/**
 * @file piloteIO1.cpp
 * @author ILyes (ilyesdu2002@hotmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-05-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */
//piloteIOT1:
//Historique: 
// 2021-04-07, Yves Roy, creation

//INCLUSIONS
#include <Arduino.h>
#include "main.h"
#include "piloteIOT1.h"

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
 * @brief Fonction qui met a 5V la broche \ref piloteIOT1_BROCHE du microcontrôleur 
 * 
 */
void piloteIOT1_metAUn(void)
{
  digitalWrite(PILOTEIOT1_BROCHE, HIGH);
}
/**
 * @brief Fonction qui met a 0V la broche \ref piloteIOT1_BROCHE du mirocontrôleur
 * 
 */
void piloteIOT1_metAZero(void)
{
  digitalWrite(PILOTEIOT1_BROCHE, LOW);
}
/**
 * @brief Fonciton qui met la broche \ref piloteIOT1_BROCHE du mirocontrôleur
 *   au niveau passé en paramètre: 1 ou 0
 * 
 * @param Niveau 
 */
void piloteIOT1_metA(unsigned char Niveau)
{
  digitalWrite(PILOTEIOT1_BROCHE, Niveau);
}
/**
 * @brief Fonction d'initialisation de la broche \ref piloteIOT1_BROCHE
 *  du mirocontrôleur. Met la broche du microcontrôleur en sortie et assigne
 *  sa valeur initial selon la définition \ref piloteIOT1_ETAT_INITIAL_A_ZERO
 *  ou \ref piloteIOT1_ETAT_INITIAL_A_UN.
 * 
 */
void piloteIOT1_initialise(void)
{
  pinMode(PILOTEIOT1_BROCHE,OUTPUT);

#ifdef PILOTEIOT1_ETAT_INITIAL_A_UN
	digitalWrite(PILOTEIOT1_BROCHE,HIGH);	
#endif

#ifdef PILOTEIOT1_ETAT_INITIAL_A_ZERO
	digitalWrite(PILOTEIOT1_BROCHE,LOW);
#endif
}

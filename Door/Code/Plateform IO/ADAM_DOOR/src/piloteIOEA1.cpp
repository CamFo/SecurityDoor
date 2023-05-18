/**
 * @file piloteIOEA1.cpp
 * @author Ilyes Gharmoul (ilyesdu2002@hotmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-05-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */
//INCLUSIONS
#include <Arduino.h>
#include "main.h"
#include "piloteIOEA1.h"

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
 * @brief Fonction qui met a 5V la broche \ref piloteIOEA1_BROCHE du microcontrôleur 
 * 
 */
void piloteIOEA1_metAUn(void)
{
  digitalWrite(PILOTEIOEA1_BROCHE, HIGH);
}
/**
 * @brief Fonction qui met a 0V la broche \ref piloteIOEA1_BROCHE du mirocontrôleur
 * 
 */
void piloteIOEA1_metAZero(void)
{
  digitalWrite(PILOTEIOEA1_BROCHE, LOW);
}
/**
 * @brief Fonciton qui met la broche \ref piloteIOEA1_BROCHE du mirocontrôleur
 *   au niveau passé en paramètre: 1 ou 0
 * 
 * @param Niveau 
 */
void piloteIOEA1_metA(unsigned char Niveau)
{
  digitalWrite(PILOTEIOEA1_BROCHE, Niveau);
}
/**
 * @brief Fonction d'initialisation de la broche \ref piloteIOEA1_BROCHE
 *  du mirocontrôleur. Met la broche du microcontrôleur en sortie et assigne
 *  sa valeur initial selon la définition \ref piloteIOEA1_ETAT_INITIAL_A_ZERO
 *  ou \ref piloteIOEA1_ETAT_INITIAL_A_UN.
 * 
 */
void piloteIOEA1_initialise(void)
{
  pinMode(PILOTEIOEA1_BROCHE,OUTPUT);

#ifdef PILOTEIOEA1_ETAT_INITIAL_A_UN
	digitalWrite(PILOTEIOEA1_BROCHE,HIGH);	
#endif

#ifdef PILOTEIOEA1_ETAT_INITIAL_A_ZERO
	digitalWrite(PILOTEIOEA1_BROCHE,LOW);
#endif
}

/**
 * @file piloteIOM1.cpp
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
#include "piloteIOM1.h"

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
 * @brief Fonction qui met a 5V la broche \ref piloteIOM1_BROCHE du microcontrôleur 
 * 
 */
void piloteIOM1_metAUn(void)
{
  digitalWrite(PILOTEIOM1_BROCHE, HIGH);
}
/**
 * @brief Fonction qui met a 0V la broche \ref piloteIOM1_BROCHE du mirocontrôleur
 * 
 */
void piloteIOM1_metAZero(void)
{
  digitalWrite(PILOTEIOM1_BROCHE, LOW);
}
/**
 * @brief Fonciton qui met la broche \ref piloteIOM1_BROCHE du mirocontrôleur
 *   au niveau passé en paramètre: 1 ou 0
 * 
 * @param Niveau 
 */
void piloteIOM1_metA(unsigned char Niveau)
{
  digitalWrite(PILOTEIOM1_BROCHE, Niveau);
}
/**
 * @brief Fonction d'initialisation de la broche \ref piloteIOM1_BROCHE
 *  du mirocontrôleur. Met la broche du microcontrôleur en sortie et assigne
 *  sa valeur initial selon la définition \ref piloteIOM1_ETAT_INITIAL_A_ZERO
 *  ou \ref piloteIOM1_ETAT_INITIAL_A_UN.
 * 
 */
void piloteIOM1_initialise(void)
{
  pinMode(PILOTEIOM1_BROCHE,OUTPUT);

#ifdef PILOTEIOM1_ETAT_INITIAL_A_UN
	digitalWrite(PILOTEIOM1_BROCHE,HIGH);	
#endif

#ifdef PILOTEIOM1_ETAT_INITIAL_A_ZERO
	digitalWrite(PILOTEIOM1_BROCHE,LOW);
#endif
}

/**
 * @file piloteIOM2.cpp
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
#include "piloteIOM2.h"

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
 * @brief Fonction qui met a 5V la broche \ref piloteIOM2_BROCHE du microcontrôleur 
 * 
 */
void piloteIOM2_metAUn(void)
{
  digitalWrite(PILOTEIOM2_BROCHE, HIGH);
}
/**
 * @brief Fonction qui met a 0V la broche \ref piloteIOM2_BROCHE du mirocontrôleur
 * 
 */
void piloteIOM2_metAZero(void)
{
  digitalWrite(PILOTEIOM2_BROCHE, LOW);
}
/**
 * @brief Fonciton qui met la broche \ref piloteIOM2_BROCHE du mirocontrôleur
 *   au niveau passé en paramètre: 1 ou 0
 * 
 * @param Niveau 
 */
void piloteIOM2_metA(unsigned char Niveau)
{
  digitalWrite(PILOTEIOM2_BROCHE, Niveau);
}
/**
 * @brief Fonction d'initialisation de la broche \ref piloteIOM2_BROCHE
 *  du mirocontrôleur. Met la broche du microcontrôleur en sortie et assigne
 *  sa valeur initial selon la définition \ref piloteIOM2_ETAT_INITIAL_A_ZERO
 *  ou \ref piloteIOM2_ETAT_INITIAL_A_UN.
 * 
 */
void piloteIOM2_initialise(void)
{
  pinMode(PILOTEIOM2_BROCHE,OUTPUT);

#ifdef PILOTEIOM2_ETAT_INITIAL_A_UN
	digitalWrite(PILOTEIOM2_BROCHE,HIGH);	
#endif

#ifdef PILOTEIOM2_ETAT_INITIAL_A_ZERO
	digitalWrite(PILOTEIOM2_BROCHE,LOW);
#endif
}

/**
 * @file piloteIOT2.cpp
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
#include "piloteIOT2.h"

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
 * @brief Fonction qui met a 5V la broche \ref PILOTEIOT2_BROCHE du microcontrôleur 
 * 
 */
void piloteIOT2_metAUn(void)
{
  digitalWrite(PILOTEIOT2_BROCHE, HIGH);
}
/**
 * @brief Fonction qui met a 0V la broche \ref PILOTEIOT2_BROCHE du mirocontrôleur
 * 
 */
void piloteIOT2_metAZero(void)
{
  digitalWrite(PILOTEIOT2_BROCHE, LOW);
}
/**
 * @brief Fonciton qui met la broche \ref PILOTEIOT2_BROCHE du mirocontrôleur
 *   au niveau passé en paramètre: 1 ou 0
 * 
 * @param Niveau 
 */
void piloteIOT2_metA(unsigned char Niveau)
{
  digitalWrite(PILOTEIOT2_BROCHE, Niveau);
}
/**
 * @brief Fonction d'initialisation de la broche \ref PILOTEIOT2_BROCHE
 *  du mirocontrôleur. Met la broche du microcontrôleur en sortie et assigne
 *  sa valeur initial selon la définition \ref PILOTEIOT2_ETAT_INITIAL_A_ZERO
 *  ou \ref PILOTEIOT2_ETAT_INITIAL_A_UN.
 * 
 */
void piloteIOT2_initialise(void)
{
  pinMode(PILOTEIOT2_BROCHE,OUTPUT);

#ifdef PILOTEIOT2_ETAT_INITIAL_A_UN
	digitalWrite(PILOTEIOT2_BROCHE,HIGH);	
#endif

#ifdef PILOTEIOT2_ETAT_INITIAL_A_ZERO
	digitalWrite(PILOTEIOT2_BROCHE,LOW);
#endif
}

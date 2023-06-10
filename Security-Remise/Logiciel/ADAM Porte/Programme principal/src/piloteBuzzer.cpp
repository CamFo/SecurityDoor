/**
 * @file piloteBuzzer.cpp
 * @author Ilyes Gharmoul (ilyesdu2002@hotmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-05-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */


//INCLUSIONS
#include <Arduino.h>
#include "main.h"
#include "piloteBuzzer.h"

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
 * @brief Fonction qui met a 5V la broche \ref piloteBuzzer_BROCHE du microcontrôleur 
 * 
 */
void piloteBuzzer_metAUn(void)
{
  digitalWrite(PILOTEBUZZER_BROCHE, HIGH);
}
/**
 * @brief Fonction qui met a 0V la broche \ref piloteBuzzer_BROCHE du mirocontrôleur
 * 
 */
void piloteBuzzer_metAZero(void)
{
  digitalWrite(PILOTEBUZZER_BROCHE, LOW);
}
/**
 * @brief Fonciton qui met la broche \ref piloteBuzzer_BROCHE du mirocontrôleur
 *   au niveau passé en paramètre: 1 ou 0
 * 
 * @param Niveau 
 */
void piloteBuzzer_metA(unsigned char Niveau)
{
  digitalWrite(PILOTEBUZZER_BROCHE, Niveau);
}
/**
 * @brief Fonction d'initialisation de la broche \ref piloteBuzzer_BROCHE
 *  du mirocontrôleur. Met la broche du microcontrôleur en sortie et assigne
 *  sa valeur initial selon la définition \ref piloteBuzzer_ETAT_INITIAL_A_ZERO
 *  ou \ref piloteBuzzer_ETAT_INITIAL_A_UN.
 * 
 */
void piloteBuzzer_initialise(void)
{
  pinMode(PILOTEBUZZER_BROCHE,OUTPUT);

#ifdef PILOTEBUZZER_ETAT_INITIAL_A_UN
	digitalWrite(PILOTEBUZZER_BROCHE,HIGH);	
#endif

#ifdef PILOTEBUZZER_ETAT_INITIAL_A_ZERO
	digitalWrite(PILOTEBUZZER_BROCHE,LOW);
#endif
}

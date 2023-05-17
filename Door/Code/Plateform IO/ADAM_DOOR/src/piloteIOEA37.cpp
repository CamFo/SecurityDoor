
//Historique: 
// 2021-04-07, Yves Roy, creation

//INCLUSIONS
#include <Arduino.h>
#include "main.h"
#include "piloteIOEA37.h"

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
 * @brief Fonction qui met a 5V la broche \ref piloteIOEA37_BROCHE du microcontrôleur 
 * 
 */
void piloteIOEA37_metAUn(void)
{
  digitalWrite(PILOTEIOEA37_BROCHE, HIGH);
}
/**
 * @brief Fonction qui met a 0V la broche \ref piloteIOEA37_BROCHE du mirocontrôleur
 * 
 */
void piloteIOEA37_metAZero(void)
{
  digitalWrite(PILOTEIOEA37_BROCHE, LOW);
}
/**
 * @brief Fonciton qui met la broche \ref piloteIOEA37_BROCHE du mirocontrôleur
 *   au niveau passé en paramètre: 1 ou 0
 * 
 * @param Niveau 
 */
void piloteIOEA37_metA(unsigned char Niveau)
{
  digitalWrite(PILOTEIOEA37_BROCHE, Niveau);
}
/**
 * @brief Fonction d'initialisation de la broche \ref piloteIOEA37_BROCHE
 *  du mirocontrôleur. Met la broche du microcontrôleur en sortie et assigne
 *  sa valeur initial selon la définition \ref piloteIOEA37_ETAT_INITIAL_A_ZERO
 *  ou \ref piloteIOEA37_ETAT_INITIAL_A_UN.
 * 
 */
void piloteIOEA37_initialise(void)
{
  pinMode(PILOTEIOEA37_BROCHE,OUTPUT);

#ifdef PILOTEIOEA37_ETAT_INITIAL_A_UN
	digitalWrite(PILOTEIOEA37_BROCHE,HIGH);	
#endif

#ifdef PILOTEIOEA37_ETAT_INITIAL_A_ZERO
	digitalWrite(PILOTEIOEA37_BROCHE,LOW);
#endif
}

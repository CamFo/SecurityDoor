
//Historique: 
// 2021-04-07, Yves Roy, creation

//INCLUSIONS
#include <Arduino.h>
#include "main.h"
#include "piloteIOC1.h"

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
 * @brief Fonction qui met a 5V la broche \ref piloteIOC1_BROCHE du microcontrôleur 
 * 
 */
void piloteIOC1_metAUn(void)
{
  digitalWrite(PILOTEIOC1_BROCHE, HIGH);
}
/**
 * @brief Fonction qui met a 0V la broche \ref piloteIOC1_BROCHE du mirocontrôleur
 * 
 */
void piloteIOC1_metAZero(void)
{
  digitalWrite(PILOTEIOC1_BROCHE, LOW);
}
/**
 * @brief Fonciton qui met la broche \ref piloteIOC1_BROCHE du mirocontrôleur
 *   au niveau passé en paramètre: 1 ou 0
 * 
 * @param Niveau 
 */
void piloteIOC1_metA(unsigned char Niveau)
{
  digitalWrite(PILOTEIOC1_BROCHE, Niveau);
}
/**
 * @brief Fonction d'initialisation de la broche \ref piloteIOC1_BROCHE
 *  du mirocontrôleur. Met la broche du microcontrôleur en sortie et assigne
 *  sa valeur initial selon la définition \ref piloteIOC1_ETAT_INITIAL_A_ZERO
 *  ou \ref piloteIOC1_ETAT_INITIAL_A_UN.
 * 
 */
void piloteIOC1_initialise(void)
{
  pinMode(PILOTEIOC1_BROCHE,OUTPUT);

#ifdef PILOTEIOC1_ETAT_INITIAL_A_UN
	digitalWrite(PILOTEIOC1_BROCHE,HIGH);	
#endif

#ifdef PILOTEIOC1_ETAT_INITIAL_A_ZERO
	digitalWrite(PILOTEIOC1_BROCHE,LOW);
#endif
}


//Historique: 
// 2021-04-07, Yves Roy, creation

//INCLUSIONS
#include <Arduino.h>
#include "main.h"
#include "piloteIOC24.h"

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
 * @brief Fonction qui met a 5V la broche \ref piloteIOC24_BROCHE du microcontrôleur 
 * 
 */
void piloteIOC24_metAUn(void)
{
  digitalWrite(PILOTEIOC24_BROCHE, HIGH);
}
/**
 * @brief Fonction qui met a 0V la broche \ref piloteIOC24_BROCHE du mirocontrôleur
 * 
 */
void piloteIOC24_metAZero(void)
{
  digitalWrite(PILOTEIOC24_BROCHE, LOW);
}
/**
 * @brief Fonciton qui met la broche \ref piloteIOC24_BROCHE du mirocontrôleur
 *   au niveau passé en paramètre: 1 ou 0
 * 
 * @param Niveau 
 */
void piloteIOC24_metA(unsigned char Niveau)
{
  digitalWrite(PILOTEIOC24_BROCHE, Niveau);
}
/**
 * @brief Fonction d'initialisation de la broche \ref piloteIOC24_BROCHE
 *  du mirocontrôleur. Met la broche du microcontrôleur en sortie et assigne
 *  sa valeur initial selon la définition \ref piloteIOC24_ETAT_INITIAL_A_ZERO
 *  ou \ref piloteIOC24_ETAT_INITIAL_A_UN.
 * 
 */
void piloteIOC24_initialise(void)
{
  pinMode(PILOTEIOC24_BROCHE,OUTPUT);

#ifdef PILOTEIOC24_ETAT_INITIAL_A_UN
	digitalWrite(PILOTEIOC24_BROCHE,HIGH);	
#endif

#ifdef PILOTEIOC24_ETAT_INITIAL_A_ZERO
	digitalWrite(PILOTEIOC24_BROCHE,LOW);
#endif
}

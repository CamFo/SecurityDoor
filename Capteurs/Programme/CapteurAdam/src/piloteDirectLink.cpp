/**
 * @file piloteDirectLink.ino
 * @author CamFo Camille Fortin (camfortin2022@gmail.com)
 * @brief Pilote qui permet la lecture d'une broche d'un microcontrôleur 
 * 
 * @version 0.1
 * @date 2022-11-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//INCLUSIONS
#include <Arduino.h>
#include "main.h"
#include "piloteDirectLink.h"

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

/// @brief Fonction qui permet de savoir l'état logique d'une BROCHE d'un micocontrôleur
/// @param Aucun \ref PILOTEDIRECTLINK_BROCHE est une définition dans \ref xmain.h  
/// @return Valeur de la PIN de 1 ou 0 sur un unsigned char  
unsigned char piloteDirectLink_lit(void)
{
  return digitalRead(PILOTEDIRECTLINK_BROCHE);
}
/// @brief Fonction qui remet a 0 l'entré direct Link
/// @param void 
void piloteDirectLink_Reset(void)
{
	pinMode(PILOTEDIRECTLINK_BROCHE, OUTPUT);
	digitalWrite(PILOTEDIRECTLINK_BROCHE, LOW);
	pinMode(PILOTEDIRECTLINK_BROCHE, INPUT);
}
/// @brief Foncion qui initialise la lecture de la Broche du microcontrôleur
/// @param Aucun \ref PILOTEDIRECTLINK_BROCHE est une définition dans \ref xmain.h  
void piloteDirectLink_initialise(void)
{
#ifdef PILOTEDIRECTLINK_MODE_FLOTTANT_AVEC_PULL_UP
	pinMode(PILOTEDIRECTLINK_BROCHE,INPUT_PULLUP);
#endif

#ifdef PILOTEDIRECTLINK_MODE_FLOTTANT_SANS_PULL_UP
	pinMode(PILOTEDIRECTLINK_BROCHE, INPUT);
#endif
}

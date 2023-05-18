/**
 * @file piloteIOIR1.cpp
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
#include "piloteIOIR1.h"

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
/// @param Aucun \ref PILOTEIOIR1_BROCHE est une définition dans \ref xmain.h  
/// @return Valeur de la PIN de 1 ou 0 sur un unsigned char  
unsigned char piloteIOIR1_lit(void)
{
  return digitalRead(PILOTEIOIR1_BROCHE);
}
/// @brief Foncion qui initialise la lecture de la Broche du microcontrôleur
/// @param Aucun \ref PILOTEIOIR1_BROCHE est une définition dans \ref xmain.h  
void piloteIOIR1_initialise(void)
{
#ifdef PILOTEIOIR1_MODE_FLOTTANT_AVEC_PULL_UP
	pinMode(PILOTEIOIR1_BROCHE,INPUT_PULLUP);
#endif

#ifdef PILOTEIOIR1_MODE_FLOTTANT_SANS_PULL_UP
	pinMode(PILOTEIOIR1_BROCHE);
#endif
}

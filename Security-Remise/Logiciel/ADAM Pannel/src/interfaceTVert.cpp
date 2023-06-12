/**
 * @file interfaceTVert.cpp
 * @author CamFo Camille Fortin (camfortin2022@gmail.com)
 * @brief Interface qui contrôle la del su Board Adafruit ESP32 feather
 * @version 0.1
 * @date 2022-11-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//INCLUSIONS
#include "main.h"
#include "piloteIOTVert.h"
#include "interfaceTVert.h"

//Definitions privees
//pas de definitions privees

//Declarations de fonctions privees:
//pas de fonction privees

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
//pas de variables publiques

//Definitions de fonctions publiques:
void interfaceTVert_allume(void)
{
  piloteIOTVert_metA(INTERFACETVERT_VALEUR_POUR_ALLUMER);
}

void interfaceTVert_eteint(void)
{
  piloteIOTVert_metA(INTERFACETVERT_VALEUR_POUR_ETEINDRE);
}

void interfaceTVert_initialise(void)
{
  piloteIOTVert_metA(INTERFACETVERT_VALEUR_POUR_ETEINDRE);
}

/**
 * @file interfaceMoteur.cpp
 * @author ilyes gharmoul (ilyesdu2002@.com)
 * @brief 
 * @version 0.1
 * @date 2023-05-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <Arduino.h>
#include "main.h"
#include "piloteIOM2.h"
#include "piloteIOM1.h"
#include "piloteIOEA1.h"
#include "interfaceMoteur.h"
#include "serviceBaseDeTemps.h"

//Definitions privees
#define INTERFACEMOTEUR_COMPTE_2S (\
INTERFACEMOTEUR_COMPTE_EN_MS * SERVICEBASEDETEMPS_FREQUENCE_EN_HZ \
  /250.0)

#define INTERFACEMOTEUR_COMPTE_1S (\
INTERFACEMOTEUR_COMPTE_EN_MS * SERVICEBASEDETEMPS_FREQUENCE_EN_HZ \
  /500.0)

#define INTERFACEMOTEUR_COMPTE_500MS (\
INTERFACEMOTEUR_COMPTE_EN_MS * SERVICEBASEDETEMPS_FREQUENCE_EN_HZ \
  /1000.0)


//Declarations de fonctions privees:
//pas de fonction privees

//Definitions de variables privees:
unsigned int interfaceMoteur_compteur;
#define GAUCHE 0
#define DROITE 1
bool oldmode;
//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
//pas de variables publiques
INTERFACEMOTEUR interfaceMoteur;
//Definitions de fonctions publiques:
void interfaceMoteur_Delai1Sec()
{
  piloteIOEA1_metAZero();
  piloteIOM2_metAZero();
  piloteIOM1_metAZero();
  interfaceMoteur_compteur++;
  if (interfaceMoteur_compteur < INTERFACEMOTEUR_COMPTE_1S)
  {
    return;
  }
    interfaceMoteur_compteur = 0;
    serviceBaseDeTemps_execute[INTERFACEMOTEUR_PHASE] = interfaceMoteur_attenteDirective;
}




void interfaceMoteur_attenteDirective()
{
  if (interfaceMoteur.RequeteActive == INTERFACEMOTEUR_INACTIVE)
  return;
  if (interfaceMoteur.direction == interfaceMoteur.RequeteDirection)
  return;

  if (interfaceMoteur.direction == INTERFACEMOTEUR_DIRECTION_DROITE)
  serviceBaseDeTemps_execute[INTERFACEMOTEUR_PHASE] = interfaceMoteur_droite;
  else if(interfaceMoteur.direction == INTERFACEMOTEUR_DIRECTION_GAUCHE)
  serviceBaseDeTemps_execute[INTERFACEMOTEUR_PHASE] = interfaceMoteur_gauche;
}
void interfaceMoteur_droite()
{
  interfaceMoteur.RequeteDirection = INTERFACEMOTEUR_DIRECTION_DROITE;
  piloteIOEA1_metAUn();
  piloteIOM2_metAUn();
  piloteIOM1_metAZero();
  interfaceMoteur_compteur++;
  if (interfaceMoteur_compteur < interfaceMoteur.dureeActive)
  {
    return;
  }
  interfaceMoteur_compteur = 0;
  interfaceMoteur.dureeActive = INTERFACEMOTEUR_DUREE_NONDEFINIE;
  interfaceMoteur.RequeteActive = INTERFACEMOTEUR_INACTIVE;
  serviceBaseDeTemps_execute[INTERFACEMOTEUR_PHASE] = interfaceMoteur_Delai1Sec;

}
void interfaceMoteur_gauche()
{
  interfaceMoteur.RequeteDirection = INTERFACEMOTEUR_DIRECTION_GAUCHE;
  piloteIOEA1_metAUn();
  piloteIOM2_metAZero();
  piloteIOM1_metAUn();
  interfaceMoteur_compteur++;
  if (interfaceMoteur_compteur < interfaceMoteur.dureeActive)
  {
    return;
  }
  interfaceMoteur_compteur = 0;
  interfaceMoteur.dureeActive = INTERFACEMOTEUR_DUREE_NONDEFINIE;
  interfaceMoteur.RequeteActive = INTERFACEMOTEUR_INACTIVE;
  serviceBaseDeTemps_execute[INTERFACEMOTEUR_PHASE] = interfaceMoteur_Delai1Sec;
}
void interfaceMoteur_initalise()
{
  interfaceMoteur.dureeActive = INTERFACEMOTEUR_DUREE_NONDEFINIE;
  interfaceMoteur.direction = INTERFACEMOTEUR_DIRECTION_UNDEFINED;
  interfaceMoteur.RequeteDirection = INTERFACEMOTEUR_DIRECTION_UNDEFINED;
  interfaceMoteur.RequeteActive = INTERFACEMOTEUR_INACTIVE;
  interfaceMoteur.etatDuModule = INTERFACEMOTEUR_MODULE_PAS_EN_FONCTION;
  serviceBaseDeTemps_execute[INTERFACEMOTEUR_PHASE] = interfaceMoteur_attenteDirective;
}
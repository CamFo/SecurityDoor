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
#include "piloteIOC24.h"
#include "piloteIOC26.h"
#include "piloteIOT13.h"
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
  piloteIOC24_metAZero();
  piloteIOC26_metAZero();
  interfaceMoteur_compteur++;
  if (interfaceMoteur_compteur < INTERFACEMOTEUR_COMPTE_1S)
  {
    return;
  }
    interfaceMoteur_compteur = 0;
    if (oldmode != GAUCHE)
    serviceBaseDeTemps_execute[INTERFACEMOTEUR_PHASE] = interfaceMoteur_gauche;
    else 
    serviceBaseDeTemps_execute[INTERFACEMOTEUR_PHASE] = interfaceMoteur_droite;
}

void interfaceMoteur_droite()
{
    #ifdef MODEDEBUG
    piloteIOT13_metAZero();
    #endif
  if (interfaceMoteur.RequeteActive == INTERFACEMOTEUR_INACTIVE)
  return;
  //piloteIOEA37_metAUn();
  piloteIOC24_metAUn();
  piloteIOC26_metAZero();
  interfaceMoteur_compteur++;
  if (interfaceMoteur_compteur < INTERFACEMOTEUR_COMPTE_2S)
  {
    return;
  }
  interfaceMoteur_compteur = 0;
  oldmode = DROITE;
  interfaceMoteur.RequeteActive = INTERFACEMOTEUR_INACTIVE;
  serviceBaseDeTemps_execute[INTERFACEMOTEUR_PHASE] = interfaceMoteur_Delai1Sec;

}
void interfaceMoteur_gauche()
{
    #ifdef MODEDEBUG
    piloteIOT13_metAUn();
    #endif
  if (interfaceMoteur.RequeteActive = INTERFACEMOTEUR_INACTIVE)
  return;
 // piloteIOEA37_metAUn();
  piloteIOC24_metAZero();
  piloteIOC26_metAUn();
  interfaceMoteur_compteur++;
  if (interfaceMoteur_compteur < INTERFACEMOTEUR_COMPTE_2S)
  {
    return;
  }
  interfaceMoteur_compteur = 0;
  oldmode = GAUCHE;
  serviceBaseDeTemps_execute[INTERFACEMOTEUR_PHASE] = interfaceMoteur_Delai1Sec;

}
void interfaceMoteur_initalise()
{
        #ifdef MODEDEBUG
    piloteIOT13_metAUn();
    #endif
    interfaceMoteur.RequeteActive = INTERFACEMOTEUR_INACTIVE;
    interfaceMoteur.etatDuModule = INTERFACEMOTEUR_MODULE_PAS_EN_FONCTION;
    interfaceMoteur.information = INTERFACEMOTEUR_INFORMATION_TRAITEE;
    serviceBaseDeTemps_execute[INTERFACEMOTEUR_PHASE] = interfaceMoteur_droite;
}
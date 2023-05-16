/**
 * @file processusClignotant.cpp
 * @author Camille Fortin (camfortin2022@gmail.com)
 * @brief Processus décrit dans processusclignotant.h
 * @version 0.1
 * @date 2023-05-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */


//INCLUSIONS
#include "main.h"
#include "interfaceT1.h"

#include "serviceBaseDeTemps.h"
#include "processusClignotant.h"
#include "piloteESPNOWCapteur.h"
#include <stdio.h>

//Definitions privees
#define PROCESSUSCLIGNOTANT_COMPTE_POUR_ALLUME (\
  PROCESSUSCLIGNOTANT_TEMPS_ALLUME_EN_MS * SERVICEBASEDETEMPS_FREQUENCE_EN_HZ \
  /1000.0)

#define PROCESSUSCLIGNOTANT_COMPTE_POUR_ETEINDRE  (\
  PROCESSUSCLIGNOTANT_TEMPS_ETEINT_EN_MS * SERVICEBASEDETEMPS_FREQUENCE_EN_HZ \
  /1000.0)
   
//Declarations de fonctions privees:
//pas de fonction privees

//Definitions de variables privees:
unsigned long processusClignotant_compteur;

//Definitions de fonctions privees:
void processusClignotant_attendAvantDAllumerLeTemoinLumineux(void);
void processusClignotant_attendAvantDEteindreLeTemoinLumineux(void);

//Definitions de variables publiques:
//pas de variables publiques

//Definitions de fonctions publiques:
void processusClignotant_attendAvantDAllumerLeTemoinLumineux(void)
{
  processusClignotant_compteur++;
  if (processusClignotant_compteur < PROCESSUSCLIGNOTANT_COMPTE_POUR_ALLUME)
  {
    return;
  }
  // Test Code Go here  
  
  ValueEnvoieCapteur.States = 0x08;
  ValueEnvoieCapteur.Commande = 0x45;
  ValueEnvoieCapteur.ValeurA = false;
  ValueEnvoieCapteur.ValeurB = false;
  ValueEnvoieCapteur.ValeurC = false;

  piloteESPNOW_send();
  
  // END test Code 
  interfaceT1_allume();
  processusClignotant_compteur = 0;
  serviceBaseDeTemps_execute[PROCESSUSCLIGNOTANT_PHASE] = processusClignotant_attendAvantDEteindreLeTemoinLumineux;
}

void processusClignotant_attendAvantDEteindreLeTemoinLumineux(void)
{ 
  processusClignotant_compteur++;
  if (processusClignotant_compteur < PROCESSUSCLIGNOTANT_COMPTE_POUR_ETEINDRE)
  {
    return;
  }

  interfaceT1_eteint();
  processusClignotant_compteur = 0;
  serviceBaseDeTemps_execute[PROCESSUSCLIGNOTANT_PHASE] = processusClignotant_attendAvantDAllumerLeTemoinLumineux;
}

void processusClignotant_initialise(void)
{
  processusClignotant_compteur = 0;
  interfaceT1_eteint();
  serviceBaseDeTemps_execute[PROCESSUSCLIGNOTANT_PHASE] = processusClignotant_attendAvantDAllumerLeTemoinLumineux;
}

/**
 * @file processusGestionPairing.cpp
 * @author Ilyes Gharmoul (ilyesdu2002@hotmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-05-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <Arduino.h>
#include "main.h"
#include "AnnexeADAM.h"
#include "piloteBuzzer.h"
#include "piloteESPNOW.h"
#include "piloteIOM1.h"
#include "piloteIOM2.h"
#include "piloteIOT1.h"
#include "piloteIOT2.h"
#include "piloteIOT3.h"
#include "piloteIOIR1.h"
#include "piloteIOIR2.h"
#include "interfaceBuzzer.h"
#include "interfaceMoteur.h"
#include "interfaceRGB.h"
#include "interfaceInfrarouge.h"
#include "serviceBaseDeTemps.h"
#include "ServiceCommunication.h"
#include "processusGestionPairing.h"

#include <stdio.h>

//Definitions privees
#define PROCESSUSPOURGESTIONPAIRING_COMPTE_30S (\
PROCESSUSPOURGESTIONPAIRING_COMPTE_EN_MS * SERVICEBASEDETEMPS_FREQUENCE_EN_HZ \
  /16.66)

#define PROCESSUSPOURGESTIONPAIRING_COMPTE_1S (\
PROCESSUSPOURGESTIONPAIRING_COMPTE_EN_MS * SERVICEBASEDETEMPS_FREQUENCE_EN_HZ \
  /500.0)
#define PROCESSUSPOURGESTIONPAIRING_COMPTE_2S (\
PROCESSUSPOURGESTIONPAIRING_COMPTE_EN_MS * SERVICEBASEDETEMPS_FREQUENCE_EN_HZ \
  /250.0)
#define PROCESSUSPOURGESTIONPAIRING_COMPTE_10S (\
PROCESSUSPOURGESTIONPAIRING_COMPTE_EN_MS * SERVICEBASEDETEMPS_FREQUENCE_EN_HZ \
  /50.0)

//Declarations de fonctions privees:
void processusGestionPairing_attemptPairing_indicators();
void processusGestionPairing_comState();
void processusGestionPairing_VerifieIfStillPaired();
void processusGestionPairing_ReAttemptPairing();
void loop3();
//Definitions de variables privees:
unsigned int processusGestionPairing_compteur;
unsigned int processusGestionPairing_compteur2;
unsigned char processusGestionPairing_PairedState;
//Definitions de fonctions privees:



//Definitions de variables publiques:
//pas de variables publiques

//Definitions de fonctions publiques:


void loop3()
{

}
void processusGestionPairing_VerifieIfStillPaired()
{
  if(GestionCommuncation_R.ADAM_recu.porte_ADAM_receive.States <= SERVICECOMMUNCATIIONR_STATE_ERREUR)
  {
    #ifdef MODE_DEBUG_PGP
    Serial.printf("\n ERREUR STATE :");
    Serial.print(GestionCommuncation_R.ADAM_recu.porte_ADAM_receive.States);
    #endif
    serviceBaseDeTemps_execute[PROCESSUSGESTIONPAIRING_PHASE] = processusGestionPairing_ReAttemptPairing;
  }
  
}
void processusGestionPairing_ReAttemptPairing()
{
  if(GestionCommuncation_R.ADAM_recu.porte_ADAM_receive.States > SERVICECOMMUNCATIIONR_STATE_ERREUR)
  {
      #ifdef MODE_DEBUG_PGP
      Serial.print("\n Pair success.");
      #endif
      serviceBaseDeTemps_execute[PROCESSUSGESTIONPAIRING_PHASE] = processusGestionPairing_VerifieIfStillPaired;
      return;
  }
  processusGestionPairing_compteur++;
  if (processusGestionPairing_compteur < PROCESSUSPOURGESTIONPAIRING_COMPTE_2S)
    return;
  #ifdef MODE_DEBUG_PGP
  Serial.print("\n Fail to repair, trying again in Parallel.");
  #endif
  processusGestionPairing_compteur = 0;
}


void processusGestionPairing_comState()
{
  if(GestionCommuncation_R.ADAM_recu.porte_ADAM_receive.States > SERVICECOMMUNCATIIONR_STATE_ERREUR)
  {
      interfaceRGB.couleur = INTERFACERGB_VALEUR_BLEU;
      interfaceRGB.RequeteActive = INTERFACERGB_ACTIVE;
      interfaceRGB.dureeActive = PROCESSUSPOURGESTIONPAIRING_COMPTE_2S;
      interfaceBuzzer.dureeActive = PROCESSUSPOURGESTIONPAIRING_COMPTE_1S;
      interfaceBuzzer.valeurBruit = INTERFACEBUZZER_25POURCENT;
      interfaceBuzzer.RequeteActive = INTERFACEBUZZER_ACTIVE;
      #ifdef MODE_DEBUG_PGP
      Serial.print("\n Pair success.");
      #endif
      processusGestionPairing_compteur = 0;
      processusGestionPairing_PairedState = PROCESSUSGGESTIONPAIRING_FINISHEDPAIRING;
      serviceBaseDeTemps_execute[PROCESSUSGESTIONPAIRING_PHASE] = processusGestionPairing_VerifieIfStillPaired;
      return;
  }
  processusGestionPairing_compteur++;
  if (processusGestionPairing_compteur < PROCESSUSPOURGESTIONPAIRING_COMPTE_30S)
  return;
  processusGestionPairing_PairedState = PROCESSUSGGESTIONPAIRING_FINISHEDPAIRING;
  interfaceRGB.couleur = INTERFACERGB_VALEUR_MAUVE;
  interfaceRGB.RequeteActive = INTERFACERGB_ACTIVE;
  interfaceRGB.dureeActive = PROCESSUSPOURGESTIONPAIRING_COMPTE_2S;
  #ifdef MODE_DEBUG_PGP
  Serial.printf("\n Failed com.");
  Serial.printf("\n Normal mode. Communicating in parallel.");
  #endif
  processusGestionPairing_compteur = 0;
  serviceBaseDeTemps_execute[PROCESSUSGESTIONPAIRING_PHASE] = processusGestionPairing_ReAttemptPairing;
}

void processusGestionPairing_attemptPairing_indicators()
{

  interfaceRGB.couleur = INTERFACERGB_VALEUR_JAUNE;
  interfaceRGB.RequeteActive = INTERFACERGB_ACTIVE;
  interfaceRGB.dureeActive = PROCESSUSPOURGESTIONPAIRING_COMPTE_2S;
  #ifdef MODE_DEBUG_PGP
  Serial.print("\r Attempting pairing.");
  #endif
  serviceBaseDeTemps_execute[PROCESSUSGESTIONPAIRING_PHASE] = processusGestionPairing_comState;
}
void processusGestionPairing_initialise()
{
  processusGestionPairing_PairedState = PROCESSUSGGESTIONPAIRING_ATTEMPTPAIRING;
  serviceBaseDeTemps_execute[PROCESSUSGESTIONPAIRING_PHASE] = processusGestionPairing_attemptPairing_indicators;
 //processusGestionPairing_Detection_init;
}



/**
 * @file processusVerifieSerrure.cpp
 * @author Ilyes Gharmoul (ilyesdu2002@hotmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-05-19
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
#include "processusVerifieSerrure.h"

#include <stdio.h>

//Definitions privees

#define PROCESSUSVERIFIESERRURE_COMPTE_2S (\
PROCESSUSVERIFIESERRURE_COMPTE_EN_MS * SERVICEBASEDETEMPS_FREQUENCE_EN_HZ \
  /250.0)

#define PROCESSUSVERIFIESERRURE_COMPTE_1S (\
PROCESSUSVERIFIESERRURE_COMPTE_EN_MS * SERVICEBASEDETEMPS_FREQUENCE_EN_HZ \
  /500.0)

#define PROCESSUSVERIFIESERRURE_COMPTE_500MS (\
PROCESSUSVERIFIESERRURE_COMPTE_EN_MS * SERVICEBASEDETEMPS_FREQUENCE_EN_HZ \
  /1000.0)

//Declarations de fonctions privees:
void processusVerifieSerrure_Detection();
void processusVerifieSerrure_DetecteOuvert();
void processusVerifieSerrure_DetecteFermer();
//Definitions de variables privees:
unsigned int processusVerifieSerrure_compteur;
unsigned int processusVerifieSerrure_oldstatedoor;
//Definitions de fonctions privees:

void processusVerifieSerrure_Detection()
{
  interfaceInfrarouge.RequeteActive = INTERFACEINFRAROUGE_ACTIVE;
  if (interfaceInfrarouge.presence == INTERFACEINFRAROUGE_PRESENCE_PRESENT)
  {
    if (interfaceInfrarouge.presence == GestionCommuncation_T.ADAM_send.porte_ADAM_send.EtatPorte)
    return;   
    serviceBaseDeTemps_execute[PROCESSUSVERIFIESERRURE_PHASE] = processusVerifieSerrure_DetecteOuvert;
  }
  else if (interfaceInfrarouge.presence == INTERFACEINFRAROUGE_PRESENCE_NON_PRESENT)
  {
    if (interfaceInfrarouge.presence == GestionCommuncation_T.ADAM_send.porte_ADAM_send.EtatPorte)
    return;
    serviceBaseDeTemps_execute[PROCESSUSVERIFIESERRURE_PHASE] = processusVerifieSerrure_DetecteFermer;
  } 
}

void processusVerifieSerrure_DetecteOuvert()
{
  #ifdef MODE_DEBUG_VERIFIESERRURE
  Serial.print("Ouvert");
  #endif
  GestionCommuncation_T.ADAM_send.porte_ADAM_send.EtatPorte = PROCESSUSVERIFIESERRURE_DETECTE_OUVERT;  
  interfaceRGB.couleur = INTERFACERGB_VALEUR_VERT;
  interfaceRGB.dureeActive = PROCESSUSVERIFIESERRURE_COMPTE_2S;
  interfaceRGB.RequeteActive = INTERFACERGB_ACTIVE;
  interfaceBuzzer.dureeActive = PROCESSUSVERIFIESERRURE_COMPTE_2S;
  interfaceBuzzer.valeurBruit = INTERFACEBUZZER_100POURCENT;
  interfaceBuzzer.RequeteActive =INTERFACEBUZZER_ACTIVE;
  serviceBaseDeTemps_execute[PROCESSUSVERIFIESERRURE_PHASE] = processusVerifieSerrure_Detection;
}
void processusVerifieSerrure_DetecteFermer()
{
  #ifdef MODE_DEBUG_VERIFIESERRURE
  Serial.print("Fermer");
  #endif
  GestionCommuncation_T.ADAM_send.porte_ADAM_send.EtatPorte = PROCESSUSVERIFIESERRURE_DETECTE_FERMER;
  interfaceRGB.couleur = INTERFACERGB_VALEUR_ROUGE;
  interfaceRGB.dureeActive = PROCESSUSVERIFIESERRURE_COMPTE_2S;
  interfaceRGB.RequeteActive = INTERFACERGB_ACTIVE;
  interfaceBuzzer.dureeActive = PROCESSUSVERIFIESERRURE_COMPTE_2S;
  interfaceBuzzer.valeurBruit = INTERFACEBUZZER_75POURCENT;
  interfaceBuzzer.RequeteActive =INTERFACEBUZZER_ACTIVE;
  serviceBaseDeTemps_execute[PROCESSUSVERIFIESERRURE_PHASE] = processusVerifieSerrure_Detection;
}
//Definitions de variables publiques:
//pas de variables publiques

//Definitions de fonctions publiques:


void processusVerifieSerrure_initialise()
{
  serviceBaseDeTemps_execute[PROCESSUSVERIFIESERRURE_PHASE] = processusVerifieSerrure_Detection;
}



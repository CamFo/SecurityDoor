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
void processusGestionPairing_Detection();
void processusGestionPairing_VerifieIfStillPaired();
void processusGestionPairing_ReAttemptPairing();
//Definitions de variables privees:
unsigned int processusGestionPairing_compteur;
//Definitions de fonctions privees:
void processusGestionPairing_VerifieIfStillPaired()
{

}
void processusGestionPairing_ReAttemptPairing()
{
    if (processusGestionPairing_compteur < PROCESSUSPOURGESTIONPAIRING_COMPTE_30S)
    {
        processusGestionPairing_compteur++;
        if(GestionCommuncation_R.ADAM_recu.porte_ADAM_receive.States > SERVICECOMMUNICATION_FAILVALUE)
        {
            processusGestionPairing_compteur = 0;
            //interfaceBuzzer.dureeActive = PROCESSUSPOURGESTIONPAIRING_COMPTE_1S;
            //interfaceBuzzer.valeurBruit = INTERFACEINFRAROUGE_25POURCENT;
            Serial.print("\n Pair success.");
            serviceBaseDeTemps_execute[PROCESSUSGESTIONPAIRING_PHASE] = processusGestionPairing_VerifieIfStillPaired;
        }
        return;
    }
    serviceBaseDeTemps_execute[PROCESSUSGESTIONPAIRING_PHASE] = processusGestionPairing_ReAttemptPairing;
}

int processusGestionPairing_compteur2;
void processusGestionPairing_Detection_init()
{
    bool initPrint;
    if (initPrint == 0)
    {
      Serial.print("\r Attempting pairing.");
      interfaceRGB.couleur = INTERFACERGB_VALEUR_JAUNE;
      interfaceRGB.RequeteActive = INTERFACERGB_ACTIVE;
      initPrint = 1;
    }

    if (processusGestionPairing_compteur < PROCESSUSPOURGESTIONPAIRING_COMPTE_30S)
    {
        processusGestionPairing_compteur++;

        if (processusGestionPairing_compteur2 > PROCESSUSPOURGESTIONPAIRING_COMPTE_2S)
        {
          Serial.print(".");
          processusGestionPairing_compteur2 = 0;
        }
        else
        processusGestionPairing_compteur2++;

        if(GestionCommuncation_R.ADAM_recu.porte_ADAM_receive.States > SERVICECOMMUNICATION_FAILVALUE)
        {
            Serial.print("\n Pair success.");
            processusGestionPairing_compteur = 0;
            interfaceBuzzer.dureeActive = PROCESSUSPOURGESTIONPAIRING_COMPTE_1S;
            interfaceBuzzer.valeurBruit = INTERFACEBUZZER_25POURCENT;
            interfaceRGB.couleur = INTERFACERGB_VALEUR_BLEU;
            interfaceRGB.RequeteActive = INTERFACERGB_ACTIVE;
            serviceBaseDeTemps_execute[PROCESSUSGESTIONPAIRING_PHASE] = processusGestionPairing_VerifieIfStillPaired;
        }
        return;
    }
    Serial.print("\n Failed com.");
    interfaceRGB.couleur = INTERFACERGB_VALEUR_ROUGE;
    interfaceRGB.RequeteActive = INTERFACERGB_ACTIVE;
    if (processusGestionPairing_compteur < PROCESSUSPOURGESTIONPAIRING_COMPTE_2S)
    {
        return;
    }
    processusGestionPairing_compteur = 0;
    processusGestionPairing_compteur2 = 0;
    serviceBaseDeTemps_execute[PROCESSUSGESTIONPAIRING_PHASE] = processusGestionPairing_ReAttemptPairing;
}
//Definitions de variables publiques:
//pas de variables publiques

//Definitions de fonctions publiques:

void loop3();
void loop3(){}

void processusGestionPairing_initialise()
{
  serviceBaseDeTemps_execute[PROCESSUSGESTIONPAIRING_PHASE] = processusGestionPairing_Detection_init;//processusGestionPairing_Detection_init;
}



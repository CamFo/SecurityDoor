/**
 * @file processusPourTest.cpp
 * @author Ilyes Gharmoul (ilyesdu2002@hotmail.com)
 * @brief 
 * @version 0.6
 * @date 2023-04-27
 * 
 * @copyright Copyright (c) 2023
 * 
 */

//INCLUSIONS
#include <Arduino.h>
#include "main.h"
#include "piloteI2C.h"
#include "piloteIOM2.h"
#include "piloteIOM1.h"
#include "piloteIOEA1.h"
#include "piloteIOT1.h"
#include "piloteIOT2.h"
#include "piloteIOT3.h"
#include "piloteBuzzer.h"
#include "piloteIOIR1.h"
#include "piloteIOIR2.h"
#include "piloteESPNOW.h"
#include "interfaceRGB.h"
#include "interfacePN523.h"
#include "interfaceBuzzer.h"
#include "interfaceMoteur.h"
#include "interfaceInfrarouge.h"
#include "processusPourTest.h"
#include "serviceBaseDeTemps.h"
#include "ServiceCommunication.h"

#include <stdio.h>

//Definitions privees

#define PROCESSUSPOURTEST_COMPTE_2S (\
PROCESSUSPOURTEST_COMPTE_EN_MS * SERVICEBASEDETEMPS_FREQUENCE_EN_HZ \
  /250.0)

#define PROCESSUSPOURTEST_COMPTE_1S (\
PROCESSUSPOURTEST_COMPTE_EN_MS * SERVICEBASEDETEMPS_FREQUENCE_EN_HZ \
  /500.0)

#define PROCESSUSPOURTEST_COMPTE_500MS (\
PROCESSUSPOURTEST_COMPTE_EN_MS * SERVICEBASEDETEMPS_FREQUENCE_EN_HZ \
  /1000.0)

//Declarations de fonctions privees:
//pas de fonction privees
void processusDeTest_I2C_Delai1Sec();
void processusDeTest_RGB_Delai1Sec();
void processusDeTest_TestI2C();
void processusDeTest_TestRGB();
void processusDeTest_GPIO14_en_input();
void processusDeTest_Buzzer();
void processusDeTest_Buzzer_Delai1Sec();
void processusDeTest_Infrarrouge_VerifieEntree();
void processusDeTest_salutCamille8D();
//Definitions de variables privees:
unsigned int processusDeTest_compteur;
int icount;
//Definitions de fonctions privees:

//Definitions de variables publiques:
//pas de variables publiques

//Definitions de fonctions publiques:



void processusDeTest_I2C_Delai1Sec()
{
  processusDeTest_compteur++;
  if (processusDeTest_compteur < PROCESSUSPOURTEST_COMPTE_2S)
  {
    return;
  }
    processusDeTest_compteur = 0;
    serviceBaseDeTemps_execute[PROCESSUSTESTS_PHASE] = processusDeTest_TestI2C;
}

void processusDeTest_TestI2C()
{
    interfacePN523_VerifierPresenceNFC();
    serviceBaseDeTemps_execute[PROCESSUSTESTS_PHASE] = processusDeTest_I2C_Delai1Sec;
}

void processusDeTest_Moteur()
{
  interfaceMoteur.RequeteActive = INTERFACEMOTEUR_ACTIVE;
  interfaceRGB.RequeteActive = INTERFACERGB_ACTIVE;
  interfaceBuzzer.RequeteActive = INTERFACEBUZZER_ACTIVE;
  interfaceBuzzer.dureeActive = PROCESSUSPOURTEST_COMPTE_2S;
  interfaceBuzzer.valeurBruit = INTERFACEBUZZER_100POURCENT;
  interfaceRGB.couleur = INTERFACERGB_VALEUR_BLANC;

  processusDeTest_compteur++;
  if (processusDeTest_compteur < PROCESSUSPOURTEST_COMPTE_2S)
  {
    return;
  }
  if (interfaceMoteur.direction == INTERFACEMOTEUR_DIRECTION_DROITE)
  interfaceMoteur.direction = INTERFACEMOTEUR_DIRECTION_GAUCHE;
  else
  interfaceMoteur.direction = INTERFACEMOTEUR_DIRECTION_DROITE;


}

void processusDeTest_TestRGB()
{ 
  interfaceRGB.RequeteActive = INTERFACERGB_ACTIVE;
  interfaceRGB.couleur = icount;
  icount++;
  if (icount >= INTERFACERGB_MAXSTATE)
  icount = INTERFACERGB_VALEUR_ROUGE;
  serviceBaseDeTemps_execute[PROCESSUSTESTS_PHASE] = processusDeTest_RGB_Delai1Sec;
}

void processusDeTest_RGB_Delai1Sec()
{
  processusDeTest_compteur++;
  if (processusDeTest_compteur < PROCESSUSPOURTEST_COMPTE_2S)
  {
    return;
  }
    processusDeTest_compteur = 0;
    serviceBaseDeTemps_execute[PROCESSUSTESTS_PHASE] = processusDeTest_TestRGB;
}


void processusDeTest_Buzzer()
{
 interfaceBuzzer.RequeteActive = INTERFACEBUZZER_ACTIVE;
 interfaceBuzzer.dureeActive = PROCESSUSPOURTEST_COMPTE_2S;
 interfaceBuzzer.valeurBruit = icount;
 if (interfaceBuzzer.etatDuModule == INTERFACEBUZZER_MODULE_PAS_EN_FONCTION);
 icount++;
 //Serial.printf("%d",icount);
 if (icount >= INTERFACEBUZZER_MAXSTATE)
 icount = INTERFACEBUZZER_AUCUNBRUIT;
 serviceBaseDeTemps_execute[PROCESSUSTESTS_PHASE] = processusDeTest_Buzzer_Delai1Sec;
}
void processusDeTest_salutCamille8D()
{
  GestionCommuncation_T.ADAM_send.porte_ADAM_send.Commande = 3;
  Serial.printf("\n porte_Adam_send.commande value: ");
  Serial.print(GestionCommuncation_T.ADAM_send.porte_ADAM_send.Commande);
  Serial.printf("\n piloteValueEnvoi.commande value: ");
  Serial.print(GestionCommuncation_T.piloteValueEnvoie.Commande);
}


void processusDeTest_Buzzer_Delai1Sec()
{
  processusDeTest_compteur++;
  if (processusDeTest_compteur < PROCESSUSPOURTEST_COMPTE_2S)
  {
    return;
  }
    processusDeTest_compteur = 0;
    serviceBaseDeTemps_execute[PROCESSUSTESTS_PHASE] = processusDeTest_Buzzer;
}

void processusDeTest_Infrarrouge_VerifieEntree()
{
 interfaceBuzzer.dureeActive = PROCESSUSPOURTEST_COMPTE_2S;
 interfaceBuzzer.valeurBruit = INTERFACEBUZZER_25POURCENT;
 interfaceInfrarouge.RequeteActive = INTERFACEINFRAROUGE_ACTIVE;
 if (interfaceInfrarouge.presence == INTERFACEINFRAROUGE_PRESENCE_PRESENT)
 interfaceBuzzer.RequeteActive = INTERFACEBUZZER_ACTIVE;
 else
 interfaceBuzzer.RequeteActive = INTERFACEBUZZER_INACTIVE;
}
void processusDeTest_initialise(void)
{
 // Serial.begin(115200);
 // Serial.setDebugOutput(TRUE);
  serviceBaseDeTemps_execute[PROCESSUSTESTS_PHASE] = nefaitrien; //Quel test faire
}

void nefaitrien();
void nefaitrien()
{
  
}
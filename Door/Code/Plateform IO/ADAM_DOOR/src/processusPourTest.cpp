//processusClignotant:
//Historique: 
// 2023-05-03, Camille Fortin

//INCLUSIONS
#include <Arduino.h>
#include "main.h"
#include "piloteI2C.h"
#include "piloteIOC24.h"
#include "piloteIOT16.h"
#include "piloteIOT13.h"
#include "piloteIOT14.h"
#include "interfaceRGB.h"
#include "interfacePN523.h"
#include "serviceBaseDeTemps.h"
#include "processusPourTest.h"
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

//Definitions de variables privees:
unsigned int processusDeTest_compteur;
//Definitions de fonctions privees:

//Definitions de variables publiques:
//pas de variables publiques

//Definitions de fonctions publiques:
int icount;
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

void processusDeTest_TestRGB()
{ 
  icount++;
  if (icount >= INTERFACERGB_MAXSTATE)
  icount = INTERFACERGB_VALEUR_ROUGE;
  interfaceRGB_allumeCouleur(icount);
  serviceBaseDeTemps_execute[PROCESSUSTESTS_PHASE] = processusDeTest_RGB_Delai1Sec;
}

void processusDeTest_GPIO14_en_input()
{
 if (digitalRead(PILOTEIOT14_BROCHE))
 {
  interfaceRGB_allumeCouleur(INTERFACERGB_VALEUR_VERT);
 }
  else
 {
  interfaceRGB_allumeCouleur(INTERFACERGB_VALEUR_ROUGE);
 }
}

void processusDeTest_initialise(void)
{
  Serial.begin(115200);
  Serial.setDebugOutput(TRUE);
  serviceBaseDeTemps_execute[PROCESSUSTESTS_PHASE] = processusDeTest_GPIO14_en_input; //Quel test faire
}

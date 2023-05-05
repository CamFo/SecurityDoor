//processusClignotant:
//Historique: 
// 2023-05-03, Camille Fortin

//INCLUSIONS
#include <Arduino.h>
#include "main.h"
#include "piloteI2C.h"
#include "interfacePN523.h"
#include "serviceBaseDeTemps.h"
#include "processusPourTest.h"
#include <stdio.h>

//Definitions privees
#define PROCESSUSPOURTEST_COMPTE_1S (\
PROCESSUSPOURTEST_COMPTE_EN_MS * SERVICEBASEDETEMPS_FREQUENCE_EN_HZ \
  /500.0)

//Declarations de fonctions privees:
//pas de fonction privees

//Definitions de variables privees:
unsigned int processusDeTest_compteur;
//Definitions de fonctions privees:

//Definitions de variables publiques:
//pas de variables publiques

//Definitions de fonctions publiques:

void processusDeTest_Delai1Sec()
{
  processusDeTest_compteur++;
  if (processusDeTest_compteur < PROCESSUSPOURTEST_COMPTE_1S)
  {
    return;
  }
    processusDeTest_compteur = 0;
    serviceBaseDeTemps_execute[PROCESSUSTESTS_PHASE] = processusDeTest_TestI2C;
}
/**
 * @brief 
 * 
 */
void processusDeTest_TestI2C()
{ 
  interfacePN523_VerifierPresenceNFC();
  serviceBaseDeTemps_execute[PROCESSUSTESTS_PHASE] = processusDeTest_Delai1Sec;
}

void processusDeTest_initialise(void)
{
  Serial.begin(115200);
  Serial.setDebugOutput(TRUE);
  piloteI2C1_initialise();
  serviceBaseDeTemps_execute[PROCESSUSTESTS_PHASE] = processusDeTest_TestI2C;
}

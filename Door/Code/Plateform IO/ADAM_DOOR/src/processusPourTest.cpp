//processusClignotant:
//Historique: 
// 2023-05-03, Camille Fortin

//INCLUSIONS
#include <Arduino.h>
#include "main.h"
#include "piloteI2C.h"

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

void processusDeTest_TestI2C()
{ 
  uint8_t error = piloteI2C1_appelAuChip(I2C_ADR_NFC,TRUE);
  Serial.printf("endTransmission: %u\n", error);

  uint8_t bytesReceived = piloteI2C1_lisUnEntier(I2C_ADR_NFC);
  Serial.printf("requestFrom: %u\n", bytesReceived);

  if((bool)bytesReceived)
  { //If received more than zero bytes
    uint8_t temp[bytesReceived];
    //I2C1.readBytes(temp, bytesReceived);
    log_print_buf(temp, bytesReceived);
  }

  serviceBaseDeTemps_execute[PROCESSUSTESTS_PHASE] = processusDeTest_Delai1Sec;
}

void processusDeTest_initialise(void)
{
  Serial.begin(115200);
  Serial.setDebugOutput(TRUE);
  piloteI2C1_initialise();
  serviceBaseDeTemps_execute[PROCESSUSTESTS_PHASE] = processusDeTest_TestI2C;
}

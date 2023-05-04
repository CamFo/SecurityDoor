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
//Declarations de fonctions privees:
//pas de fonction privees

//Definitions de variables privees:

//Definitions de fonctions privees:

//Definitions de variables publiques:
//pas de variables publiques

//Definitions de fonctions publiques:
void processusDeTest_TestI2C(void)
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

  serviceBaseDeTemps_execute[PROCESSUSTESTS_PHASE] = processusDeTest_TestI2C;
}

void processusDeTest_initialise(void)
{
  Serial.begin(115200);
  Serial.setDebugOutput(TRUE);
  piloteI2C1_initialise();
  serviceBaseDeTemps_execute[PROCESSUSTESTS_PHASE] = processusDeTest_TestI2C;
}

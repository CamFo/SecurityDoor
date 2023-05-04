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

  serviceBaseDeTemps_execute[PROCESSUSCLIGNOTANT_PHASE] = processusDeTest_TestI2C;
}

void processusDeTest_initialise(void)
{
  serviceBaseDeTemps_execute[PROCESSUSCLIGNOTANT_PHASE] = processusDeTest_TestI2C;
}

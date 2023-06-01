//#############################################################################
/**
 * @file main.c
 * @author CamFo Camille Fortin (camfortin2022@gmail.com)
 * @brief
 * Program file containing the code defined in xmain.h
 * Please refer to this other file for information necessary in order to make this work.
 * @version 0.1
 * @date 2022-11-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */
//#############################################################################


//INCLUSIONS
#include <Arduino.h>
#include "main.h"

// inlcude des pilotes
#include "piloteEntree1.h"
#include "piloteIOT1.h"
#include "piloteIOTVert.h"
#include "piloteEntreeDL.h"
#include "piloteSerinPYQ.h"

// Include des Services
#include "serviceTaskServer.h"
#include "serviceBaseDeTemps.h"
#include "serviceCommunication.h"

// Inlude des interfaces
#include "interfaceEntree1.h"
#include "interfaceT1.h"
#include "interfaceTVert.h"
#include "interfaceSHT4X.h"
#include "interfaceMotion.h"

// Include des processus
#include "processusClignotant.h"

//Definitions privees
void main_faitUnTest(void);
void coreTask( void * parameter );
//pas de definitions privees


//Declarations de fonctions privees:

/// @brief Fonction qui permet de tester certain module en activant 
//      leur requête tout de suite après leur initialisation
/// @param void
void main_faitUnTest(void)
{
  
}
/// @brief Fonction qui fait l'initialisation de tout les modules permettant
//   au fonctionnement global du véhicule.
/// @param void
void main_initialise(void);

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
void coreTask( void * parameter )
{
  Serial.print("\nLong Tasks running on core ");
  Serial.println(xPortGetCoreID());
  while(true)
  {
    delay(10);
    serviceBaseDeTemps_gereDansLoop();
  }
}

void main_initialise(void)
{
  serviceTaskServer_initialise();
  serviceBaseDeTemps_initialise();
  serviceCommunication_initialise();

  piloteEntree1_initialise();
  piloteIOT1_initialise(); 
  piloteIOTVert_initialise();
  piloteEntreeDL_initialise();
  piloteSerinPYQ_initialise();

  interfaceEntree1_initialise();
  interfaceT1_initialise();
  interfaceTVert_initialise();
  interfaceSHT4X_initialise();
  interfaceMotion_initialise();
  
  processusClignotant_initialise();
}

void setup(void) 
{
  Serial.begin(115200);
  main_initialise();
  main_faitUnTest();
  xTaskCreatePinnedToCore(coreTask, "TaskLong", 10000, NULL, 1, NULL, 0);
  serviceTaskServer_DemarreLesTachesALaTouteFinDeSetup();
}

void loop(void) 
{
  serviceTaskServer_gestion.execute();
}

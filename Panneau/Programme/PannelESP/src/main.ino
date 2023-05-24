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
#include "piloteESPNOWCapteur.h"
#include "piloteLCD.h"

// Include des Services
#include "serviceTaskServer.h"
#include "serviceBaseDeTemps.h"
#include "serviceCommunication.h"

// Inlude des interfaces
#include "interfaceEntree1.h"
#include "interfaceT1.h"
#include "interfaceTVert.h"
#include "interfaceTactile.h"
#include "interfaceLCD.h"

// Include des processus
#include "processusClignotant.h"

//Definitions privees

INTERFACELCD interfaceLCD;  // Pour passer les information à afficher à chaue Module

//pas de definitions privees

/// @brief Fonction qui permet de tester certain module en activant 
//      leur requête tout de suite après leur initialisation
/// @param void
void main_faitUnTest(void);
/// @brief Fonction qui fait l'initialisation de tout les modules permettant
//   au fonctionnement global du véhicule.
/// @param void
void main_initialise(void);

void TaskWiFicode( void * parameter);

/// @brief Fonction qui permet de faire des state machine sur un autre Core
/// @param parameter 
void TaskWiFicode( void * parameter)  
{
  Serial.print("\nTaskWiFi running on core ");
  Serial.println(xPortGetCoreID());
  while(true)
  {
    delay(10);
    serviceBaseDeTemps_gereDansLoop();
  }
}


//Declarations de fonctions privees:
void main_faitUnTest(void)
{
}

void main_initialise(void)
{
  serviceTaskServer_initialise();
  serviceBaseDeTemps_initialise();
  serviceCommunication_initialise();  //Base de temps n'as pas de bug sans la COM
  piloteEntree1_initialise();
  piloteIOT1_initialise(); 
  piloteIOTVert_initialise();
  piloteLCD_initialise();

  interfaceEntree1_initialise();
  interfaceT1_initialise();
  interfaceTVert_initialise();
  //interfaceTactile_initialise();
  interfaceLCD_initialise();
  
  processusClignotant_initialise();
}

void setup(void) 
{
  Serial.begin(115200); 
  main_initialise();
  main_faitUnTest();
  serviceTaskServer_DemarreLesTachesALaTouteFinDeSetup();
  xTaskCreatePinnedToCore(TaskWiFicode, "TaskWiFi", 10000, NULL, 1, NULL,  0);
  delay(500);
}

void loop(void) 
{
  serviceTaskServer_gestion.execute();
}

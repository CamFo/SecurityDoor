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
#include "main.h"

// inlcude des pilotes

#include "piloteIOT14.h"
#include "piloteIOT13.h"
#include "piloteIOT16.h"

#include "piloteIOC24.h"
#include "piloteIOC26.h"
#include "piloteIOEA37.h"
#include "piloteI2C.h"

// Include des Services
#include "serviceTaskServer.h"
#include "serviceBaseDeTemps.h"

// Inlude des interfaces
#include "interfaceRGB.h"
#include "interfacePN523.h"
#include "interfaceMoteur.h"
// Include des processus
#include "processusPourTest.h"

//Definitions privees
//pas de definitions privees
void main_faitUnTest(void);

//Declarations de fonctions privees:

/// @brief Fonction qui permet de tester certain module en activant 
//      leur requête tout de suite après leur initialisation
/// @param void
void main_faitUnTest(void)
{
 //
}
/// @brief Fonction qui fait l'initialisation de tout les modules permettant
//   au fonctionnement global du véhicule.
/// @param void
void main_initialise(void);

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:

void main_initialise(void)
{
  
  serviceTaskServer_initialise();
  serviceBaseDeTemps_initialise();
  piloteI2C1_initialise();
  piloteIOT14_initialise(); 
  piloteIOT13_initialise();
  piloteIOT16_initialise();
  piloteIOC24_initialise();
  piloteIOC26_initialise();
  interfaceRGB_initialise();
  interfacePN523_initalise();
  interfaceMoteur_initalise();
  processusDeTest_initialise();
}

void setup(void) 
{
  Serial.begin(115200);
  Serial.setDebugOutput(TRUE);
  main_initialise();
  main_faitUnTest();
  serviceTaskServer_DemarreLesTachesALaTouteFinDeSetup();
}

void loop(void) 
{
  serviceTaskServer_gestion.execute();
  serviceBaseDeTemps_gereDansLoop(); 
}

//Definitions de variables publiques:
//pas de variables publiques

//Definitions de fonctions publiques:
//pas de fonctions publiques

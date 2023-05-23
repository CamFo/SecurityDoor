/**
 * @file main.ino
 * @author Ilyes Gharmoul (ilyesdu2002@hotmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-05-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */


//INCLUSIONS
#include "main.h"
// inlcude des pilotes

#include "piloteIOT3.h"
#include "piloteIOT2.h"
#include "piloteIOT1.h"
#include "piloteIOIR1.h"
#include "piloteIOIR2.h"
#include "piloteESPNOW.h"
//#include "Adafruit_PN532.h"

#include "piloteIOM2.h"
#include "piloteIOM1.h"
#include "piloteIOEA1.h"

#include "piloteBuzzer.h"
#include "piloteI2C.h"

// Include des Services
#include "serviceTaskServer.h"
#include "serviceBaseDeTemps.h"
#include "ServiceCommunication.h"
// Inlude des interfaces
#include "interfaceRGB.h"
#include "interfacePN523.h"
#include "interfaceMoteur.h"
#include "interfaceBuzzer.h"
#include "interfaceInfrarouge.h"
// Include des processus
#include "Adafruit_PN532.h"
#include "processusPourTest.h"
#include "processusVerifieOuverture.h"
#include "processusGestionIndicateurs.h"
#include "processusGestionPairing.h"
#include "processusControlMoteur.h"

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
  piloteI2C1_initialise();
  piloteIOT3_initialise(); 
  piloteIOT2_initialise();
  piloteIOT1_initialise();
  piloteIOM2_initialise();
  piloteIOM1_initialise();
  piloteBuzzer_initialise();
  piloteIOIR1_initialise();
  piloteIOIR2_initialise();
  piloteESPNOW_initialise();
  serviceTaskServer_initialise();
  serviceBaseDeTemps_initialise();
  serviceCommunication_initialise();
  interfaceRGB_initialise();
  interfacePN523_initalise();
  interfaceMoteur_initalise();
  interfaceBuzzer_initalise();
  interfaceInfrarouge_initalise();
  processusDeTest_initialise();
  //processusVerifieOuverture_initialise();
  //processusGestionIndicateurs_initialise();
  //processusGestionPairing_initialise();
  //processusControlMoteur_initialise();
  Serial.print("init successfull.\n");
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

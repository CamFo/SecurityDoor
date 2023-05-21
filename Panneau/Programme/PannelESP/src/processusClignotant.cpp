/**
 * @file processusClignotant.cpp
 * @author Camille Fortin (camfortin2022@gmail.com)
 * @brief Processus décrit dans processusclignotant.h
 * @version 0.1
 * @date 2023-05-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */


//INCLUSIONS
#include "main.h"
#include "interfaceT1.h"

#include "serviceBaseDeTemps.h"
#include "processusClignotant.h"
#include "piloteESPNOWCapteur.h"
#include "FT6236.h"

#include <stdio.h>

//Definitions privees
#define PROCESSUSCLIGNOTANT_COMPTE_POUR_ALLUME (\
  PROCESSUSCLIGNOTANT_TEMPS_ALLUME_EN_MS * SERVICEBASEDETEMPS_FREQUENCE_EN_HZ \
  /1000.0)

#define PROCESSUSCLIGNOTANT_COMPTE_POUR_ETEINDRE  (\
  PROCESSUSCLIGNOTANT_TEMPS_ETEINT_EN_MS * SERVICEBASEDETEMPS_FREQUENCE_EN_HZ \
  /1000.0)
   
//Declarations de fonctions privees:
//pas de fonction privees

//Definitions de variables privees:
FT6236 ts = FT6236();

unsigned long processusClignotant_compteur;

//Definitions de fonctions privees:
void processusClignotant_attendAvantDAllumerLeTemoinLumineux(void);
void processusClignotant_attendAvantDEteindreLeTemoinLumineux(void);

//Definitions de variables publiques:
//pas de variables publiques

//Definitions de fonctions publiques:
void processusClignotant_attendAvantDAllumerLeTemoinLumineux(void)
{
  processusClignotant_compteur++;
  if (processusClignotant_compteur < PROCESSUSCLIGNOTANT_COMPTE_POUR_ALLUME)
  {
    return;
  }
  ////// BEGIN Test Code  //////
  
  
  if (ts.touched())
    {
        // Retrieve a point
        TS_Point p = ts.getPoint();

        // Print coordinates to the serial output
        Serial.print("X Coordinate: ");
        Serial.println(p.x);
        Serial.print("Y Coordinate: ");
        Serial.println(p.y);
    }
  

  ////// END Test Code //////
  interfaceT1_allume();
  processusClignotant_compteur = 0;
  serviceBaseDeTemps_execute[PROCESSUSCLIGNOTANT_PHASE] = processusClignotant_attendAvantDEteindreLeTemoinLumineux;
}

void processusClignotant_attendAvantDEteindreLeTemoinLumineux(void)
{ 
  processusClignotant_compteur++;
  if (processusClignotant_compteur < PROCESSUSCLIGNOTANT_COMPTE_POUR_ETEINDRE)
  {
    return;
  }

  interfaceT1_eteint();
  processusClignotant_compteur = 0;
  serviceBaseDeTemps_execute[PROCESSUSCLIGNOTANT_PHASE] = processusClignotant_attendAvantDAllumerLeTemoinLumineux;
}

void processusClignotant_initialise(void)
{
  processusClignotant_compteur = 0;
  interfaceT1_eteint();
  // TEST CODE INIT
  
  ts.begin(40, PILOTEI2C1_SDA, PILOTEI2C1_SCL);

  // END TEST CODE 
  serviceBaseDeTemps_execute[PROCESSUSCLIGNOTANT_PHASE] = processusClignotant_attendAvantDAllumerLeTemoinLumineux;
}

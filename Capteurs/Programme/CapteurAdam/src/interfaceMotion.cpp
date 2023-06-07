/**
 * @file interfaceMotion.cpp
 * @author Camille Fortin 
 * @brief Interface qui permet de lire et de débouncer la switch
 * @version 0.1
 * @date 2023-05-03
 * 
 * @copyright Copyright (c) 2023
 * 
 */

//INCLUSIONS
#include <Arduino.h>
#include "main.h"
#include "piloteDirectLink.h"
#include "serviceBaseDeTemps.h"
#include "interfaceMotion.h"
#include "interfaceT1.h"


//Definitions privees
#define INTERFACEMOTION_COMPTE_MAXIMUM_AVANT_LECTURE  (\
  SERVICEBASEDETEMPS_FREQUENCE_EN_HZ/INTERFACEMOTION_FREQUENCE_DES_LECTURES_EN_HZ)
  
#define INTERFACEMOTION_COMPTE_INITIAL (\
  INTERFACEMOTION_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION/2)

//Declarations de fonctions privees:
void interfaceMotion_gere(void);

//Definitions de variables privees:
unsigned int interfaceMotion_compteurAvantLecture;
unsigned int comptLed;

//Definitions de fonctions privees:
void interfaceMotion_gere(void)
{
  comptLed++;
  if(comptLed >= 1000)
  {
    interfaceT1_eteint();
  }
  interfaceMotion_compteurAvantLecture++;
  if (interfaceMotion_compteurAvantLecture < INTERFACEMOTION_COMPTE_MAXIMUM_AVANT_LECTURE)
  {
    return;
  }
  interfaceMotion_compteurAvantLecture = 0;
  if (piloteDirectLink_lit() == INTERFACEMOTION_VALEUR_LUE_SI_ACTIVE)
  {
    interfaceT1_allume();
    comptLed = 0;
    Serial.println("MOTIONNNN");
    interfaceMotion.etatDuModule = INTERFACEMOTION_MODULE_EN_FONCTION;
    interfaceMotion.etatDeLEntree = INTERFACEMOTION_ACTIVE;
    interfaceMotion.information = INTERFACEMOTION_INFORMATION_DISPONIBLE;
    piloteDirectLink_Reset();  
    return;
  }
  if (interfaceMotion.etatDeLEntree == INTERFACEMOTION_INACTIVE)
  {
    return;
  }
  interfaceMotion.etatDuModule = INTERFACEMOTION_MODULE_EN_FONCTION;  
  interfaceMotion.etatDeLEntree = INTERFACEMOTION_INACTIVE;
  interfaceMotion.information = INTERFACEMOTION_INFORMATION_DISPONIBLE;
}

//Definitions de variables publiques:
INTERFACEMOTION interfaceMotion;

//Definitions de fonctions publiques:
void interfaceMotion_initialise(void)
{
  interfaceT1_eteint();
  interfaceMotion.etatDuModule = INTERFACEMOTION_MODULE_PAS_EN_FONCTION;
  interfaceMotion.information = INTERFACEMOTION_INFORMATION_TRAITEE;
  interfaceMotion.etatDeLEntree = INTERFACEMOTION_PAS_EN_FONCTION;
	interfaceMotion_compteurAvantLecture = 0;
  serviceBaseDeTemps_execute[INTERFACEMOTION_PHASE] = interfaceMotion_gere;
}

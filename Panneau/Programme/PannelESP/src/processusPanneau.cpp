/**
 * @file processusPanneau.cpp
 * @author Camille Fortin (camfortin2022@gmail.com)
 * @brief Processus décrit dans processusPanneau.h
 * @version 0.1
 * @date 2023-05-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */


//INCLUSIONS
#include <Arduino.h>

#include "main.h"
#include "piloteESPNOWCapteur.h"
#include "piloteESPNOWDoor.h"
#include "serviceBaseDeTemps.h"
#include "ServiceCommunication.h"
#include "processusPanneau.h"
#include "processusAffichage.h"

//Definitions privees
PROCESSUSPANNEAU processusPanneau;
   
//Declarations de fonctions privees:
//pas de fonction privees
void processusPanneau_attendReponsesModules(void);
void processusPanneau_attendArmement(void);
void processusPanneau_attendFinArmement(void);

//Definitions de variables privees:

unsigned long processusPanneau_compteur;
unsigned int comptArmement;

//Definitions de fonctions privees:
void processusPanneau_attendReponsesModules(void)
{
  if(ValeurRecuCapteur.States != SERVICECOMMUNICATION_STATE_OPERATION)
  {
    return;
  }  
  if(ValeurRecuDoor.States != SERVICECOMMUNICATION_STATE_OPERATION)
  {
    return;
  }

  serviceBaseDeTemps_execute[PROCESSUSPANNEAU_PHASE] = processusPanneau_attendArmement;
}
void processusPanneau_attendArmement(void)
{
  if(processusPanneau.requete != PROCESSUSPANNEAU_REQUETE_ACTIVE)
  {
    return;
  }
  processusPanneau.requete = PROCESSUSPANNEAU_REQUETE_TRAITEE;



}

void processusPanneau_attendFinArmement(void)
{
  comptArmement ++;
  if(comptArmement <= 200)
  {
    return;  
  }
  /*
  processusAffichage.compteurArm --;
  processusAffichage.chiffreAffichee = true;
  comptArmement = 0; 
  */

}


//Definitions de variables publiques:
//pas de variables publiques

//Definitions de fonctions publiques:

void processusPanneau_initialise(void)
{
  processusPanneau_compteur = 0;

  serviceBaseDeTemps_execute[PROCESSUSPANNEAU_PHASE] = processusPanneau_attendReponsesModules;
}

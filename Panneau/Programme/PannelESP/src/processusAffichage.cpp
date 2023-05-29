/**
 * @file processusAffichage.cpp
 * @author Camille Fortin (camfortin2022@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-05-29
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <Arduino.h>
#include "main.h"
#include "serviceBaseDeTemps.h"
#include "interfaceLCD.h"
#include "interfaceTactile.h"
#include "processusAffichage.h"

//Définition de variable privée
bool bouttonBarreOldState;
bool bouttonDebarreOldState;

extern INTERFACETACTILE interfaceTactile;

//Définition de fonction privée
void processusAffichage_gere(void);



void processusAffichage_initialise(void)
{
  
  serviceBaseDeTemps_executeDansLoop[PROCESSUSAFFICHAGE_PHASE] = processusAffichage_gere;
}


void processusAffichage_gere(void)
{
  if(interfaceTactile.etatBouttonBarre == true) // Si le boutton barré est pesé
  {
    if(bouttonBarreOldState == false)
    {
        interfaceLCD_boutton(20, 85, 100, 70, false, DarkRed, 0xA000, 0x7000);
        bouttonBarreOldState = true;
    }
  }
  else
  {
    if(bouttonBarreOldState == true)
    {
        interfaceLCD_boutton(20, 85, 100, 70, false, DarkRed, 0x7000, 0xA000);
        bouttonBarreOldState = false; 
    }
  }
  if(interfaceTactile.etatBouttonDebarre == true) // Si le boutton Débarré est pesé
  {
    if(bouttonDebarreOldState == false)
    {
       interfaceLCD_boutton(140, 85, 100, 70, false, DarkGreen, 0x04E0, 0x02A0);
       bouttonDebarreOldState = true;
    }
  }
  else
  {
    if(bouttonDebarreOldState == true)
    {
       interfaceLCD_boutton(140, 85, 100, 70, false, DarkGreen, 0x02A0, 0x4E0);
       bouttonDebarreOldState = false;
    }
  }
}

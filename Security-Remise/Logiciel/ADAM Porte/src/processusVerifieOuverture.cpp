/**
 * @file processusVerifieOuverture.cpp
 * @author Ilyes Gharmoul (ilyesdu2002@hotmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-05-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <Arduino.h>
#include "main.h"
#include "AnnexeADAM.h"
#include "piloteBuzzer.h"
#include "piloteESPNOW.h"
#include "piloteIOM1.h"
#include "piloteIOM2.h"
#include "piloteIOT1.h"
#include "piloteIOT2.h"
#include "piloteIOT3.h"
#include "piloteIOIR1.h"
#include "piloteIOIR2.h"
#include "interfaceBuzzer.h"
#include "interfaceMoteur.h"
#include "interfaceRGB.h"
#include "interfaceInfrarouge.h"
#include "serviceBaseDeTemps.h"
#include "ServiceCommunication.h"
#include "processusVerifieOuverture.h"

#include <stdio.h>
#define PROCESSUSVERIFIEOUVERTURE_COMPTE_2S (\
PROCESSUSVERIFIEOUVERTURE_COMPTE_EN_MS * SERVICEBASEDETEMPS_FREQUENCE_EN_HZ \
  /250.0)

int processusGestionIndicateur_compteur;
void processusVerifieOuverture_gestionBuzzer();

void processusVerifieOuverture_gestionBuzzer()
{

}

void processusVerifieOuverture_VerifieState()
{

}
void loop2();
void loop2()
{

}
void processusVerifieOuverture_initialise()
{
    serviceBaseDeTemps_execute[PROCESSUSVERIFIEOUVERTURE_PHASE] = loop2;
}

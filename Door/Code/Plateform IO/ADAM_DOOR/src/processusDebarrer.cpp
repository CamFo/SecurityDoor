/**
 * @file processusDebarrer.cpp
 * @author Ilyes Gharmoul (ilyesdu2002@hotmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-05-19
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
#include "processusDebarrer.h"

#include <stdio.h>

//Definitions privees

#define PROCESSUSDEBARRER_COMPTE_2S (\
PROCESSUSDEBARRER_COMPTE_EN_MS * SERVICEBASEDETEMPS_FREQUENCE_EN_HZ \
  /250.0)

#define PROCESSUSDEBARRER_COMPTE_1S (\
PROCESSUSDEBARRER_COMPTE_EN_MS * SERVICEBASEDETEMPS_FREQUENCE_EN_HZ \
  /500.0)

#define PROCESSUSDEBARRER_COMPTE_500MS (\
PROCESSUSDEBARRER_COMPTE_EN_MS * SERVICEBASEDETEMPS_FREQUENCE_EN_HZ \
  /1000.0)

//Declarations de fonctions privees:
void processusDebarrer_GestionMethode();
//Definitions de variables privees:
unsigned int processusDebarrer_compteur;
//Definitions de fonctions privees:

void processusDebarrer_GestionMethode()
{

}
//Definitions de variables publiques:
//pas de variables publiques

//Definitions de fonctions publiques:


void processusDebarrer_initialise()
{   
    serviceBaseDeTemps_execute[PROCESSUSDEBARRER_PHASE] = processusDebarrer_GestionMethode;
}



/**
 * @file processusGestionIndicateurs.cpp
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
#include "processusGestionIndicateurs.h"

#include <stdio.h>
#define PROCESSUSGESTIONINIDCATEUR_COMPTE_2S (\
PROCESSUSGESTIONINIDCATEUR_COMPTE_EN_MS * SERVICEBASEDETEMPS_FREQUENCE_EN_HZ \
  /250.0)

int processusGestionIndicateur_compteur;
void processusGestionIndicateurs_gestionBuzzer();

void processusGestionIndicateurs_gestionBuzzer()
{
 //GestionCommuncation_R.ADAM_recu.porte_ADAM_receive.ValueRA = 1;
 Serial.print("processusGestionIndicateurs_gestionBuzzer a bien init");
}

void processusGestionIndicateurs_VerifieState()
{

}
void loop2();
void loop2()
{

}
void processusGestionIndicateurs_initialise()
{
    serviceBaseDeTemps_execute[PROCESSUSGESTIONINDICATEURS_PHASE] = loop2;
}

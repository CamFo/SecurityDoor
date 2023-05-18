/**
 * @file interfaceInfrarouge.cpp
 * @author Ilyes Gharmoul (ilyesdu2002@hotmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-05-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <Arduino.h>
#include "main.h"
#include "piloteIOIR1.h"
#include "piloteIOIR2.h"
#include "interfaceRGB.h"
#include "interfaceInfrarouge.h"
#include "serviceBaseDeTemps.h"
#include "ServiceCommunication.h"

INTERFACEINFRAROUGE interfaceInfrarouge;
unsigned int interfaceInfrarouge_compte;

void interfaceInfrarouge_attenteDirective();
void interfaceInfrarouge_activeTransmetteur();
void interfaceInfrarouge_LectureInfrarouge();

void interfaceInfrarouge_LectureInfrarouge()
{

}
void interfaceInfrarouge_activeTransmetteur()
{
    interfaceInfrarouge.etatDuModuleTransmetteur = INTERFACEINFRAROUGE_MODULE_EN_FONCTION;
    piloteIOIR2_metAUn();
    serviceBaseDeTemps_execute[INTERFACEINFRAROUGE_PHASE] = interfaceInfrarouge_LectureInfrarouge;
}

void interfaceInfrarouge_attenteDirective()
{
    piloteIOIR2_metAZero();
    if (interfaceInfrarouge.RequeteActive == INTERFACEINFRAROUGE_INACTIVE)
    return;
    serviceBaseDeTemps_execute[INTERFACEINFRAROUGE_PHASE] = interfaceInfrarouge_activeTransmetteur;

}

void interfaceInfrarouge_initalise()
{
    interfaceInfrarouge.etatDuModuleTransmetteur = INTERFACEINFRAROUGE_PAS_EN_FONCTION;
    interfaceInfrarouge.etatDuModuleRecepteur = INTERFACEINFRAROUGE_PAS_EN_FONCTION;
    interfaceInfrarouge.RequeteActive = INTERFACEINFRAROUGE_INACTIVE;
    serviceBaseDeTemps_execute[INTERFACEINFRAROUGE_PHASE] = interfaceInfrarouge_attenteDirective;
}
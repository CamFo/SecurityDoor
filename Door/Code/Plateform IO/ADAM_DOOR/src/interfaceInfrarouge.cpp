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
#include "interfaceInfrarouge.h"
#include "serviceBaseDeTemps.h"
#include "ServiceCommunication.h"


#define INTERFACEINFRAROUGE_COMPTE_2S (\
INTERFACEINFRAROUGE_COMPTE_EN_MS * SERVICEBASEDETEMPS_FREQUENCE_EN_HZ \
  /500.0)


INTERFACEINFRAROUGE interfaceInfrarouge;
unsigned int interfaceInfrarouge_compteur;
double interfaceInfrarouge_StoreCompteur;
void interfaceInfrarouge_attenteDirective();
void interfaceInfrarouge_activeTransmetteur();
void interfaceInfrarouge_LectureInfrarouge();
void interfaceInfrarouge_VerifiePresence();

void interfaceInfrarouge_LectureInfrarouge()
{
    interfaceInfrarouge.etatDuModuleRecepteur = INTERFACEINFRAROUGE_MODULE_EN_FONCTION;
    if (piloteIOIR1_lis())
    {
    interfaceInfrarouge_StoreCompteur++;
    }
    interfaceInfrarouge_compteur++;
    if (interfaceInfrarouge_compteur < INTERFACEINFRAROUGE_COMPTE_2S)
    return;
    interfaceInfrarouge_compteur = 0;
    interfaceInfrarouge.etatDuModuleRecepteur = INTERFACEINFRAROUGE_MODULE_PAS_EN_FONCTION;
    interfaceInfrarouge.etatDuModuleTransmetteur = INTERFACEINFRAROUGE_MODULE_PAS_EN_FONCTION;
    serviceBaseDeTemps_execute[INTERFACEINFRAROUGE_PHASE] = interfaceInfrarouge_VerifiePresence;
}
void interfaceInfrarouge_VerifiePresence()
{
    interfaceInfrarouge.valeurDistance = map((long)interfaceInfrarouge_StoreCompteur,0,INTERFACEINFRAROUGE_COMPTE_2S,0,100);
    #ifdef MODE_DEBUG_INTERFACEIR
    Serial.print(interfaceInfrarouge.valeurDistance);
    Serial.printf("    '%' de detection\n");
    #endif
    if (interfaceInfrarouge.valeurDistance < INTERFACEINFRAROUGE_VERIFIEPRESENCE)
    interfaceInfrarouge.presence = INTERFACEINFRAROUGE_PRESENCE_NON_PRESENT;
    else
    interfaceInfrarouge.presence = INTERFACEINFRAROUGE_PRESENCE_PRESENT;


    interfaceInfrarouge_StoreCompteur = 0;
    interfaceInfrarouge.etatDesModules = INTERFACEINFRAROUGE_MODULE_PAS_EN_FONCTION;
    interfaceInfrarouge.RequeteActive = INTERFACEINFRAROUGE_INACTIVE;
    serviceBaseDeTemps_execute[INTERFACEINFRAROUGE_PHASE] = interfaceInfrarouge_attenteDirective;
}
void interfaceInfrarouge_activeTransmetteur()
{
    interfaceInfrarouge.etatDuModuleTransmetteur = INTERFACEINFRAROUGE_MODULE_EN_FONCTION;
    //piloteIOIR2_metAUn();
    piloteIOIR2_PWM_AUn();
    serviceBaseDeTemps_execute[INTERFACEINFRAROUGE_PHASE] = interfaceInfrarouge_LectureInfrarouge;
}

void interfaceInfrarouge_attenteDirective()
{
    interfaceInfrarouge.etatDuModuleRecepteur = INTERFACEINFRAROUGE_MODULE_PAS_EN_FONCTION;
    interfaceInfrarouge.etatDuModuleTransmetteur = INTERFACEINFRAROUGE_MODULE_PAS_EN_FONCTION;
    interfaceInfrarouge.etatDesModules = INTERFACEINFRAROUGE_MODULE_PAS_EN_FONCTION;
    if (interfaceInfrarouge.RequeteActive == INTERFACEINFRAROUGE_INACTIVE)
    {
        //piloteIOIR2_metAZero();
        piloteIOIR2_PWM_AZero();
        return;
    }
    interfaceInfrarouge.etatDesModules = INTERFACEINFRAROUGE_MODULE_EN_FONCTION;
    serviceBaseDeTemps_execute[INTERFACEINFRAROUGE_PHASE] = interfaceInfrarouge_activeTransmetteur;
}

void interfaceInfrarouge_initalise()
{
    interfaceInfrarouge.etatDuModuleTransmetteur = INTERFACEINFRAROUGE_MODULE_PAS_EN_FONCTION;
    interfaceInfrarouge.etatDuModuleRecepteur = INTERFACEINFRAROUGE_MODULE_PAS_EN_FONCTION;
    interfaceInfrarouge.etatDesModules = INTERFACEINFRAROUGE_MODULE_PAS_EN_FONCTION;
    interfaceInfrarouge.RequeteActive = INTERFACEINFRAROUGE_INACTIVE;
    serviceBaseDeTemps_execute[INTERFACEINFRAROUGE_PHASE] = interfaceInfrarouge_attenteDirective;
}
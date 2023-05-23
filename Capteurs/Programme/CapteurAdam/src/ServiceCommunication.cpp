//#############################################################################
/**
 * @file ServiceESP-NOW.cpp
 * @author Camille Fortin (camfortin2022@gmail.com)
 * @brief
 * Program file containing the code defined in ServiceESP-NOW.h
 * Please refer to this other file for information necessary in order to make this work.
 * @version 0.1
 * @date 2023-05-16
 *
 * @copyright Copyright (c) 2023
 *
 */
//#############################################################################

//#############################################################################
#pragma region INCLUDES

#include <Arduino.h>

#include "main.h"
#include "serviceBaseDeTemps.h"
#include "serviceCommunication.h"
#include "piloteESPNOW.h"

#pragma endregion INCLUDES
//############################### PRIVATE VARIABLE ###########################

unsigned int compteur1 = 0;

//############################### EXTERN DECLERATION ###########################
/**
 * @brief The Public structure used by the module. Used to get/set different
 * values and commands to send to the Sensor of the Adam Project. The 
 * pannel will set this value to be sent in the next communication slot.
 */
extern CAPTEUR_ADAM_S ValeurEnvoieCapteur;
/**
 * @brief The Public Structure Used by the module. Is used by the callback function
 *  \ref OnDataRecv wich put the received data by the Sensor in this structure.
 * 
 */
extern CAPTEUR_ADAM_R ValeurRecuCapteur;
/**
 * @brief Structure used to check if the module is working and if information is available
 * 
 */
SERVICECOMMUNICATION ServiceCommunication;

//############################  STATE MACHINE FUNCTION  #####################################
/**
 * @brief Function wich pair two device in ESPNOW
 */
void serviceCommunication_Pairing(void);
/**
 * @brief Function wich wait response from the paired device
 */
void serviceCommunication_WaitResponse(void);
/**
 * @brief Function wich Send a message to the pair device via ESPNOW
 */
void serviceCommunication_Envoie(void);
/**
 * @brief Function wich wait 1 second before restarting communication cycle
 */
void serviceCommunication_Attend(void);



void serviceCommunication_initialise(void)
{
    piloteESPNOW_initialise();
    ServiceCommunication.etatDuModule = SERVICECOMMUNICATION_MODULE_EN_FONCTION;
    serviceBaseDeTemps_execute[SERVICECOMMUNICATION_PHASE] = serviceCommunication_Pairing;
}
void serviceCommunication_Pairing(void)
{
    if(piloteESPNOW.etatDuModule != PILOTEESPNOW_MODULE_EN_FONCTION)  //On s'assure que le pilote est initialiser
    {
        return;
    }
    piloteESPNOW_Pair();
    serviceBaseDeTemps_execute[SERVICECOMMUNICATION_PHASE] = serviceCommunication_WaitResponse;
}
void serviceCommunication_WaitResponse(void)
{
    if(piloteESPNOW.information == PILOTEESPNOW_INFORMATION_TRAITEE)
    {
        return;
    }
    piloteESPNOW.information = PILOTEESPNOW_INFORMATION_TRAITEE;
    serviceBaseDeTemps_execute[SERVICECOMMUNICATION_PHASE] = serviceCommunication_Envoie;
}

void serviceCommunication_Envoie(void)
{
    ValeurEnvoieCapteur.States = 0x08;
    ValeurEnvoieCapteur.Commande = 0xAA;
    ValeurEnvoieCapteur.ValeurA = true;
    ValeurEnvoieCapteur.ValeurB = true;
    ValeurEnvoieCapteur.ValeurC = true;

    piloteESPNOW_send();
    serviceBaseDeTemps_execute[SERVICECOMMUNICATION_PHASE] = serviceCommunication_Attend;
}

void serviceCommunication_Attend(void)
{
    compteur1 = compteur1 + 1;
    if(compteur1 < 500) // 500 x la période de la base de temps (2 ms)
    {
        return;
    }
    Serial.print("Finish waiting 1 sec\n");
    compteur1 = 0;
    serviceBaseDeTemps_execute[SERVICECOMMUNICATION_PHASE] = serviceCommunication_Envoie;
}

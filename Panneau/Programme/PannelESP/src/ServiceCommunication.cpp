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
#include "piloteESPNOWCapteur.h"

#pragma endregion INCLUDES
//############################### PRIVATE VARIABLE ###########################

unsigned int compteur1 = 0;

//############################### EXTERN DECLERATION ###########################
/**
 * @brief The Public structure used by the module. Used to get/set different
 * values and commands to send to the Sensor of the Adam Project. The 
 * pannel will set this value to be sent in the next communication slot.
 */
stSend ValueEnvoieCapteur;
/**
 * @brief The Public Structure Used by the module. Is used by the callback function
 *  \ref OnDataRecv wich put the received data by the Sensor in this structure.
 * 
 */
stReceived ValueRecuCapteur;
/**
 * @brief Structure used to check if the module is working and if information is available
 * 
 */
SERVICECOMMUNICATION ServiceCommunication;

//############################  STATE MACHINE FUNCTION  #####################################

void serviceCommunication_Pairing(void);
void serviceCommunication_Envoie(void);
void serviceCommunication_WaitResponse(void);
void serviceCommunication_Attend(void);

void serviceCommunication_initialise(void)
{
    piloteESPNOWCapteur_initialise();
    ServiceCommunication.etatDuModule = SERVICECOMMUNICATION_MODULE_EN_FONCTION;
    serviceBaseDeTemps_execute[SERVICECOMMUNICATION_PHASE] = serviceCommunication_Pairing;
}
void serviceCommunication_Pairing(void)
{
    if(piloteESPNOWCapteur.etatDuModule != PILOTEESPNOW_MODULE_EN_FONCTION)  //On s'assure que le pilote est initialiser
    {
        return;

    }
    piloteESPNOWCapteur_Pair();
    serviceBaseDeTemps_execute[SERVICECOMMUNICATION_PHASE] = serviceCommunication_Envoie;
}

void serviceCommunication_Envoie(void)
{
    ValueEnvoieCapteur.States = 0x08;
    ValueEnvoieCapteur.Commande = 0x45;
    ValueEnvoieCapteur.ValeurA = false;
    ValueEnvoieCapteur.ValeurB = true;
    ValueEnvoieCapteur.ValeurC = false;

    piloteESPNOWCapteur_send();
    serviceBaseDeTemps_execute[SERVICECOMMUNICATION_PHASE] = serviceCommunication_WaitResponse;
}

void serviceCommunication_WaitResponse(void)
{
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

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
extern CAPTEUR_ADAM_S ValeurEnvoie;
/**
 * @brief The Public Structure Used by the module. Is used by the callback function
 *  \ref OnDataRecv wich put the received data by the Sensor in this structure.
 * 
 */
extern CAPTEUR_ADAM_R ValeurRecu;
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


// DÉCLARATION
void serviceCommunication_initialise(void)
{
    piloteESPNOW_initialise();
    ValeurEnvoie.States = 0x08; // 0x08 en Arret
    ValeurEnvoie.Commande = 0x00;
    ValeurEnvoie.Temperature = 0x00;
    ValeurEnvoie.Humiditee = 0x00;
    ValeurEnvoie.Motion = 0x00;
    ServiceCommunication.etatDuModule = SERVICECOMMUNICATION_MODULE_EN_FONCTION;
    serviceBaseDeTemps_executeDansLoop[SERVICECOMMUNICATION_PHASE] = serviceCommunication_Pairing;
}
void serviceCommunication_Pairing(void)
{
    if(piloteESPNOW.etatDuModule != PILOTEESPNOW_MODULE_EN_FONCTION)  //On s'assure que le pilote est initialiser
    {
        return;
    }
    piloteESPNOW_Pair();
    serviceBaseDeTemps_executeDansLoop[SERVICECOMMUNICATION_PHASE] = serviceCommunication_WaitResponse;
}
void serviceCommunication_WaitResponse(void)
{
    if(piloteESPNOW.information == PILOTEESPNOW_INFORMATION_TRAITEE)
    {
        compteur1++; 
        if(compteur1 == 1000)
        {
            compteur1 = 0;
            Serial.println("PANNEAU HORS LIGNE");
            return;
        }
        return;
    }
    piloteESPNOW.information = PILOTEESPNOW_INFORMATION_TRAITEE;

    Serial.println("Bytes received from Pannel");
    Serial.print("State: ");
    Serial.println(ValeurRecu.States);
    Serial.print("Command: ");
    Serial.println(ValeurRecu.Commande);
    Serial.print("Valeur A: ");
    Serial.println(ValeurRecu.ValeurA);
    Serial.print("Valeur B: ");
    Serial.println(ValeurRecu.ValeurB);
    Serial.print("Valeur C: ");
    Serial.println(ValeurRecu.ValeurC);
    Serial.println();
    Serial.flush();
    if(ValeurRecu.States == SERVICECOMMUNICATION_STATE_OPERATION) // On est en opération
    {
      ValeurEnvoie.States = SERVICECOMMUNICATION_STATE_OPERATION;
    }
    if(ValeurRecu.States == SERVICECOMMUNICATION_STATE_ENARRET) // Si on recoit en Arret
    {
      ValeurEnvoie.States = SERVICECOMMUNICATION_STATE_ENARRET; // On se ment en Arret
    }
    serviceBaseDeTemps_executeDansLoop[SERVICECOMMUNICATION_PHASE] = serviceCommunication_Envoie;
}

void serviceCommunication_Envoie(void)
{
    piloteESPNOW_send();
    serviceBaseDeTemps_executeDansLoop[SERVICECOMMUNICATION_PHASE] = serviceCommunication_WaitResponse;
}


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
#include "piloteESPNOW.h"
#include "AnnexeADAM.h"
#include "serviceBaseDeTemps.h"
#include "serviceCommunication.h"


#pragma endregion INCLUDES
//############################### PRIVATE VARIABLE ###########################

unsigned int compteur1 = 0;

//############################### EXTERN DECLERATION ###########################

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
   //GestionCommuncation_T.piloteValueEnvoie.States = 0x08;   /// avec le systeme d'annexe, pas besoin de rien faire ici!!!!!
   // GestionCommuncation_T.piloteValueEnvoie.Commande = 0x45;
   // GestionCommuncation_T.piloteValueEnvoie.ValueSA = false;
   // GestionCommuncation_T.piloteValueEnvoie.ValueSB = false;
   // GestionCommuncation_T.piloteValueEnvoie.ValueSC = false;

    piloteESPNOW_send();
    serviceBaseDeTemps_execute[SERVICECOMMUNICATION_PHASE] = serviceCommunication_WaitResponse;
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

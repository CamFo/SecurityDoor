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
#include <Arduino.h>

#include "main.h"
#include "serviceBaseDeTemps.h"
#include "serviceCommunication.h"

#include "piloteESPNOWCapteur.h"
#include "piloteESPNOWDoor.h"

#include "interfaceLCD.h"

//Private Variable

unsigned int compteur1 = 0;

unsigned int compteurDoor = 0;
unsigned int compteurCapteur = 0;

//############################### EXTERN DECLERATION ###########################
/**
 * @brief The Public structure used by the module. Used to get/set different
 * values and commands to send to the DOOR of the Adam Project. The 
 * pannel will set this value to be sent in the next communication slot.
 */
extern DOOR_ADAM_S ValeurEnvoieDoor;
/**
 * @brief The Public Structure Used by the module. Is used by the callback function
 *  \ref OnDataRecv wich put the received data by the DOOR in this structure.
 */
extern DOOR_ADAM_R ValeurRecuDoor;

/**
 * @brief The Public structure used by the module. Used to get/set different
 * values and commands to send to the CAPTEUR of the Adam Project. The 
 * pannel will set this value to be sent in the next communication slot.
 */
extern CAPTEUR_ADAM_S ValeurEnvoieCapteur;
/**
 * @brief The Public Structure Used by the module. Is used by the callback function
 *  \ref OnDataRecv wich put the received data by the CAPTEUR in this structure.
 */
extern CAPTEUR_ADAM_R ValeurRecuCapteur;


/**
 * @brief Structure used to check if the module is working and if information is available
 */
SERVICECOMMUNICATION ServiceCommunication;

//############################  STATE MACHINE FUNCTION  #####################################

void serviceCommunication_PairingDoor(void);
void serviceCommunication_EnvoieDoor(void);
void serviceCommunication_WaitResponseDoor(void);
void serviceCommunication_PairingCapteur(void);
void serviceCommunication_EnvoieCapteur(void);
void serviceCommunication_WaitResponseCapteur(void);
void serviceCommunication_Attend(void);

void serviceCommunication_initialise(void)
{
    
    ServiceCommunication.etatDuModule = SERVICECOMMUNICATION_MODULE_EN_FONCTION;
    serviceBaseDeTemps_execute[SERVICECOMMUNICATION_PHASE] = serviceCommunication_PairingDoor;
}

//###############  BEGIN DOOR COMMUNICATION ###################
void serviceCommunication_PairingDoor(void)
{
    piloteESPNOWDoor_initialise();
    piloteESPNOWDoor_Pair();
    serviceBaseDeTemps_execute[SERVICECOMMUNICATION_PHASE] = serviceCommunication_EnvoieDoor;
}

void serviceCommunication_EnvoieDoor(void)
{
    if(piloteESPNOWDoor.etatDuModule != PILOTEESPNOWDOOR_MODULE_EN_FONCTION) // Sécurité
    {
        return;
    }

    ValeurEnvoieDoor.States = 0x08;
    ValeurEnvoieDoor.Commande = 0x62;
    ValeurEnvoieDoor.ValeurA = false;
    ValeurEnvoieDoor.ValeurB = true;
    ValeurEnvoieDoor.ValeurC = false;

    piloteESPNOWDoor_send();
    serviceBaseDeTemps_execute[SERVICECOMMUNICATION_PHASE] = serviceCommunication_WaitResponseDoor;
}

void serviceCommunication_WaitResponseDoor(void)
{
    if(piloteESPNOWDoor.information != PILOTEESPNOWDOOR_INFORMATION_DISPONIBLE)
    {
        compteurDoor++;
        if(compteurDoor <= 50)
        {
            return;
        }
        compteurDoor = 0;

        unsigned char OFFstring[] = "ETAT de la Porte: OFF";
        interfaceLCD_afficheString(320, 100, OFFstring, PURERED, DarkGrey);

        Serial.println("########### ERREUR --  DOOR OFFLINE  -- ERREUR ###########");
        // ON EST EN ERREUR LA PORTE NAS PAS REPONDU DANS UN DELAIS DE 50x la base de temps
        serviceBaseDeTemps_execute[SERVICECOMMUNICATION_PHASE] = serviceCommunication_PairingCapteur;
        return;
    }
    piloteESPNOWDoor.information =PILOTEESPNOWDOOR_INFORMATION_TRAITEE;


    Serial.println("Bytes received Door: ");
    Serial.print("State: ");
    Serial.println(ValeurRecuDoor.States);
    Serial.print("Command: ");
    Serial.println(ValeurRecuDoor.Commande);
    Serial.print("État Porte: ");
    Serial.println(ValeurRecuDoor.EtatPorte);
    Serial.print("User NFC: ");
    Serial.println(ValeurRecuDoor.UserNFC);
    Serial.print("État Serrure: ");
    Serial.println(ValeurRecuDoor.EtatSerrure);
    Serial.println();

    unsigned char ONstring[] = "ETAT de la Porte: ON ";
    interfaceLCD_afficheString(320, 100, ONstring, PUREGREEN, DarkGrey);

    serviceBaseDeTemps_execute[SERVICECOMMUNICATION_PHASE] = serviceCommunication_PairingCapteur;
}
//#############  END DOOR COMMUNICATION ################


//#############  BEGIN CAPTEUR COMMUNICATION ##############
void serviceCommunication_PairingCapteur(void)
{   
    piloteESPNOWCapteur_initialise();
    piloteESPNOWCapteur_Pair();
    serviceBaseDeTemps_execute[SERVICECOMMUNICATION_PHASE] = serviceCommunication_EnvoieCapteur;
}
void serviceCommunication_EnvoieCapteur(void)
{
    if(piloteESPNOWCapteur.etatDuModule != PILOTEESPNOWCAPTEUR_MODULE_EN_FONCTION) // Sécurité
    {
        return;
    }

    ValeurEnvoieCapteur.States = 0x08;
    ValeurEnvoieCapteur.Commande = 0xFF;
    ValeurEnvoieCapteur.ValeurA = true;
    ValeurEnvoieCapteur.ValeurB = true;
    ValeurEnvoieCapteur.ValeurC = 56;

    piloteESPNOWCapteur_send();
    serviceBaseDeTemps_execute[SERVICECOMMUNICATION_PHASE] = serviceCommunication_WaitResponseCapteur;
}
void serviceCommunication_WaitResponseCapteur(void)
{
    if(piloteESPNOWCapteur.information != PILOTEESPNOWCAPTEUR_INFORMATION_DISPONIBLE)
    {
        compteurCapteur++;
        if(compteurCapteur <= 50)
        {
            return;
        }
        compteurCapteur = 0;

        unsigned char OFFstring[] = "ETAT du Capteur: OFF";
        interfaceLCD_afficheString(320, 120, OFFstring, PURERED, DarkGrey);

        Serial.println("########### ERREUR --  CAPTEUR OFFLINE  -- ERREUR ###########");
        // ON EST EN ERREUR LE CAPTEUR NAS PAS REPONDU DANS UN DELAIS DE 50x la base de temps
        serviceBaseDeTemps_execute[SERVICECOMMUNICATION_PHASE] = serviceCommunication_Attend;
        return;
    }
    piloteESPNOWCapteur.information = PILOTEESPNOWCAPTEUR_INFORMATION_TRAITEE;

    Serial.println("Bytes received: ");
    Serial.print("State: ");
    Serial.println(ValeurRecuCapteur.States);
    Serial.print("Command: ");
    Serial.println(ValeurRecuCapteur.Commande);
    Serial.print("Température: ");
    Serial.println(ValeurRecuCapteur.Temperature);
    Serial.print("Humidité: ");
    Serial.println(ValeurRecuCapteur.Humiditee);
    Serial.print("Mouvement: ");
    Serial.println(ValeurRecuCapteur.Motion);
    Serial.println();

    unsigned char ONstring[] = "ETAT du Capteur: ON ";
    interfaceLCD_afficheString(320, 120, ONstring, PUREGREEN, DarkGrey);

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
    serviceBaseDeTemps_execute[SERVICECOMMUNICATION_PHASE] = serviceCommunication_PairingDoor;
}

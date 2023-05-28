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
#include <esp_now.h>
#include <WiFi.h>

#include "main.h"
#include "serviceBaseDeTemps.h"
#include "ServiceCommunication.h"

#include "piloteESPNOWCapteur.h"
#include "piloteESPNOWDoor.h"

#include "interfaceLCD.h"

//Private Variable

unsigned int compteur1 = 0;
unsigned int compteurDoor = 0;
unsigned int compteurCapteur = 0;
unsigned int compteurEntreP = 0;

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
void serviceCommunication_AttendEntrePair(void);
void serviceCommunication_PairingCapteur(void);
void serviceCommunication_EnvoieCapteur(void);
void serviceCommunication_WaitResponseCapteur(void);
void serviceCommunication_Attend(void);

void serviceCommunication_initialise(void)
{
    WiFi.mode(WIFI_MODE_STA);

    if (esp_now_init() != ESP_OK) 
    {
        Serial.println("Error initializing ESP-NOW");
        return;
    }
    
    // INITIALISE VALUE TO SEND
    ValeurEnvoieDoor.States = SERVICECOMMUNICATION_STATE_ENARRET;
    ValeurEnvoieDoor.Commande = SERVICECOMMUNICATION_COMMANDE_NULL; 
    ValeurEnvoieDoor.ValeurA = 0x00;
    ValeurEnvoieDoor.ValeurB = 0x00;
    ValeurEnvoieDoor.ValeurC = 0x00;

    ValeurEnvoieCapteur.States = SERVICECOMMUNICATION_STATE_ENARRET;
    ValeurEnvoieCapteur.Commande = SERVICECOMMUNICATION_COMMANDE_NULL;
    ValeurEnvoieCapteur.ValeurA = 0x00;
    ValeurEnvoieCapteur.ValeurB = 0x00;
    ValeurEnvoieCapteur.ValeurC = 0x00;

    ServiceCommunication.etatDuModule = SERVICECOMMUNICATION_MODULE_EN_FONCTION;
    serviceBaseDeTemps_executeDansLoop[SERVICECOMMUNICATION_PHASE] = serviceCommunication_PairingDoor;
}

//###############  BEGIN DOOR COMMUNICATION ###################
void serviceCommunication_PairingDoor(void)
{
    Serial.println("[#][#]########  COMMUNICATION CYCLE BEGIN ########[#][#]");
    Serial.flush();

    piloteESPNOWDoor_initialise();
    piloteESPNOWDoor_Pair();
    serviceBaseDeTemps_executeDansLoop[SERVICECOMMUNICATION_PHASE] = serviceCommunication_EnvoieDoor;
}

void serviceCommunication_EnvoieDoor(void)
{
    if(piloteESPNOWDoor.etatDuModule != PILOTEESPNOWDOOR_MODULE_EN_FONCTION) // Sécurité
    {
        return;
    }

    piloteESPNOWDoor_send();
    serviceBaseDeTemps_executeDansLoop[SERVICECOMMUNICATION_PHASE] = serviceCommunication_WaitResponseDoor;
}

void serviceCommunication_WaitResponseDoor(void)
{
    if(piloteESPNOWDoor.information != PILOTEESPNOWDOOR_INFORMATION_DISPONIBLE)
    {
        compteurDoor++;
        if(compteurDoor <= 10)
        {
            return;
        }
        compteurDoor = 0;

        interfaceLCD.DoorState = DOORSTATE_OFF;
        BRS_LCD_Draw_Shape_CircleF(450, 66, 8, PURERED);  // Led RGB qui indique l'état de la COM

        Serial.println("X=X=X ERREUR --  DOOR OFFLINE  -- ERREUR X=X=X\n");
        // ON EST EN ERREUR LA PORTE NAS PAS REPONDU DANS UN DELAIS 200 Ms
        serviceBaseDeTemps_executeDansLoop[SERVICECOMMUNICATION_PHASE] = serviceCommunication_AttendEntrePair;
        return;
    }
    piloteESPNOWDoor.information =PILOTEESPNOWDOOR_INFORMATION_TRAITEE;


    Serial.println("Bytes received DOOR");
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
    Serial.flush();

    interfaceLCD.DoorState = DOORSTATE_ON;
    BRS_LCD_Draw_Shape_CircleF(450, 66, 8, PUREGREEN);  // Led RGB qui indique l'état de la COM

    serviceBaseDeTemps_executeDansLoop[SERVICECOMMUNICATION_PHASE] = serviceCommunication_AttendEntrePair;
}
//#############  END DOOR COMMUNICATION ################

void serviceCommunication_AttendEntrePair(void)
{
    if(compteurEntreP <= 50) // Délais de 50 x 10ms = 500ms
    {
        compteurEntreP ++;
        return;
    }
    compteurEntreP = 0;
    serviceBaseDeTemps_executeDansLoop[SERVICECOMMUNICATION_PHASE] = serviceCommunication_PairingCapteur;
}


//#############  BEGIN CAPTEUR COMMUNICATION ##############
void serviceCommunication_PairingCapteur(void)
{   
    piloteESPNOWCapteur_initialise();
    piloteESPNOWCapteur_Pair();
    serviceBaseDeTemps_executeDansLoop[SERVICECOMMUNICATION_PHASE] = serviceCommunication_EnvoieCapteur;
}
void serviceCommunication_EnvoieCapteur(void)
{

    if(piloteESPNOWCapteur.etatDuModule != PILOTEESPNOWCAPTEUR_MODULE_EN_FONCTION) // Sécurité
    {
        return;
    }

    piloteESPNOWCapteur_send();
    serviceBaseDeTemps_executeDansLoop[SERVICECOMMUNICATION_PHASE] = serviceCommunication_WaitResponseCapteur;
}
void serviceCommunication_WaitResponseCapteur(void)
{
    if(piloteESPNOWCapteur.information != PILOTEESPNOWCAPTEUR_INFORMATION_DISPONIBLE)
    {
        compteurCapteur++;
        if(compteurCapteur <= 10)
        {
            return;
        }
        compteurCapteur = 0;

        interfaceLCD.CapteurState = CAPTEURSTATE_OFF;
        BRS_LCD_Draw_Shape_CircleF(450, 87, 8, PURERED);  // Led RGB qui indique l'état de la COM


        Serial.println("X=X=X ERREUR -- CAPTEUR OFFLINE -- ERREUR X=X=X\n");
        // ON EST EN ERREUR LE CAPTEUR NAS PAS REPONDU DANS UN DELAIS DE 50x la base de temps

        Serial.println("[#][#]########  COMMUNICATION CYCLE END ########[#][#]");
        Serial.flush();
        serviceBaseDeTemps_executeDansLoop[SERVICECOMMUNICATION_PHASE] = serviceCommunication_Attend;
        return;
    }
    piloteESPNOWCapteur.information = PILOTEESPNOWCAPTEUR_INFORMATION_TRAITEE;

    Serial.println("Bytes received: CAPTEUR");
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
    Serial.flush();

    interfaceLCD.CapteurState = CAPTEURSTATE_ON;
    BRS_LCD_Draw_Shape_CircleF(450, 87, 8, PUREGREEN);  // Led RGB qui indique l'état de la COM
    
    Serial.println("[#][#]########  -COMMUNICATION CYCLE END- ########[#][#]");
    Serial.flush();
    serviceBaseDeTemps_executeDansLoop[SERVICECOMMUNICATION_PHASE] = serviceCommunication_Attend;
}

void serviceCommunication_Attend(void)
{
    compteur1 = compteur1 + 1;
    if(compteur1 < 100) // 200 x la période de 10ms du Core 0
    {
        return;
    }
    compteur1 = 0;
    serviceBaseDeTemps_executeDansLoop[SERVICECOMMUNICATION_PHASE] = serviceCommunication_PairingDoor;
}

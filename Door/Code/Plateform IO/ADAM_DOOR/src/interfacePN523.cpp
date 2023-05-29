/**
 * @file interfacePN523.cpp
 * @author Ilyes Gharmoul (ilyesdu2002@hotmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-05-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */

//INCLUSIONS
#include <Arduino.h>
#include "main.h"
#include "piloteI2C.h"
#include "PN532.h"
#include "Adafruit_PN532.h"
#include "interfacePN523.h"
#include "serviceBaseDeTemps.h"
#include <stdio.h>


#define INTERFACEPN532_COMPTE_2S (\
INTERFACEPN532_COMPTE_EN_MS * SERVICEBASEDETEMPS_FREQUENCE_EN_HZ \
  /250.0)

Adafruit_PN532 nfc(PILOTEI2C_SDA1,PILOTEI2C_SCL1);


//Definitions privees

//Declarations de fonctions privees:
void interfacePN523_VerifierPresenceNFC();
void interfacePN523_LectureNFC();
#define MODE_DEBUG_PN532
//Definitions de variables privees:
unsigned int interfacePN532_compteur;
//Definitions de fonctions privees:
void interfacePN523_VerifierPresenceNFC()
{
    uint32_t versiondata = nfc.getFirmwareVersion();
    if (! versiondata)
    {
        #ifdef MODE_DEBUG_PN532
        interfacePN532_compteur++;
        if (interfacePN532_compteur < INTERFACEPN532_COMPTE_2S)
        return;
        interfacePN532_compteur = 0;
        Serial.print("Didn't find PN53x board");
        #endif
        return;
    }
    Serial.print("Found chip PN5"); Serial.println((versiondata>>24) & 0xFF, HEX);
    Serial.print("Firmware ver. "); Serial.print((versiondata>>16) & 0xFF, DEC);
    Serial.print('.'); Serial.println((versiondata>>8) & 0xFF, DEC);

    Serial.println("Waiting for an ISO14443A Card ...");
    serviceBaseDeTemps_execute[INTERFACEPN523_PHASE] = interfacePN523_LectureNFC;
    return;
    //piloteI2C1_ecritUnByte(I2C_ADR_NFC,PN532_I2C_BUSY,TRUE);
    //piloteI2C1_lisUnOctet(PN532_I2C_READBIT);
}

void interfacePN523_LectureNFC()
{

}

//Definitions de variables publiques:
INTERFACEPN523 interfacePN523;

//Definitions de fonctions publiques:
void interfacePN523_initalise()
 {
    nfc.begin();
    interfacePN523.etatDeLecture = INTERFACEPN523_MODULE_PAS_EN_FONCTION;
    interfacePN523.information = INTERFACEPN523_INFORMATION_TRAITEE;
    interfacePN523.etatDuModule = INTERFACEPN523_MODULE_PAS_EN_FONCTION;
    serviceBaseDeTemps_execute[INTERFACEPN523_PHASE] = interfacePN523_VerifierPresenceNFC;
 }




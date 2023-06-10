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
INTERFACEPN523 interfacePN523;

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
    Serial.print("test");
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
uint8_t success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
  uint8_t uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)

  // Wait for an NTAG203 card.  When one is found 'uid' will be populated with
  // the UID, and uidLength will indicate the size of the UUID (normally 7)
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);

  if (success) {
    // Display some basic information about the card
    Serial.println("Found an ISO14443A card");
    Serial.print("  UID Length: ");Serial.print(uidLength, DEC);Serial.println(" bytes");
    Serial.print("  UID Value: ");
    nfc.PrintHex(uid, uidLength);
    Serial.println("");

    if (uidLength == 7)
    {
      uint8_t data[32];

      // We probably have an NTAG2xx card (though it could be Ultralight as well)
      Serial.println("Seems to be an NTAG2xx tag (7 byte UID)");

      // NTAG2x3 cards have 39*4 bytes of user pages (156 user bytes),
      // starting at page 4 ... larger cards just add pages to the end of
      // this range:

      // See: http://www.nxp.com/documents/short_data_sheet/NTAG203_SDS.pdf

      // TAG Type       PAGES   USER START    USER STOP
      // --------       -----   ----------    ---------
      // NTAG 203       42      4             39
      // NTAG 213       45      4             39
      // NTAG 215       135     4             129
      // NTAG 216       231     4             225

      for (uint8_t i = 0; i < 42; i++)
      {
        success = nfc.ntag2xx_ReadPage(i, data);

        // Display the current page number
        Serial.print("PAGE ");
        if (i < 10)
        {
          Serial.print("0");
          Serial.print(i);
        }
        else
        {
          Serial.print(i);
        }
        Serial.print(": ");

        // Display the results, depending on 'success'
        if (success)
        {
          // Dump the page data
          nfc.PrintHexChar(data, 4);
        }
        else
        {
          Serial.println("Unable to read the requested page!");
        }
      }
    }
    else
    {
      Serial.println("This doesn't seem to be an NTAG203 tag (UUID length != 7 bytes)!");
    }
  }
}

//Definitions de variables publiques:


//Definitions de fonctions publiques:
void interfacePN523_initalise()
 {
    nfc.begin();
    interfacePN523.etatDeLecture = INTERFACEPN523_MODULE_PAS_EN_FONCTION;
    interfacePN523.information = INTERFACEPN523_INFORMATION_TRAITEE;
    interfacePN523.etatDuModule = INTERFACEPN523_MODULE_PAS_EN_FONCTION;
    //serviceBaseDeTemps_execute[INTERFACEPN523_PHASE] = interfacePN523_VerifierPresenceNFC;
 }




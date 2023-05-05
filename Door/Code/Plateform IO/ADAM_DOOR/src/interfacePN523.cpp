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
#include "interfacePN523.h"
#include "PN532.h"
#include "serviceBaseDeTemps.h"
#include <stdio.h>


//Definitions privees


//Declarations de fonctions privees:
//pas de fonction privees

//Definitions de variables privees:
unsigned int interfacePN523_compteur;
//Definitions de fonctions privees:
void interfacePN523_VerifierPresenceNFC()
{
    piloteI2C1_ecritUnByte(I2C_ADR_NFC,PN532_I2C_BUSY,TRUE);
    piloteI2C1_lisUnEntier(PN532_I2C_READBIT);
}
//Definitions de variables publiques:
INTERFACEPN523 interfacePN523;

//Definitions de fonctions publiques:
void interfacePN523_initalise()
 {
  interfacePN523.etatDeLecture = INTERFACEPN523_MODULE_PAS_EN_FONCTION;
  interfacePN523.information = INTERFACEPN523_INFORMATION_TRAITEE;
  interfacePN523.etatDuModule = INTERFACEPN523_MODULE_PAS_EN_FONCTION;
  //serviceBaseDeTemps_execute[INTERFACEPN523_PHASE] = interfacePN523_VerifierPresenceNFC;
 }




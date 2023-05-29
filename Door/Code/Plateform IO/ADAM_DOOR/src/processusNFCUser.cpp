/**
 * @file processusNFCUser.cpp
 * @author Ilyes Gharmoul (ilyesdu2002@hotmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-05-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PN532.h>
#include "main.h"
#include "piloteI2C.h"
#include "piloteIOT1.h"
#include "piloteIOT2.h"
#include "piloteIOT3.h"
#include "piloteBuzzer.h"
#include "piloteESPNOW.h"
#include "interfaceRGB.h"
#include "interfacePN523.h"
#include "interfaceBuzzer.h"
#include "interfaceMoteur.h"
#include "processusPourTest.h"
#include "serviceBaseDeTemps.h"
#include "ServiceCommunication.h"
#include "processusNFCUser.h"


#include <stdio.h>
void processusNFCUser_verifiePresenceNFC();

void processusNFCUser_verifiePresenceNFC()
{

}
void processusNFCUser_initialise()
{
  serviceBaseDeTemps_execute[PROCESSUSGESTIONPAIRING_PHASE] = processusNFCUser_verifiePresenceNFC;
  
}
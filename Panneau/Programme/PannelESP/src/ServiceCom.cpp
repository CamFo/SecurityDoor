//#############################################################################
/**
 * @file ServiceESP-NOW.cpp
 * @author Camille Fortin (camfortin2022@gmail.com)
 * @brief
 * Program file containing the code defined in ServiceESP-NOW.h
 * Please refer to this other file for information necessary in order to make this work.
 * @version 0.1
 * @date 2022-11-14
 *
 * @copyright Copyright (c) 2022
 *
 */
//#############################################################################

//#############################################################################
#pragma region INCLUDES

#include <WiFi.h>
#include <stdio.h>

#include "main.h"
#include "serviceCom.h"
#include "piloteESPNOWCapteur.h"

#pragma endregion INCLUDES
//#############################################################################
#pragma region EXTERN_DECLARATIONS

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


#pragma endregion EXTERN_DECLARATIONS
//#############################################################################
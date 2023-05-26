#ifndef Service_Communication_H
#define Service_Communication_H
/**
 * @file ServiceESP-NOW.h
 * @author Camille Fortin (camfortin2022@gmail.com)
 * @brief
 * This service is a c library which goal is to parse data sent or data received for the Adam Project.
 * It's made to send command to modules and received their response at a predetermined interval.
 * @version 0.1
 * @date 2023-05-16
 * @copyright Copyright (c) 2023
 * 
 */
//#############################################################################

#define SERVICECOMMUNICATION_INFORMATION_DISPONIBLE 1
#define SERVICECOMMUNICATION_INFORMATION_TRAITEE 0
#define SERVICECOMMUNICATION_MODULE_EN_FONCTION 1
#define SERVICECOMMUNICATION_MODULE_PAS_EN_FONCTION 0

//-----------------------------------------------------------------------------
#define SERVICECOMMUNICATION_STATE_ENARRET    0x09
#define SERVICECOMMUNICATION_STATE_OPERATION  0x08
#define SERVICECOMMUNCATIION_STATE_ERREUR     0x07
//State

#define SERVICECOMMUNICATION_COMMANDE_BARRER   0x10
#define SERVICECOMMUNICATION_COMMANDE_DEBARRER 0x11
#define SERVICECOMMUNICATION_COMMANDE_NULL   0x00
/**
 * @brief Indicates that the library is not currently in any errors.
 */
#define NO_ERROR 0
/**
 * @brief Indicates that there was an error when parsing a received \ref stModes
 * from a communicating module. The received \ref stModes didn't match availables
 * \ref stModes and couldn't be put in \ref ModuleData
 */
#define ERROR_RX_MODE_DOESNT_EXIST 1
/**
 * @brief Indicates that there was an error when parsing a received \ref stStates
 * from a communicating module. The received \ref stStates didn't match availables
 * \ref stStates and couldn't be put in \ref ModuleData
 */
#define ERROR_RX_STATE_DOESNT_EXIST 2
/**
 * @brief Indicates that there was an error when parsing a received \ref stCommands
 * from a communicating module. The received \ref stCommands didn't match availables
 * \ref stCommands and couldn't be put in \ref ModuleData
 */
#define ERROR_RX_COMMAND_DOESNT_EXIST 3
/**
 * @brief The library timed out and could not receive an \ref stModes from a CAN
 * slot in the given time.
 */
#define ERROR_TIMEDOUT 4
/**
 * @brief Indicates that the module using this library encountered an error due to
 * factors outside of this library.
 */
#define ERROR_SPECIFIC_TO_MODULE 5


// STRUCTURE PUBLICS

/// @brief Structure public qui permet de savoir et de changer l'état du module  
typedef struct
{
  unsigned char etatDuModule;
  unsigned char information;

} SERVICECOMMUNICATION;
extern SERVICECOMMUNICATION ServiceCommunication;



//#############################################################################
#pragma region PUBLIC_FUNCTIONS

/**
* @brief Function called which initialises all the structures necessary. it is
* important to call this function before main execution of the program. It is a state
* machine wich function with a timebase services.
* @author Camille Fortin
* @date 2023-05-16
* @param void Initialisation functions take no parameters
*/
void serviceCommunication_initialise(void);


#pragma endregion PUBLIC_FUNCTIONS
//#############################################################################


#endif
/**
 * @file interfaceMoteur.cpp
 * @author ilyes gharmoul (ilyesdu2002@.com)
 * @brief 
 * @version 0.1
 * @date 2023-05-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <Arduino.h>
#include "main.h"
#include "piloteIOC1.h"
#include "interfaceMoteur.h"


//Definitions privees
//pas de definitions privees

//Declarations de fonctions privees:
//pas de fonction privees

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
//pas de variables publiques

//Definitions de fonctions publiques:
INTERFACEMOTEUR interfaceMoteur;

void interfaceMoteur_initalise()
{
    interfaceMoteur.etatDuModule = INTERFACEMOTEUR_MODULE_PAS_EN_FONCTION;
    interfaceMoteur.information = INTERFACEMOTEUR_INFORMATION_TRAITEE;
}
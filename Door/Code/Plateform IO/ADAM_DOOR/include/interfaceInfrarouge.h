/**
 * @file interfaceInfrarouge.h
 * @author Ilyes Gharmoul (ilyesdu2002@hotmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-05-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef INTERFACEINFRAROUGE_H
#define INTERFACEINFRAROUGE_H

#define INTERFACEINFRAROUGE_MODULE_EN_FONCTION 1
#define INTERFACEINFRAROUGE_MODULE_PAS_EN_FONCTION 0
#define INTERFACEINFRAROUGE_INFORMATION_DISPONIBLE 1
#define INTERFACEINFRAROUGE_INFORMATION_TRAITEE 0
#define INTERFACEINFRAROUGE_INACTIVE 0
#define INTERFACEINFRAROUGE_ACTIVE  1
#define INTERFACEINFRAROUGE_PAS_EN_FONCTION 2


#define INTERFACEINFRAROUGE_AUCUNBRUIT 0
#define INTERFACEINFRAROUGE_25POURCENT 1
#define INTERFACEINFRAROUGE_50POURCENT 2
#define INTERFACEINFRAROUGE_75POURCENT 3
#define INTERFACEINFRAROUGE_100POURCENT 4
#define INTERFACEINFRAROUGE_MAXSTATE 5
/// @brief Structure public qui permet de savoir et de changer l'état du module  
typedef struct
{
    bool RequeteActive;
    bool etatDuModuleRecepteur;
    bool etatDuModuleTransmetteur;
} INTERFACEINFRAROUGE;
void interfaceInfrarouge_initalise();



extern INTERFACEINFRAROUGE interfaceInfrarouge;

#endif
/**
 * @file interfaceMoteur.h
 * @author Ilyes Gharmoul (ilyesdu2002@.com)
 * @brief 
 * @version 0.1
 * @date 2023-05-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef INTERFACEMOTEUR_H
#define INTERFACEMOTEUR_H


#define INTERFACEMOTEUR_MODULE_EN_FONCTION 1
#define INTERFACEMOTEUR_MODULE_PAS_EN_FONCTION 0
#define INTERFACEMOTEUR_INFORMATION_DISPONIBLE 1
#define INTERFACEMOTEUR_INFORMATION_TRAITEE 0
#define INTERFACEMOTEUR_INACTIVE 0
#define INTERFACEMOTEUR_ACTIVE  1
#define INTERFACEMOTEUR_PAS_EN_FONCTION 2
#define INTERFACEMOTEUR_DIRECTION_UNDEFINED 0
#define INTERFACEMOTEUR_DIRECTION_DROITE 1
#define INTERFACEMOTEUR_DIRECTION_GAUCHE 2
#define INTERFACEMOTEUR_DUREE_NONDEFINIE 0
/// @brief Structure public qui permet de savoir et de changer l'état du module  
typedef struct
{
  unsigned char etatDuModule;  
  unsigned char RequeteDirection;
  unsigned char direction;
  unsigned int  dureeActive;
  bool RequeteActive;

} INTERFACEMOTEUR;

void interfaceMoteur_droite();
void interfaceMoteur_gauche();
void interfaceMoteur_initalise();
void interfaceMoteur_Delai1Sec();
void interfaceMoteur_attenteDirective();

extern INTERFACEMOTEUR interfaceMoteur;
#endif
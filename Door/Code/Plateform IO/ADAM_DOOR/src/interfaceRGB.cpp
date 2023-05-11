/**
 * @file interfaceRGB.cpp
 * @author Ilyes Gharmoul (ilyesdu2002@hotmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-05-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */

// Includes

#include <Arduino.h>
#include "main.h"
#include "piloteIOT12.h"
#include "piloteIOT13.h"
#include "piloteIOT14.h"
#include "interfaceRGB.h"

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

//A mettre les defines dans main.h
//#define INTERFACERGB_VALEUR_ROUGE 0
//#define INTERFACERGB_VALEUR_BLEU  1
//#define INTERFACERGB_VALEUR_VERT  2
//#define INTERFACERGB_VALEUR_JAUNE 3
//#define INTERFACERGB_VALEUR_BLEUP 4
//#define INTERFACERGB_VALEUR_MAUVE 5
//#define INTERFACERGB_VALEUR_BLANC 6

void interfaceRGB_allumeBlanc()
{
  piloteIOT12_metAUn();
  piloteIOT13_metAUn();
  piloteIOT14_metAUn();
}
void interfaceRGB_eteintTous()
{
  piloteIOT12_metAZero();
  piloteIOT13_metAZero();
  piloteIOT14_metAZero();
}
void interfaceRGB_initialise()
{
  interfaceRGB_eteintTous();
}
void interfaceRGB_allumeCouleur(unsigned int Couleur)
{
  switch(Couleur)
  {
    case INTERFACERGB_VALEUR_ROUGE:
    piloteIOT12_metA(INTERFACERGB_VALEUR_POUR_ETEINDRE);
    piloteIOT13_metA(INTERFACERGB_VALEUR_POUR_ALLUMER);
    piloteIOT14_metA(INTERFACERGB_VALEUR_POUR_ETEINDRE);
    break;
    case INTERFACERGB_VALEUR_BLEU:
    piloteIOT12_metA(INTERFACERGB_VALEUR_POUR_ETEINDRE);
    piloteIOT13_metA(INTERFACERGB_VALEUR_POUR_ETEINDRE);
    piloteIOT14_metA(INTERFACERGB_VALEUR_POUR_ALLUMER);
    break;
    case INTERFACERGB_VALEUR_VERT:
    piloteIOT12_metA(INTERFACERGB_VALEUR_POUR_ALLUMER);
    piloteIOT13_metA(INTERFACERGB_VALEUR_POUR_ETEINDRE);
    piloteIOT14_metA(INTERFACERGB_VALEUR_POUR_ETEINDRE);
    break;
    case INTERFACERGB_VALEUR_JAUNE:
    piloteIOT12_metA(INTERFACERGB_VALEUR_POUR_ALLUMER);
    piloteIOT13_metA(INTERFACERGB_VALEUR_POUR_ALLUMER);
    piloteIOT14_metA(INTERFACERGB_VALEUR_POUR_ETEINDRE);
    break;
    case INTERFACERGB_VALEUR_BLEUP:
    piloteIOT12_metA(INTERFACERGB_VALEUR_POUR_ALLUMER);
    piloteIOT13_metA(INTERFACERGB_VALEUR_POUR_ETEINDRE);
    piloteIOT14_metA(INTERFACERGB_VALEUR_POUR_ALLUMER);
    break; 
    case INTERFACERGB_VALEUR_MAUVE:
    piloteIOT12_metA(INTERFACERGB_VALEUR_POUR_ETEINDRE);
    piloteIOT13_metA(INTERFACERGB_VALEUR_POUR_ALLUMER);
    piloteIOT14_metA(INTERFACERGB_VALEUR_POUR_ALLUMER);
    break;
    case INTERFACERGB_VALEUR_BLANC:
    piloteIOT12_metA(INTERFACERGB_VALEUR_POUR_ALLUMER);
    piloteIOT13_metA(INTERFACERGB_VALEUR_POUR_ALLUMER);
    piloteIOT14_metA(INTERFACERGB_VALEUR_POUR_ALLUMER);
    break;
  }
}

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
#include "piloteIOT1.h"
#include "piloteIOT2.h"
#include "piloteIOT3.h"
#include "interfaceRGB.h"
#include "serviceBaseDeTemps.h"

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

INTERFACERGB interfaceRGB;
unsigned int interfaceRGB_compteur;
void interfaceRGB_changecouleur();

void interfaceRGB_allumeBlanc()
{
  piloteIOT2_metAUn(); //R
  piloteIOT1_metAUn(); //B
  piloteIOT3_metAUn(); //G

}
void interfaceRGB_eteintTous()
{
  piloteIOT2_metAZero();
  piloteIOT3_metAZero();
  piloteIOT1_metAZero();
}

void interfaceRGB_allumeCouleur(unsigned int Couleur)
{
  switch(Couleur)
  {
    case INTERFACERGB_VALEUR_ROUGE:
    piloteIOT1_metA(INTERFACERGB_VALEUR_POUR_ALLUMER);
    piloteIOT2_metA(INTERFACERGB_VALEUR_POUR_ETEINDRE);
    piloteIOT3_metA(INTERFACERGB_VALEUR_POUR_ETEINDRE);
    #ifdef MODE_DEBUG
    Serial.print("ROUGE \n");
    #endif
    break;
    case INTERFACERGB_VALEUR_BLEU:
    piloteIOT1_metA(INTERFACERGB_VALEUR_POUR_ETEINDRE);
    piloteIOT2_metA(INTERFACERGB_VALEUR_POUR_ETEINDRE);
    piloteIOT3_metA(INTERFACERGB_VALEUR_POUR_ALLUMER);
    #ifdef MODE_DEBUG
    Serial.print("BLEU \n");
    #endif
    break;
    case INTERFACERGB_VALEUR_VERT:
    piloteIOT1_metA(INTERFACERGB_VALEUR_POUR_ETEINDRE);
    piloteIOT2_metA(INTERFACERGB_VALEUR_POUR_ALLUMER);
    piloteIOT3_metA(INTERFACERGB_VALEUR_POUR_ETEINDRE);
    #ifdef MODE_DEBUG
    Serial.print("VERT \n");
    #endif
    break;
    case INTERFACERGB_VALEUR_JAUNE:
    piloteIOT1_metA(INTERFACERGB_VALEUR_POUR_ALLUMER);
    piloteIOT2_metA(INTERFACERGB_VALEUR_POUR_ALLUMER);
    piloteIOT3_metA(INTERFACERGB_VALEUR_POUR_ETEINDRE);
    #ifdef MODE_DEBUG
    Serial.print("JAUNE \n");
    #endif
    break;
    case INTERFACERGB_VALEUR_BLEUP:
    piloteIOT1_metA(INTERFACERGB_VALEUR_POUR_ALLUMER);
    piloteIOT2_metA(INTERFACERGB_VALEUR_POUR_ETEINDRE);
    piloteIOT3_metA(INTERFACERGB_VALEUR_POUR_ALLUMER);
    #ifdef MODE_DEBUG
    Serial.print("BLEU PALE \n");
    #endif
    break; 
    case INTERFACERGB_VALEUR_MAUVE:
    piloteIOT1_metA(INTERFACERGB_VALEUR_POUR_ETEINDRE);
    piloteIOT2_metA(INTERFACERGB_VALEUR_POUR_ALLUMER);
    piloteIOT3_metA(INTERFACERGB_VALEUR_POUR_ALLUMER);
    #ifdef MODE_DEBUG
    Serial.print("MAUVE \n");
    #endif
    break;
    case INTERFACERGB_VALEUR_BLANC:
    piloteIOT1_metA(INTERFACERGB_VALEUR_POUR_ALLUMER);
    piloteIOT2_metA(INTERFACERGB_VALEUR_POUR_ALLUMER);
    piloteIOT3_metA(INTERFACERGB_VALEUR_POUR_ALLUMER);
    #ifdef MODE_DEBUG
    Serial.print("BLANC \n");
    #endif
    break;
    case INTERFACERGB_VALEUR_ETEINT:
    interfaceRGB_eteintTous();
    break; 
  }
}

void interfaceRGB_changecouleur()
{
  if (interfaceRGB.RequeteActive == INTERFACERGB_INACTIVE)
  return;

  interfaceRGB.etatDuModule = INTERFACERGB_MODULE_EN_FONCTION;
  interfaceRGB_allumeCouleur(interfaceRGB.couleur);
  if (interfaceRGB.oldCouleur != interfaceRGB.couleur)
  interfaceRGB_compteur = 0;

  interfaceRGB.oldCouleur = interfaceRGB.couleur;
  interfaceRGB_compteur++;
  if (interfaceRGB_compteur < interfaceRGB.dureeActive)
  return;

  interfaceRGB_compteur = 0; 
  interfaceRGB_eteintTous();
  interfaceRGB.etatDuModule = INTERFACERGB_MODULE_PAS_EN_FONCTION;
  interfaceRGB.couleur = INTERFACERGB_VALEUR_ETEINT;
  interfaceRGB.RequeteActive = INTERFACERGB_INACTIVE;
  serviceBaseDeTemps_execute[INTERFACERGB_PHASE] = interfaceRGB_changecouleur;
}
void interfaceRGB_initialise()
{
    interfaceRGB_eteintTous();
    interfaceRGB.dureeActive = INTERFACERGB_PAS_EN_FONCTION;
    interfaceRGB.RequeteActive = INTERFACERGB_INACTIVE;
    interfaceRGB.etatDuModule = INTERFACERGB_MODULE_PAS_EN_FONCTION;
    interfaceRGB.couleur =  INTERFACERGB_VALEUR_ETEINT;
    serviceBaseDeTemps_execute[INTERFACERGB_PHASE] = interfaceRGB_changecouleur;
}
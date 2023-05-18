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
    Serial.print("ROUGE \n");
    break;
    case INTERFACERGB_VALEUR_BLEU:
    piloteIOT1_metA(INTERFACERGB_VALEUR_POUR_ETEINDRE);
    piloteIOT2_metA(INTERFACERGB_VALEUR_POUR_ETEINDRE);
    piloteIOT3_metA(INTERFACERGB_VALEUR_POUR_ALLUMER);
    Serial.print("BLEU \n");
    break;
    case INTERFACERGB_VALEUR_VERT:
    piloteIOT1_metA(INTERFACERGB_VALEUR_POUR_ETEINDRE);
    piloteIOT2_metA(INTERFACERGB_VALEUR_POUR_ALLUMER);
    piloteIOT3_metA(INTERFACERGB_VALEUR_POUR_ETEINDRE);
    Serial.print("VERT \n");
    break;
    case INTERFACERGB_VALEUR_JAUNE:
    piloteIOT1_metA(INTERFACERGB_VALEUR_POUR_ALLUMER);
    piloteIOT2_metA(INTERFACERGB_VALEUR_POUR_ALLUMER);
    piloteIOT3_metA(INTERFACERGB_VALEUR_POUR_ETEINDRE);
    Serial.print("JAUNE \n");
    break;
    case INTERFACERGB_VALEUR_BLEUP:
    piloteIOT1_metA(INTERFACERGB_VALEUR_POUR_ALLUMER);
    piloteIOT2_metA(INTERFACERGB_VALEUR_POUR_ETEINDRE);
    piloteIOT3_metA(INTERFACERGB_VALEUR_POUR_ALLUMER);
    Serial.print("BLEU PALE \n");
    break; 
    case INTERFACERGB_VALEUR_MAUVE:
    piloteIOT1_metA(INTERFACERGB_VALEUR_POUR_ETEINDRE);
    piloteIOT2_metA(INTERFACERGB_VALEUR_POUR_ALLUMER);
    piloteIOT3_metA(INTERFACERGB_VALEUR_POUR_ALLUMER);
    Serial.print("MAUVE \n");
    break;
    case INTERFACERGB_VALEUR_BLANC:
    piloteIOT1_metA(INTERFACERGB_VALEUR_POUR_ALLUMER);
    piloteIOT2_metA(INTERFACERGB_VALEUR_POUR_ALLUMER);
    piloteIOT3_metA(INTERFACERGB_VALEUR_POUR_ALLUMER);
    Serial.print("BLANC \n");
    break;
  }
}

void interfaceRGB_changecouleur()
{
 if (interfaceRGB.RequeteActive == INTERFACERGB_INACTIVE)
 return;
 interfaceRGB_allumeCouleur(interfaceRGB.couleur);
 interfaceRGB.RequeteActive = INTERFACERGB_INACTIVE;
 serviceBaseDeTemps_execute[INTERFACERGB_PHASE] = interfaceRGB_changecouleur;
}
void interfaceRGB_initialise()
{
    interfaceRGB_eteintTous();
    interfaceRGB.RequeteActive = INTERFACERGB_INACTIVE;
    interfaceRGB.etatDuModule = INTERFACERGB_MODULE_PAS_EN_FONCTION;
    interfaceRGB.couleur =  INTERFACERGB_VALEUR_ETEINT;
    serviceBaseDeTemps_execute[INTERFACERGB_PHASE] = interfaceRGB_changecouleur;
}
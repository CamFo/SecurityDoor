/**
 * @file interfaceBuzzer.cpp
 * @author Ilyes Gharmoul (ilyesdu2002@hotmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-05-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <Arduino.h>
#include "main.h"
#include "piloteBuzzer.h"
#include "interfaceBuzzer.h"
#include "serviceBaseDeTemps.h"
#include "interfaceRGB.h"

#define INTERFACEBUZZER_COMPTE_2S (\
INTERFACEBUZZER_COMPTE_EN_MS * SERVICEBASEDETEMPS_FREQUENCE_EN_HZ \
  /250.0)
/**
 * @brief 1 seconde
 * 
 */
#define INTERFACEBUZZER_COMPTE_500mHz (\
INTERFACEBUZZER_COMPTE_EN_MS * SERVICEBASEDETEMPS_FREQUENCE_EN_HZ \
  /500.0)

/**
 * @brief 500 miliseconde
 * 
 */
#define INTERFACEBUZZER_COMPTE_1HZ (\
INTERFACEBUZZER_COMPTE_EN_MS * SERVICEBASEDETEMPS_FREQUENCE_EN_HZ \
  /1000.0)

/**
 * @brief 100 milisecondes
 * 
 */
#define INTERFACEBUZZER_COMPTE_5HZ (\
INTERFACEBUZZER_COMPTE_EN_MS * SERVICEBASEDETEMPS_FREQUENCE_EN_HZ \
  /5000.0)
/**
 * @brief 50 milisecondes
 * 
 */
#define INTERFACEBUZZER_COMPTE_10HZ (\
INTERFACEBUZZER_COMPTE_EN_MS * SERVICEBASEDETEMPS_FREQUENCE_EN_HZ \
  /10000.0)
/**
 * @brief 25 milisecondes
 * 
 */
#define INTERFACEBUZZER_COMPTE_20HZ (\
INTERFACEBUZZER_COMPTE_EN_MS * SERVICEBASEDETEMPS_FREQUENCE_EN_HZ \
  /20000.0)
/**
 * @brief 12.5 milisecondes
 * 
 */
#define INTERFACEBUZZER_COMPTE_40HZ (\
INTERFACEBUZZER_COMPTE_EN_MS * SERVICEBASEDETEMPS_FREQUENCE_EN_HZ \
  /40000.0)
/**
 * @brief 6.25 milisecondes
 * 
 */
#define INTERFACEBUZZER_COMPTE_80HZ (\
INTERFACEBUZZER_COMPTE_EN_MS * SERVICEBASEDETEMPS_FREQUENCE_EN_HZ \
  /80000.0)

#define INTERFACEBUZZER_COMPTE_160HZ (\
INTERFACEBUZZER_COMPTE_EN_MS * SERVICEBASEDETEMPS_FREQUENCE_EN_HZ \
  /160000.0)


INTERFACEBUZZER interfaceBuzzer;
unsigned int interfaceBuzzer_compteur;
unsigned int interfaceBuzzer_compteur2;
bool estate;
void interfaceBuzzer_switchState();

void interfaceBuzzer_switchState()
{
    if (estate == 0)
    {
    estate = 1;
    piloteBuzzer_metAUn();
    }
    else
    {
    estate = 0;
    piloteBuzzer_metAZero();
    }
}
void interfaceBuzzer_gestionFrequence()
{
    switch(interfaceBuzzer.valeurBruit)
    {
        case INTERFACEBUZZER_100POURCENT:
        //Serial.print("100");
        piloteBuzzer_metAUn();
        break;

        case INTERFACEBUZZER_75POURCENT:
        //Serial.print("75");
        interfaceBuzzer_compteur2++;
        if (interfaceBuzzer_compteur2 > INTERFACEBUZZER_COMPTE_20HZ)
        {
          interfaceBuzzer_switchState();
          interfaceBuzzer_compteur2 = 0;
        }
        break;

        case INTERFACEBUZZER_50POURCENT:
        //Serial.print("50");
        interfaceBuzzer_compteur2++;
        if(interfaceBuzzer_compteur2 > INTERFACEBUZZER_COMPTE_80HZ)
        {
          interfaceBuzzer_switchState();
          interfaceBuzzer_compteur2 = 0;
        }
        break;

        case INTERFACEBUZZER_25POURCENT:
        //Serial.print("25");
        interfaceBuzzer_compteur2++;
        if (interfaceBuzzer_compteur2 > INTERFACEBUZZER_COMPTE_160HZ)
        {
          interfaceBuzzer_switchState();
          interfaceBuzzer_compteur2 = 0;
        }
        break;
    }
    interfaceBuzzer_compteur++;
    if (interfaceBuzzer_compteur < interfaceBuzzer.dureeActive)
    {
        return;
    }

    interfaceBuzzer_compteur = 0; 
    interfaceBuzzer.etatDuModule = INTERFACEBUZZER_MODULE_PAS_EN_FONCTION;
    interfaceBuzzer.valeurBruit = INTERFACEBUZZER_AUCUNBRUIT;
    interfaceBuzzer.RequeteActive = INTERFACEBUZZER_INACTIVE;
    serviceBaseDeTemps_execute[INTERFACEBUZZER_PHASE] = interfaceBuzzerGestion;
}
void interfaceBuzzerGestion()
{
    piloteBuzzer_metAZero();
    if (interfaceBuzzer.RequeteActive == INTERFACEBUZZER_INACTIVE)
    return;
    switch (interfaceBuzzer.valeurBruit)
    {
      case INTERFACEBUZZER_AUCUNBRUIT:
      interfaceBuzzer.RequeteActive = INTERFACEBUZZER_INACTIVE;
      interfaceBuzzer.etatDuModule = INTERFACEBUZZER_MODULE_PAS_EN_FONCTION;
      return;
      break;
      case INTERFACEBUZZER_25POURCENT:
      interfaceBuzzer.etatDuModule = INTERFACEBUZZER_MODULE_EN_FONCTION;
      interfaceRGB.couleur = INTERFACERGB_VALEUR_BLANC;
      // Serial.print("50pourcent\n");
      serviceBaseDeTemps_execute[INTERFACEBUZZER_PHASE] = interfaceBuzzer_gestionFrequence;
      break;

      case INTERFACEBUZZER_50POURCENT:
      interfaceBuzzer.etatDuModule = INTERFACEBUZZER_MODULE_EN_FONCTION;
      interfaceRGB.couleur = INTERFACERGB_VALEUR_JAUNE;
      // Serial.print("50pourcent\n");
      serviceBaseDeTemps_execute[INTERFACEBUZZER_PHASE] = interfaceBuzzer_gestionFrequence;
      return;
      break;

      case INTERFACEBUZZER_75POURCENT:
      interfaceBuzzer.etatDuModule = INTERFACEBUZZER_MODULE_EN_FONCTION;
      interfaceRGB.couleur = INTERFACERGB_VALEUR_MAUVE;
      //Serial.print("75pourcent\n");
      serviceBaseDeTemps_execute[INTERFACEBUZZER_PHASE] = interfaceBuzzer_gestionFrequence;
      return;
      break;

      case INTERFACEBUZZER_100POURCENT:
      interfaceBuzzer.etatDuModule = INTERFACEBUZZER_MODULE_EN_FONCTION;
      interfaceRGB.couleur = INTERFACERGB_VALEUR_BLEUP;
      //Serial.print("100pourcent\n");
      serviceBaseDeTemps_execute[INTERFACEBUZZER_PHASE] = interfaceBuzzer_gestionFrequence;
      return;
      break;

      default:
      interfaceBuzzer.RequeteActive = INTERFACEBUZZER_INACTIVE;
      return;
      break;
    }
}
void interfaceBuzzer_initalise()
{
    interfaceBuzzer.etatDuModule = INTERFACEBUZZER_MODULE_PAS_EN_FONCTION;
    interfaceBuzzer.RequeteActive = INTERFACEBUZZER_INACTIVE;
    interfaceBuzzer.valeurBruit= INTERFACEBUZZER_AUCUNBRUIT;
    serviceBaseDeTemps_execute[INTERFACEBUZZER_PHASE] = interfaceBuzzerGestion;
}
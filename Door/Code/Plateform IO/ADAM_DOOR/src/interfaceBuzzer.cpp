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
#define INTERFACEBUZZER_COMPTE_1S (\
INTERFACEBUZZER_COMPTE_EN_MS * SERVICEBASEDETEMPS_FREQUENCE_EN_HZ \
  /500.0)
#define INTERFACEBUZZER_COMPTE_500MS (\
INTERFACEBUZZER_COMPTE_EN_MS * SERVICEBASEDETEMPS_FREQUENCE_EN_HZ \
  /1000.0)

#define INTERFACEBUZZER_COMPTE_100MS (\
INTERFACEBUZZER_COMPTE_EN_MS * SERVICEBASEDETEMPS_FREQUENCE_EN_HZ \
  /5000.0)
#define INTERFACEBUZZER_COMPTE_50MS (\
INTERFACEBUZZER_COMPTE_EN_MS * SERVICEBASEDETEMPS_FREQUENCE_EN_HZ \
  /10000.0)
#define INTERFACEBUZZER_COMPTE_25MS (\
INTERFACEBUZZER_COMPTE_EN_MS * SERVICEBASEDETEMPS_FREQUENCE_EN_HZ \
  /20000.0)


INTERFACEBUZZER interfaceBuzzer;
unsigned int interfaceBuzzer_compteur;


void interfaceBuzzer_gestionFrequence()
{
    switch(interfaceBuzzer.valeurBruit)
    {
        case INTERFACEBUZZER_100POURCENT:
        piloteBuzzer_metAUn();
        Serial.print("allume xd");
        interfaceBuzzer_compteur++;
        if (interfaceBuzzer_compteur < INTERFACEBUZZER_COMPTE_1S)
        {
            return;
        }
        interfaceBuzzer_compteur = 0;
        interfaceBuzzer.valeurBruit = INTERFACEBUZZER_AUCUNBRUIT;
 //       serviceBaseDeTemps_execute[INTERFACEBUZZER_PHASE] = interfaceBuzzerGestion;
        return;
        break;
        case INTERFACEBUZZER_50POURCENT:
        serviceBaseDeTemps_execute[INTERFACEBUZZER_PHASE] = interfaceBuzzerGestion;
        return;
        break;
        case INTERFACEBUZZER_75POURCENT:
        serviceBaseDeTemps_execute[INTERFACEBUZZER_PHASE] = interfaceBuzzerGestion;
        return;
        break;
    }
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
        return;
        break;

        case INTERFACEBUZZER_50POURCENT:
        serviceBaseDeTemps_execute[INTERFACEBUZZER_PHASE] = interfaceBuzzer_50pourcent;
        break;

        case INTERFACEBUZZER_75POURCENT:
        serviceBaseDeTemps_execute[INTERFACEBUZZER_PHASE] = interfaceBuzzer_75pourcent;
        break;

        case INTERFACEBUZZER_100POURCENT:
        serviceBaseDeTemps_execute[INTERFACEBUZZER_PHASE] = interfaceBuzzer_100pourcent;
        break;

        default:
        interfaceBuzzer.RequeteActive = INTERFACEBUZZER_INACTIVE;
        return;
        break;
    }
}
void interfaceBuzzer_50pourcent()
{
 interfaceRGB.couleur = INTERFACERGB_VALEUR_JAUNE;
// Serial.print("50pourcent\n");
 serviceBaseDeTemps_execute[INTERFACEBUZZER_PHASE] = interfaceBuzzer_gestionFrequence;
}
void interfaceBuzzer_75pourcent()
{
 interfaceRGB.couleur = INTERFACERGB_VALEUR_MAUVE;
 //Serial.print("75pourcent\n");
 serviceBaseDeTemps_execute[INTERFACEBUZZER_PHASE] = interfaceBuzzer_gestionFrequence;
}
void interfaceBuzzer_100pourcent()
{
 interfaceRGB.couleur = INTERFACERGB_VALEUR_BLEUP;
 //Serial.print("100pourcent\n");
 serviceBaseDeTemps_execute[INTERFACEBUZZER_PHASE] = interfaceBuzzer_gestionFrequence;
}

void interfaceBuzzer_initalise()
{
    interfaceBuzzer.etatDuModule = INTERFACEBUZZER_MODULE_PAS_EN_FONCTION;
    interfaceBuzzer.RequeteActive = INTERFACEBUZZER_INACTIVE;
    interfaceBuzzer.valeurBruit= INTERFACEBUZZER_AUCUNBRUIT;
    serviceBaseDeTemps_execute[INTERFACEBUZZER_PHASE] = interfaceBuzzerGestion;
}
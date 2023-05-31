/**
 * @file processusControlMoteur.cpp
 * @author Ilyes Gharmoul (ilyesdu2002@hotmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-05-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <Arduino.h>
#include "main.h"
#include "AnnexeADAM.h"
#include "piloteBuzzer.h"
#include "piloteESPNOW.h"
#include "piloteIOEA1.h"
#include "piloteIOM1.h"
#include "piloteIOM2.h"
#include "piloteIOT1.h"
#include "piloteIOT2.h"
#include "piloteIOT3.h"
#include "piloteIOIR1.h"
#include "piloteIOIR2.h"
#include "interfaceBuzzer.h"
#include "interfaceMoteur.h"
#include "interfaceRGB.h"
#include "interfaceInfrarouge.h"
#include "serviceBaseDeTemps.h"
#include "ServiceCommunication.h"
#include "processusControlMoteur.h"

#include <stdio.h>

//Definitions privees
#define PROCESSUSCONTROLMOTEUR_COMPTE_1S (\
PROCESSUSCONTROLMOTEUR_COMPTE_EN_MS * SERVICEBASEDETEMPS_FREQUENCE_EN_HZ \
  /500.0)

#define PROCESSUSCONTROLMOTEUR_COMPTE_2S (\
PROCESSUSCONTROLMOTEUR_COMPTE_EN_MS * SERVICEBASEDETEMPS_FREQUENCE_EN_HZ \
  /250.0)

#define PROCESSUSCONTROLMOTEUR_COMPTE_10S (\
PROCESSUSCONTROLMOTEUR_COMPTE_EN_MS * SERVICEBASEDETEMPS_FREQUENCE_EN_HZ \
  /50.0)

#define PROCESSUSCONTROLMOTEUR_COMPTE_30S (\
PROCESSUSCONTROLMOTEUR_COMPTE_EN_MS * SERVICEBASEDETEMPS_FREQUENCE_EN_HZ \
  /16.66)

#define PROCESSUSCONTROLMOTEUR_DEGREE_90 (\
PROCESSUSCONTROLMOTEUR_COMPTE_EN_MS * SERVICEBASEDETEMPS_FREQUENCE_EN_HZ \
  /700.0)

#define PROCESSUSCONTROLMOTEUR_DEGREE_180 (\
PROCESSUSCONTROLMOTEUR_COMPTE_EN_MS * SERVICEBASEDETEMPS_FREQUENCE_EN_HZ \
  /1500.0)



//Declarations de fonctions privees:
void processusControlMoteur_attenteCommande();
void processusControlMoteur_barreCommande();
void processusControlMoteur_debarreCommande();
void processusControlMoteur_attenteFinCommande();

// I want to see the world burn.
void processusControlMoteur_Barre_bloque();
void processusControlMoteur_Barre_bloquePAS();
void processusControlMoteur_Debarre_bloque();
void processusControlMoteur_Debarre_bloquePAS();

void loop1();
//Definitions de variables privees:
unsigned int processusGestionControlMoteur_compteur;
bool processusGestionMoteur_OldState;
//Definitions de fonctions privees:

void processusControlMoteur_attenteFinCommande()
{
  if (GestionCommuncation_R.ADAM_recu.porte_ADAM_receive.Commande != ANNEXEADAM_PORTE_ETATSERRURE_NULL)
  return;
  serviceBaseDeTemps_execute[PROCESSUSCONTROLMOTEUR_PHASE] = processusControlMoteur_attenteCommande;
}
void processusControlMoteur_attenteCommande()
{
  if (GestionCommuncation_R.ADAM_recu.porte_ADAM_receive.States > SERVICECOMMUNCATIIONR_STATE_ERREUR)
  {
    if (GestionCommuncation_R.ADAM_recu.porte_ADAM_receive.Commande == SERVICECOMMUNICATIONR_COMMANDE_DEBARRER) 
    {
    #ifdef PCM_OLDWAY
      serviceBaseDeTemps_execute[PROCESSUSCONTROLMOTEUR_PHASE] = processusControlMoteur_debarreCommande;
      return;
    #endif
    serviceBaseDeTemps_execute[PROCESSUSCONTROLMOTEUR_PHASE] = processusControlMoteur_Debarre_bloque;
    }
    else if (GestionCommuncation_R.ADAM_recu.porte_ADAM_receive.Commande == SERVICECOMMUNICATIONR_COMMANDE_BARRER)
    {
    #ifdef PCM_OLDWAY
      serviceBaseDeTemps_execute[PROCESSUSCONTROLMOTEUR_PHASE] = processusControlMoteur_barreCommande;
      return;
    #endif
    serviceBaseDeTemps_execute[PROCESSUSCONTROLMOTEUR_PHASE] = processusControlMoteur_Barre_bloque;
    }
  }
}

void processusControlMoteur_Barre_bloque()
{
  if (interfaceRGB.oldCouleur != INTERFACERGB_VALEUR_VERT)
  {
    interfaceRGB.RequeteActive = INTERFACERGB_ACTIVE;
    interfaceRGB.couleur = INTERFACERGB_VALEUR_VERT;
    interfaceRGB.dureeActive = PROCESSUSCONTROLMOTEUR_COMPTE_2S;
  }
  interfaceMoteur.dureeActive = PROCESSUSCONTROLMOTEUR_DEGREE_180;
  interfaceMoteur.RequeteActive = INTERFACEMOTEUR_ACTIVE;
  interfaceMoteur.direction = INTERFACEMOTEUR_DIRECTION_DROITE;
  serviceBaseDeTemps_execute[PROCESSUSCONTROLMOTEUR_PHASE] = processusControlMoteur_Barre_bloquePAS;
}

void processusControlMoteur_Barre_bloquePAS()
{
  if (interfaceMoteur.etatDuModule == INTERFACEMOTEUR_MODULE_EN_FONCTION)
    return;
  Serial.print("INTERFACEMOTEUR_MODULE_EN_FONCTION");
  interfaceMoteur.dureeActive = PROCESSUSCONTROLMOTEUR_DEGREE_180;
  interfaceMoteur.RequeteActive = INTERFACEMOTEUR_ACTIVE;
  interfaceMoteur.direction = INTERFACEMOTEUR_DIRECTION_GAUCHE;
  serviceBaseDeTemps_execute[PROCESSUSCONTROLMOTEUR_PHASE] = processusControlMoteur_attenteFinCommande;
}
void processusControlMoteur_Debarre_bloque()
{
  
  if (interfaceRGB.oldCouleur != INTERFACERGB_VALEUR_ROUGE)
  {
    interfaceRGB.RequeteActive = INTERFACERGB_ACTIVE;
    interfaceRGB.couleur = INTERFACERGB_VALEUR_ROUGE;
    interfaceRGB.dureeActive = PROCESSUSCONTROLMOTEUR_COMPTE_2S;
  }
  interfaceMoteur.dureeActive = PROCESSUSCONTROLMOTEUR_DEGREE_90;
  interfaceMoteur.RequeteActive = INTERFACEMOTEUR_ACTIVE;
  interfaceMoteur.direction = INTERFACEMOTEUR_DIRECTION_GAUCHE;
  serviceBaseDeTemps_execute[PROCESSUSCONTROLMOTEUR_PHASE] = processusControlMoteur_Debarre_bloquePAS;
}

void processusControlMoteur_Debarre_bloquePAS()
{

  if (interfaceMoteur.etatDuModule == INTERFACEMOTEUR_MODULE_EN_FONCTION)
    return;
  Serial.print("INTERFACEMOTEUR_MODULE_EN_FONCTION");
  interfaceMoteur.dureeActive = PROCESSUSCONTROLMOTEUR_DEGREE_90;
  interfaceMoteur.RequeteActive = INTERFACEMOTEUR_ACTIVE;
  interfaceMoteur.direction = INTERFACEMOTEUR_DIRECTION_DROITE;
  serviceBaseDeTemps_execute[PROCESSUSCONTROLMOTEUR_PHASE] = processusControlMoteur_attenteFinCommande;
}




void processusControlMoteur_barreCommande()
{
  if (interfaceRGB.oldCouleur != INTERFACERGB_VALEUR_ROUGE)
  {
    interfaceRGB.RequeteActive = INTERFACERGB_ACTIVE;
    interfaceRGB.couleur = INTERFACERGB_VALEUR_ROUGE;
    interfaceRGB.dureeActive = PROCESSUSCONTROLMOTEUR_COMPTE_2S;
  }
  interfaceMoteur.dureeActive =PROCESSUSCONTROLMOTEUR_COMPTE_2S;
  interfaceMoteur.RequeteActive = INTERFACEMOTEUR_ACTIVE;
  interfaceMoteur.direction = INTERFACEMOTEUR_DIRECTION_GAUCHE;
  serviceBaseDeTemps_execute[PROCESSUSCONTROLMOTEUR_PHASE] = processusControlMoteur_attenteCommande;
}
void processusControlMoteur_debarreCommande()
{
  if (interfaceRGB.oldCouleur != INTERFACERGB_VALEUR_VERT)
  {
    interfaceRGB.RequeteActive = INTERFACERGB_ACTIVE;
    interfaceRGB.couleur = INTERFACERGB_VALEUR_VERT;
    interfaceRGB.dureeActive = PROCESSUSCONTROLMOTEUR_COMPTE_2S;
  }
  interfaceMoteur.dureeActive =PROCESSUSCONTROLMOTEUR_COMPTE_2S;
  interfaceMoteur.RequeteActive = INTERFACEMOTEUR_ACTIVE;
  interfaceMoteur.direction = INTERFACEMOTEUR_DIRECTION_DROITE;
  serviceBaseDeTemps_execute[PROCESSUSCONTROLMOTEUR_PHASE] = processusControlMoteur_attenteCommande;
}
void loop1()
{

}
void processusControlMoteur_initialise()
{
  serviceBaseDeTemps_execute[PROCESSUSCONTROLMOTEUR_PHASE] = processusControlMoteur_attenteCommande;
}




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
//Declarations de fonctions privees:
void processusControlMoteur_attenteCommande();
void processusControlMoteur_barreCommande();
void processusControlMoteur_debarreCommande();
void loop1();
//Definitions de variables privees:
unsigned int processusGestionControlMoteur_compteur;
//Definitions de fonctions privees:

void processusControlMoteur_attenteCommande()
{
  processusGestionControlMoteur_compteur++;
  if (processusGestionControlMoteur_compteur < PROCESSUSCONTROLMOTEUR_COMPTE_2S)
  {
    return;
  }
  processusGestionControlMoteur_compteur = 0;
  if (GestionCommuncation_R.ADAM_recu.porte_ADAM_receive.States <= SERVICECOMMUNCATIION_STATE_ERREUR)
  {
    return; // (control dedier en presence seulement ou NFC si il y a lieu) 
  }
  else
  {
    if (GestionCommuncation_R.ADAM_recu.porte_ADAM_receive.Commande == SERVICECOMMUNICATION_COMMANDE_DEBARRER) //porte debarre value (idk ask cam)
    {
      serviceBaseDeTemps_execute[PROCESSUSCONTROLMOTEUR_PHASE] = processusControlMoteur_debarreCommande;
    }
      
    else if (GestionCommuncation_R.ADAM_recu.porte_ADAM_receive.Commande == SERVICECOMMUNICATION_COMMANDE_BARRER)
    {
      serviceBaseDeTemps_execute[PROCESSUSCONTROLMOTEUR_PHASE] = processusControlMoteur_barreCommande;
    }
      
  }
}
void processusControlMoteur_barreCommande()
{
  GestionCommuncation_T.ADAM_send.porte_ADAM_send.EtatSerrure = SERVICECOMMUNICATION_COMMANDE_BARRER;
  
  interfaceRGB.RequeteActive = INTERFACERGB_ACTIVE;
  interfaceRGB.couleur = INTERFACERGB_VALEUR_VERT;

  interfaceMoteur.requeteActive = INTERFACEMOTEUR_ACTIVE;
  interfaceMoteur.direction = INTERFACEMOTEUR_DIRECTION_GAUCHE;
  serviceBaseDeTemps_execute[PROCESSUSCONTROLMOTEUR_PHASE] = processusControlMoteur_attenteCommande;
}
void processusControlMoteur_debarreCommande()
{
  GestionCommuncation_T.ADAM_send.porte_ADAM_send.EtatSerrure = SERVICECOMMUNICATION_COMMANDE_DEBARRER;

  interfaceRGB.RequeteActive = INTERFACERGB_ACTIVE;
  interfaceRGB.couleur = INTERFACERGB_VALEUR_VERT;

  interfaceMoteur.requeteActive = INTERFACEMOTEUR_ACTIVE;
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




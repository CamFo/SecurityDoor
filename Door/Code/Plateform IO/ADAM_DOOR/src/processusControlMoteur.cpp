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
  if (GestionCommuncation_R.ADAM_recu.porte_ADAM_receive.States <= SERVICECOMMUNCATIIONR_STATE_ERREUR 
  || GestionCommuncation_R.ADAM_recu.porte_ADAM_receive.Commande == ANNEXEADAM_PORTE_ETATSERRURE_NULL)
  {
    if (GestionCommuncation_T.ADAM_send.porte_ADAM_send.Commande == SERVICECOMMUNICATIONR_COMMANDE_DEBARRER) 
      serviceBaseDeTemps_execute[PROCESSUSCONTROLMOTEUR_PHASE] = processusControlMoteur_debarreCommande;
      
    else if (GestionCommuncation_T.ADAM_send.porte_ADAM_send.Commande == SERVICECOMMUNICATIONR_COMMANDE_BARRER)
      serviceBaseDeTemps_execute[PROCESSUSCONTROLMOTEUR_PHASE] = processusControlMoteur_barreCommande;
  }
  else
  {
    if (GestionCommuncation_R.ADAM_recu.porte_ADAM_receive.Commande == SERVICECOMMUNICATIONR_COMMANDE_DEBARRER) 
      serviceBaseDeTemps_execute[PROCESSUSCONTROLMOTEUR_PHASE] = processusControlMoteur_debarreCommande;
      
    else if (GestionCommuncation_R.ADAM_recu.porte_ADAM_receive.Commande == SERVICECOMMUNICATIONR_COMMANDE_BARRER)
      serviceBaseDeTemps_execute[PROCESSUSCONTROLMOTEUR_PHASE] = processusControlMoteur_barreCommande;
  }
}
void processusControlMoteur_barreCommande()
{
  //GestionCommuncation_T.ADAM_send.porte_ADAM_send.EtatSerrure = SERVICECOMMUNICATION_COMMANDE_BARRER;
  if (interfaceRGB.oldCouleur != INTERFACERGB_VALEUR_ROUGE)
  {
    interfaceRGB.RequeteActive = INTERFACERGB_ACTIVE;
    interfaceRGB.couleur = INTERFACERGB_VALEUR_ROUGE;
    interfaceRGB.dureeActive = PROCESSUSCONTROLMOTEUR_COMPTE_2S;
  }
  interfaceMoteur.RequeteActive = INTERFACEMOTEUR_ACTIVE;
  interfaceMoteur.direction = INTERFACEMOTEUR_DIRECTION_GAUCHE;
  serviceBaseDeTemps_execute[PROCESSUSCONTROLMOTEUR_PHASE] = processusControlMoteur_attenteCommande;
}
void processusControlMoteur_debarreCommande()
{
  //GestionCommuncation_T.ADAM_send.porte_ADAM_send.EtatSerrure = SERVICECOMMUNICATION_COMMANDE_DEBARRER; //devrais etre dans un autre processus
  if (interfaceRGB.oldCouleur != INTERFACERGB_VALEUR_VERT)
  {
    interfaceRGB.RequeteActive = INTERFACERGB_ACTIVE;
    interfaceRGB.couleur = INTERFACERGB_VALEUR_VERT;
    interfaceRGB.dureeActive = PROCESSUSCONTROLMOTEUR_COMPTE_2S;
  }
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




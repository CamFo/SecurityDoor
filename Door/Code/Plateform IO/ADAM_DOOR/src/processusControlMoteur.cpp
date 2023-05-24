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
void processusGestionPairing_AttenteCommande();
//Definitions de variables privees:
unsigned int processusGestionControlMoteur_compteur;
//Definitions de fonctions privees:

void processusGestionPairing_AttenteCommande()
{
  processusGestionControlMoteur_compteur++;
  if (processusGestionControlMoteur_compteur < PROCESSUSCONTROLMOTEUR_COMPTE_2S)
  {
    return;
  }
  if (GestionCommuncation_R.ADAM_recu.porte_ADAM_receive.ValueRA <= SERVICECOMMUNCATIION_STATE_ERREUR)
  return; // (control dedier a Gestion_R_porteAdam.), sinon fait manuellement avec Transmit.
  if (GestionCommuncation_R.ADAM_recu.porte_ADAM_receive.Commande == SERVICECOMMUNICATION_COMMANDE_DEBARRER) //porte debarre value (idk ask cam)
  {
    GestionCommuncation_T.ADAM_send.porte_ADAM_send.EtatSerrure = SERVICECOMMUNICATION_COMMANDE_DEBARRER;
    interfaceMoteur.RequeteActive = INTERFACEMOTEUR_ACTIVE;
    interfaceRGB.RequeteActive = INTERFACERGB_ACTIVE;
    interfaceRGB.couleur = INTERFACERGB_VALEUR_VERT;
    interfaceMoteur.direction = INTERFACEMOTEUR_DIRECTION_DROITE;
  }
  else if (GestionCommuncation_R.ADAM_recu.porte_ADAM_receive.ValueRA == SERVICECOMMUNICATION_COMMANDE_BARRER)
  {
    GestionCommuncation_T.ADAM_send.porte_ADAM_send.EtatSerrure = SERVICECOMMUNICATION_COMMANDE_BARRER;
    interfaceMoteur.RequeteActive = INTERFACEMOTEUR_ACTIVE;
    interfaceRGB.RequeteActive = INTERFACERGB_ACTIVE;
    interfaceRGB.couleur = INTERFACERGB_VALEUR_VERT;
    interfaceMoteur.direction = INTERFACEMOTEUR_DIRECTION_GAUCHE;
  }
}
void loop1();
void loop1()
{
   if (GestionCommuncation_R.ADAM_recu.porte_ADAM_receive.Commande == 17)//SERVICECOMMUNICATION_COMMANDE_DEBARRER) //porte debarre value (idk ask cam)
  {
    interfaceMoteur.RequeteActive = INTERFACEMOTEUR_ACTIVE;
    interfaceRGB.RequeteActive = INTERFACERGB_ACTIVE;
    interfaceRGB.couleur = INTERFACERGB_VALEUR_VERT;
    interfaceMoteur.direction = INTERFACEMOTEUR_DIRECTION_DROITE;
  }
  else if (GestionCommuncation_R.ADAM_recu.porte_ADAM_receive.Commande == SERVICECOMMUNICATION_COMMANDE_BARRER)
  {
    interfaceMoteur.RequeteActive = INTERFACEMOTEUR_ACTIVE;
    interfaceRGB.RequeteActive = INTERFACERGB_ACTIVE;
    interfaceRGB.couleur = INTERFACERGB_VALEUR_VERT;
    interfaceMoteur.direction = INTERFACEMOTEUR_DIRECTION_GAUCHE;
  }
}
void processusControlMoteur_initialise()
{
  serviceBaseDeTemps_execute[PROCESSUSCONTROLMOTEUR_PHASE] = processusGestionPairing_AttenteCommande;
}




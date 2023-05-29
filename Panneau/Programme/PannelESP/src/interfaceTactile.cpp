/**
 * @file interfaceTactile.ino
 * @author Camille Fortin 
 * @brief Interface qui permet de lire et de débouncer la switch
 * @version 0.1
 * @date 2023-05-03
 * 
 * @copyright Copyright (c) 2023
 * 
 */

//INCLUSIONS
#include "main.h"
#include "FT6236.h"
#include "serviceBaseDeTemps.h"
#include "interfaceTactile.h"
#include "ServiceCommunication.h"
#include "piloteESPNOWCapteur.h"
#include "piloteESPNOWDoor.h"


//Definitions privees
INTERFACETACTILE interfaceTactile;


//Declarations de fonctions privees:
void interfaceTactile_gere(void);
void interfaceTactile_detecteBoutton(void);

//Definitions de variables privees:
FT6236 ts = FT6236();
TS_Point p;

unsigned int interfaceTactile_compteurAvantLecture;

//Definitions de fonctions privees:
void interfaceTactile_detecteBoutton(void)
{
  // Retrieve a point
  p = ts.getPoint();

  if(p.x >= 80 && p.x <= 150)  // Si on est entre 80 et 150 X
  {
    if(p.y >= 360 && p.y <= 460)
    {
       interfaceTactile.etatBouttonDebarre = false;
      interfaceTactile.etatBouttonBarre = true;
      ValeurEnvoieDoor.Commande = SERVICECOMMUNICATION_COMMANDE_BARRER;
      //Serial.println("BARRE");
    }
    if(p.y >= 240 && p.y <= 360)
    {
      interfaceTactile.etatBouttonBarre = false;
      interfaceTactile.etatBouttonDebarre = true;
      ValeurEnvoieDoor.Commande = SERVICECOMMUNICATION_COMMANDE_DEBARRER;
      //Serial.println("DEBARRE");
    }
  }

  interfaceTactile.x = p.x;
  interfaceTactile.y = p.y;
  interfaceTactile.etatDuModule = INTERFACETACTILE_MODULE_EN_FONCTION;
}

void interfaceTactile_gere(void)
{
  interfaceTactile_compteurAvantLecture++;
  if (interfaceTactile_compteurAvantLecture < 4) // Compte avant lecture a 4 x la base de temps
  {
    return;
  }
  interfaceTactile_compteurAvantLecture = 0;

  if (ts.touched())
  {
    ValeurEnvoieDoor.States = SERVICECOMMUNICATION_STATE_OPERATION;
    ValeurEnvoieCapteur.States = SERVICECOMMUNICATION_STATE_OPERATION;
    interfaceTactile_detecteBoutton();
    interfaceTactile.information = INTERFACETACTILE_INFORMATION_DISPONIBLE;
    interfaceTactile.etatDeLEntree = INTERFACETACTILE_ACTIVE;
  }
    
  interfaceTactile.etatDeLEntree = INTERFACETACTILE_INACTIVE;   // Entré inactive car il n'as pas de détection présentement
}

//Definitions de fonctions publiques:
void interfaceTactile_initialise(void)
{
  interfaceTactile.etatDuModule = INTERFACETACTILE_MODULE_PAS_EN_FONCTION;
  interfaceTactile.information = INTERFACETACTILE_INFORMATION_TRAITEE;
  interfaceTactile.etatDeLEntree = INTERFACETACTILE_PAS_EN_FONCTION;
	interfaceTactile_compteurAvantLecture = 0;

  ts.begin(40, PILOTEI2C1_SDA, PILOTEI2C1_SCL);  // Démarrage de la communication I2C

  serviceBaseDeTemps_execute[INTERFACETACTILE_PHASE] = interfaceTactile_gere;
}

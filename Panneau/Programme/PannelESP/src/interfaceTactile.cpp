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


//Definitions privees

//Declarations de fonctions privees:
void interfaceTactile_gere(void);
void interfaceTactile_detectePave(void);

//Definitions de variables privees:
FT6236 ts = FT6236();

unsigned int interfaceTactile_compteurAvantLecture;

//Definitions de fonctions privees:
void interfaceTactile_detectePave(void)
{

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
    // Retrieve a point
    TS_Point p = ts.getPoint();

    // Print coordinates to the serial output
    Serial.print("X Coordinate: ");
    Serial.println(p.x);
    Serial.print("Y Coordinate: ");
    Serial.println(p.y);

    interfaceTactile.x = p.x;
    interfaceTactile.y = p.y;
    interfaceTactile.information = INTERFACETACTILE_INFORMATION_DISPONIBLE;
    interfaceTactile.etatDeLEntree = INTERFACETACTILE_ACTIVE;
  }
    
  interfaceTactile.etatDeLEntree = INTERFACETACTILE_INACTIVE;   // Entré inactive car il n'as pas de détection présentement
}

//Definitions de variables publiques:
INTERFACETACTILE interfaceTactile;

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

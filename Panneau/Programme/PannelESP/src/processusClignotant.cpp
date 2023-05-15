//processusClignotant:
//Historique: 
// 2023-05-03, Camille Fortin

//INCLUSIONS
#include "main.h"
#include "interfaceT1.h"

#include "serviceBaseDeTemps.h"
#include "processusClignotant.h"
#include "piloteESPNOW.h"
#include <stdio.h>

//Definitions privees
#define PROCESSUSCLIGNOTANT_COMPTE_POUR_ALLUME (\
  PROCESSUSCLIGNOTANT_TEMPS_ALLUME_EN_MS * SERVICEBASEDETEMPS_FREQUENCE_EN_HZ \
  /1000.0)

#define PROCESSUSCLIGNOTANT_COMPTE_POUR_ETEINDRE  (\
  PROCESSUSCLIGNOTANT_TEMPS_ETEINT_EN_MS * SERVICEBASEDETEMPS_FREQUENCE_EN_HZ \
  /1000.0)
   
//Declarations de fonctions privees:
//pas de fonction privees

//Definitions de variables privees:
unsigned long processusClignotant_compteur;

//Definitions de fonctions privees:
void processusClignotant_attendAvantDAllumerLeTemoinLumineux(void);
void processusClignotant_attendAvantDEteindreLeTemoinLumineux(void);

//Definitions de variables publiques:
//pas de variables publiques

//Definitions de fonctions publiques:
void processusClignotant_attendAvantDAllumerLeTemoinLumineux(void)
{
  processusClignotant_compteur++;
  if (processusClignotant_compteur < PROCESSUSCLIGNOTANT_COMPTE_POUR_ALLUME)
  {
    return;
  }
  // Test Code Go here
  unsigned char adr[] = {0xC4, 0xDD, 0x57, 0x9C, 0xD3, 0x6C};   //  FeatherMAC  C4:DD:57:9C:D3:6C         PanneauMAC  70:B8:F6:F0:C6:B0  0x70, 0xB8, 0xF6, 0xF0, 0xC6, 0xB0
  piloteESPNOW_send(adr);
  // END test Code 
  interfaceT1_allume();
  processusClignotant_compteur = 0;
  serviceBaseDeTemps_execute[PROCESSUSCLIGNOTANT_PHASE] = processusClignotant_attendAvantDEteindreLeTemoinLumineux;
}

void processusClignotant_attendAvantDEteindreLeTemoinLumineux(void)
{ 
  processusClignotant_compteur++;
  if (processusClignotant_compteur < PROCESSUSCLIGNOTANT_COMPTE_POUR_ETEINDRE)
  {
    return;
  }

  interfaceT1_eteint();
  processusClignotant_compteur = 0;
  serviceBaseDeTemps_execute[PROCESSUSCLIGNOTANT_PHASE] = processusClignotant_attendAvantDAllumerLeTemoinLumineux;
}

void processusClignotant_initialise(void)
{
  processusClignotant_compteur = 0;
  interfaceT1_eteint();
  serviceBaseDeTemps_execute[PROCESSUSCLIGNOTANT_PHASE] = processusClignotant_attendAvantDAllumerLeTemoinLumineux;
}

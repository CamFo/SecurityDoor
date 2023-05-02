//*****
//
// Nom: Pilote I2C pour le projet ADAM
// Materiel: ADAM_BACKDOOR ADAM_FRONTDOOR NFC RFID PN523
// Créé par: Ilyes Gharmoul
// Crée le: 2023-05-02
//
// Description: Pïlote pour le protocle I2C du projet Adam
// Version 1: Implementation du pilote I2C pour le fonctionnement du PN523 sur les pins 23 et 27 
//
//*****
#include "AD_D_PILOTEI2C.h"

TwoWire TwoWireI2C1;





void PiloteI2C::PiloteI2C_BeginI2C()
{
  TwoWireI2C1.begin(SDA,SCL,I2C1_SPEED);
}





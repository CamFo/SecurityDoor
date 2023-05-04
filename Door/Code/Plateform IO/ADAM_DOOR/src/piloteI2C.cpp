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
#include <Arduino.h>
#include <Wire.h>
#include "main.h"
#include "piloteI2C.h"

TwoWire I2C1 = TwoWire(0);

void piloteI2C1_initialise()
{
 I2C1.begin(SDA1,SCL1,FREQ1);
}

unsigned char piloteI2C1_lisUnOctet(unsigned char Adr)
{
  I2C1.requestFrom((uint8_t)Adr,(uint8_t)1);
  return I2C1.read();
}
uint8_t piloteI2C1_appelAuChip(unsigned char Adr,bool active)
{
  I2C1.beginTransmission((uint8_t)Adr);
  return I2C1.endTransmission(active);
}
uint8_t piloteI2C1_ecritUnOctet(unsigned int Adr,unsigned char Msg,bool active)
{
  I2C1.beginTransmission((uint8_t)Adr);
  I2C1.write((uint8_t)Msg);
  return I2C1.endTransmission(active);
}
unsigned int piloteI2C1_lisUnEntier(unsigned char Adr)
{
  I2C1.requestFrom((uint8_t)Adr, (uint8_t)2);
  return (unsigned int)(I2C1.read() | (((unsigned int)I2C1.read()) << 8));   
}



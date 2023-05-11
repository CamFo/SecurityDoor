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
/**
 * @brief Initialisateur de PiloteI2C1, utilise la classe TwoWire de arduino ("wire.h") pour definir les pins I2Cs et la fréquence d'oscillation
 * 
 */
void piloteI2C1_initialise()
{
 I2C1.begin(SDA1,SCL1,FREQ1);
}
/**
 * @brief ecrit en I2C l'adresse d'une chip et annule la communication, utilise pour verifier la présence d'un chip.
 * 
 * @param Adr 
 * @param active 
 * @return uint8_t 
 */
uint8_t piloteI2C1_appelAuChip(unsigned int Adr,bool active)
{
  I2C1.beginTransmission((uint8_t)Adr);
  return I2C1.endTransmission(active);
}
/**
 * @brief lis directement un adresse sans ecrire l'adresse physique d'un chip (pour des tests, n'est pas applicable dans une vraie lecture I2C)
 * 
 * @param Adr 
 * @return unsigned char 
 */
unsigned char piloteI2C1_lisUnOctet(unsigned int Adr)
{
  if (I2C1.requestFrom((uint8_t)Adr,(uint8_t)1) == -1)
  {
    Serial.print("err");
  }
  return (unsigned char) I2C1.read();
}
/**
 * @brief Lis un octet au complet à l'adresse d'un registre
 * 
 * @param Adr 
 * @return unsigned int 
 */
unsigned int piloteI2C1_lisUnEntier(unsigned char Adr)
{
  I2C1.requestFrom((uint8_t)Adr, (uint8_t)2);
  return (unsigned int)(I2C1.read() | (((unsigned int)I2C1.read()) << 8));   
}
/**
 * @brief Ecrit à l'adresse d'un registre de une chip et ecrit à son registre un message de un octet
 * 
 * @param Adr 
 * @param Msg 
 * @param active 
 * @return uint8_t 
 */
uint8_t piloteI2C1_ecritUnByte(unsigned int Adr,unsigned char Msg,bool active)
{
  I2C1.beginTransmission((uint8_t)Adr);
  I2C1.write((uint8_t)Msg);
  return I2C1.endTransmission(active);
}


/**
 * @brief Ecrit un octet au complet (2 bytes) à une adresse
 * 
 * @param Adr 
 * @param Msg 
 * @param active 
 * @return uint8_t 
 */
uint8_t piloteI2C1_ecritUnOctet(unsigned int Adr,unsigned char Msg,bool active)
{
  I2C1.beginTransmission((uint8_t)Adr);
  I2C1.write((unsigned char)(Msg >> 8));
  I2C1.write((unsigned char)(Msg & 0xFF));
  return I2C1.endTransmission();  
}
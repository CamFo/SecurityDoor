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


#ifndef PILOTEI2C_H
#define PILOTEI2C_H


  
void piloteI2C1_initialise();
unsigned char piloteI2C1_lisUnOctet(unsigned char);
uint8_t piloteI2C1_appelAuChip(unsigned int,bool);
uint8_t piloteI2C1_ecritUnByte(unsigned int Adr,unsigned char Msg,bool active);
unsigned int piloteI2C1_lisUnEntier(unsigned char);


#endif
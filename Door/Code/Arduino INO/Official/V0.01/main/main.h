//***********************************************************************************************************
//
// Nom: main.h
// Materiel: ADAM_BACKDOOR ADAM_FRONTDOOR NFC RFID PN523
// Créé par: Ilyes Gharmoul
// Crée le: 2023-05-02
//
// Description: Fichier interactible pour utiliser les fonctions disponible sur le matériel.
//              Ses fonctions comprennent:
//                  * utiliser plusieurs bus I2C
//                  *
// Version 1: Implementation du pilote I2C pour le fonctionnement du PN523 sur les pins 23 et 27 
//
//***********************************************************************************************************


#ifdef MAIN_H
#define MAIN_H
//***************************************************  NFC  *************************************************    
//**************I2C*******************

#define I2C_ADR_NFC (0x24);

//***************************************************BUS I2C*************************************************    

#define BUS_I2C1 
#define I2C1_SPEED 100000;
#define I2C1_SDA   (23);
#define I2C1_SCL   (27);

//#define BUS_I2C2
//#define BUS_I2C3

#endif
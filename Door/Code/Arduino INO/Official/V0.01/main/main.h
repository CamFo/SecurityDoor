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


#ifndef MAIN_H
#define MAIN_H
//**************************************************  PHASES  ***********************************************    

#define SERVICEBASEDETEMPS_NOMBRE_DE_PHASES_DANS_LOOP 1
#define SERVICEBASEDETEMPS_NOMBRE_DE_PHASES 1


//**************I2C*******************

#define I2C_ADR_NFC (0x24)

//***************************************************BUS I2C*************************************************    

#define BUS_I2C1 
#define FREQ1 100000
#define SDA1   (23)
#define SCL1   (27)

//#define BUS_I2C2
//#define BUS_I2C3
#define TRUE true
#endif
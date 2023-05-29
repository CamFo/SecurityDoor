#ifndef INTERFACEPN523_H
#define INTERFACEPN523_H

//MODULE: INTERFACEPN523
//DESCRIPTION: Pour interfacer avec le module PN523, un capteur NFC 
//             faisait de la communication HUART, SPI ou NFC.
//             
//la frequence INTERFACEPN523_FREQUENCE_DES_LECTURES_EN_HZ
//Le nombre minimum de lectures est donne par
//INTERFACEPN523_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION

//HISTORIQUE:
// 2023-05-05 Ilyes G

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")


//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define INTERFACEPN523_PHASE 0



//INFORMATION PUBLIQUE:
//Definitions publiques:

#define INTERFACEPN523_MODULE_EN_FONCTION 1
#define INTERFACEPN523_MODULE_PAS_EN_FONCTION 0
#define INTERFACEPN523_INFORMATION_DISPONIBLE 1
#define INTERFACEPN523_INFORMATION_TRAITEE 0
#define INTERFACEPN523_INACTIVE 0
#define INTERFACEPN523_ACTIVE  1
#define INTERFACEPN523_PAS_EN_FONCTION 2

typedef struct
{
  unsigned char etatDuModule;  
  unsigned char information;
  unsigned char etatDeLecture;
} INTERFACEPN523;

extern INTERFACEPN523 interfacePN523;

//Fonctions publiques:
void interfacePN523_initalise();



#endif

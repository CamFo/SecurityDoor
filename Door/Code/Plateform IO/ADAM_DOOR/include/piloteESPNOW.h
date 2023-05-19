/**
 * @file piloteESPNOW.h
 * @author Camille Fortin (camfortin2022@gmail.com)
 * @author Ilyes Gharmoul (ilyesgharmoul@hotmail.com)
 * @brief 
 * @version 0.2
 * @date 2023-05-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "AnnexeADAM.h"
#ifndef PILOTEESPNOW_H
#define PILOTEESPNOW_H

// DEFINE a mettre dans le main
#define PILOTEESPNOW_CHANNEL 0

#define PILOTEESPNOW_INFORMATION_DISPONIBLE 1
#define PILOTEESPNOW_INFORMATION_TRAITEE 0
#define PILOTEESPNOW_MODULE_EN_FONCTION 1
#define PILOTEESPNOW_MODULE_PAS_EN_FONCTION 0

// Variable publique

/// @brief Structure public qui permet de savoir et de changer l'état du module  
typedef struct
{
  unsigned char etatDuModule;
  unsigned char information;

} PILOTEESPNOW;
extern PILOTEESPNOW piloteESPNOW;


// Structure d'envoie et de réception
typedef struct
{
    unsigned char States;
    unsigned char Commande;
    unsigned char ValueSA;
    unsigned char ValueSB;    
    unsigned char ValueSC;
    
}STSEND;

typedef struct 
{
    unsigned char States;
    unsigned char Commande;
    unsigned char ValueRA;
    unsigned char ValueRB;
    unsigned char ValueRC;

}STRECEIVE;

typedef union
{
  STSEND piloteValueEnvoie;
  UNIONADAM_S ADAM_send;
}STRUCTURECOMMUNCATION_T;

typedef union
{
  STRECEIVE piloteValueReceive;
  UNIONADAM_R ADAM_recu;
}STRUCTURECOMMUNCATION_R;

extern STRUCTURECOMMUNCATION_R GestionCommuncation_R;
extern STRUCTURECOMMUNCATION_T GestionCommuncation_T;

//Fonctions publiques:


void piloteESPNOW_initialise(void);
void piloteESPNOW_Pair(void);
void piloteESPNOW_send(void);


// ##############  STRUCTURE DE RÉFÉRENCE ################



#endif
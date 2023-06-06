/**
 * @file piloteESPNOWDoor.h
 * @author Camille Fortin (camfortin2022@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-05-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef PILOTEESPNOWDOOR_H
#define PILOTEESPNOWDOOR_H

// DEFINE a mettre dans le main
#define PILOTEESPNOWDOOR_CHANNEL 0

#define PILOTEESPNOWDOOR_INFORMATION_DISPONIBLE 1
#define PILOTEESPNOWDOOR_INFORMATION_TRAITEE 0
#define PILOTEESPNOWDOOR_MODULE_EN_FONCTION 1
#define PILOTEESPNOWDOOR_MODULE_PAS_EN_FONCTION 0

// Variable publique

/// @brief Structure public qui permet de savoir et de changer l'état du module  
typedef struct
{
  unsigned char etatDuModule;
  unsigned char information;

} PILOTEESPNOWDOOR;
extern PILOTEESPNOWDOOR piloteESPNOWDoor;


// Structure de réception pour enregistrer les informations recu de la porte
typedef struct
{
    unsigned char States;
    unsigned char Commande;
    unsigned char EtatPorte;
    unsigned char UserNFC;    
    unsigned char EtatSerrure;
    
}DOOR_ADAM_R;

// Structure d'envoie à la porte 
typedef struct 
{
    unsigned char States;
    unsigned char Commande;
    unsigned char ValeurA;
    unsigned char ValeurB;
    unsigned char ValeurC;

}DOOR_ADAM_S;

extern DOOR_ADAM_R ValeurRecuDoor;
extern DOOR_ADAM_S ValeurEnvoieDoor;

//Fonctions publiques:

void piloteESPNOWDoor_initialise(void);
void piloteESPNOWDoor_Pair(void);
void piloteESPNOWDoor_send(void);


// ##############  STRUCTURE DE RÉFÉRENCE ################



#endif
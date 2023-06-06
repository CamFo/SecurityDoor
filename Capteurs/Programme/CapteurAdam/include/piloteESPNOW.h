/**
 * @file piloteESPNOW.h
 * @author Camille Fortin (camfortin2022@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-05-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */

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


// Structure de réception pour enregistrer les informations recu du Capteur
typedef struct
{
    unsigned char States;
    unsigned char Commande;
    unsigned char Temperature;
    unsigned char Humiditee;    
    unsigned char Motion;
    
}CAPTEUR_ADAM_R;

//Structure d'envoie au capteur
typedef struct 
{
    unsigned char States;
    unsigned char Commande;
    unsigned char ValeurA;
    unsigned char ValeurB;
    unsigned char ValeurC;

}CAPTEUR_ADAM_S;


extern CAPTEUR_ADAM_R ValeurRecuCapteur;
extern CAPTEUR_ADAM_S ValeurEnvoieCapteur;

//Fonctions publiques:


void piloteESPNOW_initialise(void);
void piloteESPNOW_Pair(void);
void piloteESPNOW_send(void);


// ##############  STRUCTURE DE RÉFÉRENCE ################



#endif
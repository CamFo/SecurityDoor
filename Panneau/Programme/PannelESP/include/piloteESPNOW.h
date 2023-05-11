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

#ifndef PILOTEESPNOW
#define PILOTEESPNOW

// DEFINE a mettre dans le main
//#define ADREESSMAC_DOOR

// Variable publique
unsigned char broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

// Structure d'envoie et de réception
typedef struct
{
    unsigned char States;
    unsigned char Commande;
    unsigned char ValeurA;
    unsigned char ValeurB;    
    unsigned char ValeurC;
    
}stSend;
stSend ValueEnvoie;

typedef struct 
{
    unsigned char States;
    unsigned char Commande;
    unsigned char ValeurA;
    unsigned char ValeurB;
    unsigned char ValeurC;

}stReceived;
stReceived ValueRecu;

//Fonctions publiques:


void piloteESPNOW_initialise(void);
void piloteESPNOW_send(void);


// ##############  STRUCTURE DE RÉFÉRENCE ################



#endif
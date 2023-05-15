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
//#define ADREESSMAC_DOOR

// Variable publique


// Structure d'envoie et de réception
typedef struct
{
    unsigned char States;
    unsigned char Commande;
    unsigned char ValeurA;
    unsigned char ValeurB;    
    unsigned char ValeurC;
    
}stSend;
extern stSend ValueEnvoie;

typedef struct 
{
    unsigned char States;
    unsigned char Commande;
    unsigned char ValeurA;
    unsigned char ValeurB;
    unsigned char ValeurC;

}stReceived;
extern stReceived ValueRecu;

//Fonctions publiques:


void piloteESPNOW_initialise(void);
void piloteESPNOW_Pair(unsigned char adresse[]);
void piloteESPNOW_send(unsigned char adresse[]);


// ##############  STRUCTURE DE RÉFÉRENCE ################



#endif
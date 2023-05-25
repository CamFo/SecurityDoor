/**
 * @file AnnexeADAM.h
 * @author Ilyes Gharmoul (ilyesdu2002@hotmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-05-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef ANNEXEADAM_H
#define ANNEXEADAM_H

#define ANNEXEADAM_PORTE_ETATSERRURE_OUVERTE 0
#define ANNEXEADAM_PORTE_ETATSERRURE_FERME   1

#define SERVICECOMMUNICATION_FAILVALUE        0xFF
#define SERVICECOMMUNICATION_STATE_OPERATION  0x08
#define SERVICECOMMUNICATION_STATE_ENARRET    0x09
#define SERVICECOMMUNCATIION_STATE_ERREUR     0x07
//State

#define SERVICECOMMUNICATION_COMMANDE_BARRER   0x10
#define SERVICECOMMUNICATION_COMMANDE_DEBARRER 0x11


// Structure d'envoie et de réception
typedef struct
{
    unsigned char States; // en arret operation erreur 
    unsigned char Commande; // RIEN
    unsigned char EtatPorte; // ouvert fermer
    unsigned char UserNFC;    // dernier user nfc ou 0
    unsigned char EtatSerrure; // barrer debarrer
    
}PORTE_ADAM_S;

typedef struct
{
    unsigned char States;
    unsigned char Commande;
    unsigned char ValueSA;
    unsigned char ValueSB;    
    unsigned char ValueSC;
    
}CAPTEUR_ADAM_S;

typedef struct
{
    unsigned char States;
    unsigned char Commande;
    unsigned char ValueSA;
    unsigned char ValueSB;    
    unsigned char ValueSC;
    
}PANNEAU_ADAM_S;

typedef struct 
{
    unsigned char States;   // operation pas en operation ou erreur
    unsigned char Commande; // barrer debarrer
    unsigned char UnusedA;
    unsigned char UnusedB;
    unsigned char UnusedC;

}PORTE_ADAM_R;

typedef struct 
{
    unsigned char States;   
    unsigned char Commande; 
    unsigned char ValueRA;
    unsigned char ValueRB;
    unsigned char ValueRC;

}CAPTEUR_ADAM_R;

typedef struct 
{
    unsigned char States;
    unsigned char Commande;
    unsigned char ValueRA;
    unsigned char ValueRB;
    unsigned char ValueRC;

}PANNEAU_ADAM_R;

typedef union
{
    /* data */
    PORTE_ADAM_S porte_ADAM_send;
    CAPTEUR_ADAM_S capteur_ADAM_send;
    PANNEAU_ADAM_S panneau_ADAM_send;
    unsigned char tampon[5];
}UNIONADAM_S;

typedef union
{
    /* data */
    PORTE_ADAM_R porte_ADAM_receive;
    CAPTEUR_ADAM_R capteur_ADAM_receive;
    PANNEAU_ADAM_R panneau_ADAM_receive;
    unsigned char tampon[5];
}UNIONADAM_R;

//Fonctions publiques:

#endif
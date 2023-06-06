/**
 * @file processusPanneau.h
 * @author Camille Fortin (camfortin2022@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-05-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef PROCESSUSPANNEAU_H
#define PROCESSUSPANNEAU_H


#define PROCESSUSPANNEAU_REQUETE_ACTIVE 0x01
#define PROCESSUSPANNEAU_REQUETE_TRAITEE 0x00
#define PROCESSUSPANNEAU_MODULE_EN_FONCTION 0x01
#define PROCESSUSPANNEAU_MODULE_PAS_EN_FONCTION 0x00
#define PROCESSUSPANNEAU_INFORMATION_DISPONIBLE 0x01
#define PROCESSUSPANNEAU_INFORMATION_INDISPONIBLE 0x00


typedef struct
{
  unsigned char etatDuModule;  
  unsigned char information;
  unsigned char requete;
} PROCESSUSPANNEAU;

extern PROCESSUSPANNEAU processusPanneau;

void processusPanneau_initialise(void);


#endif
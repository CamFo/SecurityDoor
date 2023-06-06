/**
 * @file processusAffichage.h
 * @author Camille Fortin (camfortin2022@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-05-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef PROCESSUSAFFICHAGE_H
#define PROCESSUSAFFICHAGE_H

typedef struct
{
    bool etatArmement;
    unsigned int compteurArm;
    bool chiffreAffichee = false;
}
PROCESSUSAFFICHAGE;

extern PROCESSUSAFFICHAGE processusAffichage;

void processusAffichage_initialise(void);


#endif
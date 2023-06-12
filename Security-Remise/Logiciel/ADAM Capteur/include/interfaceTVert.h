/**
 * @file interfaceTVert.h
 * @author CamFo Camille Fortin (camfortin2022@gmail.com)
 * @brief pour s'interfacer avec le temoin lumineux Vert du panneau ADAM. 
 * @version 0.1
 * @date 2022-11-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef INTERFACETVERT_H
#define INTERFACETVERT_H

//MODULE: interfaceTVert
//DESCRIPTION: pour s'interfacer avec le temoin lumineux T1. 

//HISTORIQUE:
// 2018-09-08, Yves Roy, creation
// 2022-04-11, reutilisation avec le ESP32 en 247-527

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define INTERFACETVERT_VALEUR_POUR_ALLUMER  1   
//#define INTERFACETVERT_VALEUR_POUR_ETEINDRE 0

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
//pas de dependances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
//pas de definitions publiques

//Fonctions publiques:
void interfaceTVert_allume(void);
void interfaceTVert_eteint(void);
void interfaceTVert_initialise(void);

//Variables publiques:
//pas de variables publiques

#endif

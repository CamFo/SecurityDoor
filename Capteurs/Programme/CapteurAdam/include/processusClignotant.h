/**
 * @file processusClignotant.h
 * @author Camille Fortin (camfortin2022@gmail.com)
 * @brief Processus servant a faire clignoter le board pour s'assurer que 
 *      le programme fonctionne et faire des test.
 * @version 0.1
 * @date 2023-05-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef PROCESSUSCLIGNOTANT_H
#define PROCESSUSCLIGNOTANT_H

//MODULE: processusClignotant
//DESCRIPTION: implemente la gestion d'un clignotant.

//HISTORIQUE:
// 2018-09-09, Yves Roy, creation
// 2022-04-11, Yves Roy, reutilisation pour ESP32 247-527

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//pas de dependances materielles

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define PROCESSUSCLIGNOTANT_TEMPS_ALLUME_EN_MS  500
//#define PROCESSUSCLIGNOTANT_TEMPS_ETEINT_EN_MS  500
//#define PROCESSUSCLIGNOTANT_PHASE 0


//INFORMATION PUBLIQUE:
//Definitions publiques:
//pas de definitions publiques

//Fonctions publiques:
void processusClignotant_initialise(void);

//Variables publiques:
//pas de variables publiques

#endif

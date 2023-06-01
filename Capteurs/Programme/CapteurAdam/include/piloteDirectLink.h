/**
 * @file piloteDirectLink.h
 * @author CamFo Camille Fortin (camfortin2022@gmail.com)
 * @brief Pilote qui permettre la lecture d'une entree d'un microcontrôleur en utilisant la librairie Arduino
 * @version 0.1
 * @date 2022-11-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef PILOTEDIRECTLINK_H
#define PILOTEDIRECTLINK_H

//MODULE: piloteDirectLink

//ENVIRONNEMENT ESP32 et Arduino 
// 2021-04-04, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define PILOTEDIRECTLINK_MODE_FLOTTANT_AVEC_PULL_UP
//#define PILOTEDIRECTLINK_MODE_FLOTTANT_SANS_PULL_UP
//#define PILOTEDIRECTLINK_BROCHE 21

//Dependances logicielles
//pas de dependances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
// pas de definitions publiques

//Fonctions publiques:

/// @brief Fonction qui permet de savoir l'état logique d'une BROCHE d'un micocontrôleur
/// @param void \ref PILOTEDIRECTLINK_BROCHE est une définition dans \ref xmain.h  
/// @return Valeur de la PIN de 1 ou 0 sur un unsigned char  
unsigned char piloteDirectLink_lit(void);
/// @brief Fonction qui remet a 0 l'entré direct Link
/// @param void  
void piloteDirectLink_Reset(void);
/// @brief Foncion qui initialise la lecture de la Broche du microcontrôleur
/// @param void \ref PILOTEDIRECTLINK_BROCHE est une définition dans \ref xmain.h  
void piloteDirectLink_initialise(void);

//Variables publiques:
//pas de variables publiques

#endif

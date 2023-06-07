/**
 * @file piloteIOIR1.h
 * @author Ilyes Gharmoul (ilyesdu2002@hotmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-05-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef PILOTEIOIR1_H
#define PILOTEIOIR1_H

//MODULE: piloteIOIR1
//DESCRIPTION: pour permettre la commande d'une sortie en "push-pull" (teste avec ESP32)
// 2022-04-11, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define PILOTEIOIR1_BROCHE 26
//#define PILOTEIOIR1_ETAT_INITIAL_A_UN
//#define PILOTEIOIR1_ETAT_INITIAL_A_ZERO

//Dependances logicielles
//pas de dependances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
// pas de definitions publiques

//Fonctions publiques:

/**
 * @brief Fonction qui permet de savoir l'état logique d'une BROCHE d'un micocontrôleur
 * 
 * @return  Valeur de la PIN de 1 ou 0 sur un unsigned char  
 */
unsigned char piloteIOIR1_lis();

void piloteIOIR1_initialise(void);

//Variables publiques:
//pas de variables publiques
#endif

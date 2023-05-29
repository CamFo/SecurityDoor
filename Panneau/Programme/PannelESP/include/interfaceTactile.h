/**
 * @file interfaceTactile.h
 * @author Camille Fortin camfortin2022@gmail.com
 * @brief 
 * @version 0.1
 * @date 2023-05-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef INTERFACETACTILE_H
#define INTERFACETACTILE_H

#define INTERFACETACTILE_MODULE_EN_FONCTION 1
#define INTERFACETACTILE_MODULE_PAS_EN_FONCTION 0
#define INTERFACETACTILE_INFORMATION_DISPONIBLE 1
#define INTERFACETACTILE_INFORMATION_TRAITEE 0
#define INTERFACETACTILE_INACTIVE 0
#define INTERFACETACTILE_ACTIVE  1
#define INTERFACETACTILE_PAS_EN_FONCTION 2

/// @brief Structure public qui permet de savoir et de changer l'état du module  
typedef struct
{
  unsigned char etatDuModule;  
  unsigned char information;
  unsigned char etatDeLEntree;
  int x;
  int y;
  bool etatBouttonBarre;
  bool etatBouttonDebarre;
} INTERFACETACTILE;

//Fonctions publiques:
/**
 * @brief Fonction d'initialisaiton du Pavée tactile
 */
void interfaceTactile_initialise(void);

//Variables publiques:
/**
 * @brief Structure qui enregistre les informations publique du module
 */
extern INTERFACETACTILE interfaceTactile;

#endif
/**
 * @file interfaceRGB.h
 * @author Ilyes Gharmoul (ilyesdu2002@hotmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-05-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef INTERACERGB_H
#define INTERACERGB_H

//MODULE: INTERACERGB
//DESCRIPTION: pour s'interfacer avec une bande de lumière

//HISTORIQUE:
// 2018-09-08, Yves Roy, creation
// 2022-04-11, reutilisation avec le ESP32 en 247-527

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")

#define INTERFACERGB_VALEUR_ROUGE 0
#define INTERFACERGB_VALEUR_BLEU  1
#define INTERFACERGB_VALEUR_VERT  2
#define INTERFACERGB_VALEUR_JAUNE 3
#define INTERFACERGB_VALEUR_BLEUP 4
#define INTERFACERGB_VALEUR_MAUVE 5
#define INTERFACERGB_VALEUR_BLANC 6
#define INTERFACERGB_VALEUR_ETEINT 7
#define INTERFACERGB_MAXSTATE 8

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
//pas de dependances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
//pas de definitions publiques
#define INTERFACERGB_MODULE_EN_FONCTION 1
#define INTERFACERGB_MODULE_PAS_EN_FONCTION 0
#define INTERFACERGB_INFORMATION_DISPONIBLE 1
#define INTERFACERGB_INFORMATION_TRAITEE 0
#define INTERFACERGB_INACTIVE 0
#define INTERFACERGB_ACTIVE  1
#define INTERFACERGB_PAS_EN_FONCTION 2
/**
 * @brief Valeur pour allumer les temoins RGB
 * 
 */
#define INTERFACERGB_VALEUR_POUR_ALLUMER 1
/**
 * @brief Valeur pour eteindre les temoins RGB
 * 
 */
#define INTERFACERGB_VALEUR_POUR_ETEINDRE 0

//Fonctions publiques:
void interfaceRGB_allumeBlanc(void);
void interfaceRGB_eteintTous(void);
void interfaceRGB_allumeCouleur(unsigned int);
void interfaceRGB_initialise();
typedef struct
{
  unsigned char etatDuModule;  
  unsigned char couleur;
  bool RequeteActive;
} INTERFACERGB;

extern INTERFACERGB interfaceRGB;

//Variables publiques:
//pas de variables publiques

#endif

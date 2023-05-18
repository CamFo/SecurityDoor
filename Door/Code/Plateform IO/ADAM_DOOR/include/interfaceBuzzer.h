/**
 * @file interfaceBuzzer.h
 * @author Ilyes Gharmoul (ilyesdu2002@hotmail.com,)
 * @brief 
 * @version 0.1
 * @date 2023-05-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef INTERFACEBUZZER_H
#define INTERFACEBUZZER_H

#define INTERFACEBUZZER_MODULE_EN_FONCTION 1
#define INTERFACEBUZZER_MODULE_PAS_EN_FONCTION 0
#define INTERFACEBUZZER_INFORMATION_DISPONIBLE 1
#define INTERFACEBUZZER_INFORMATION_TRAITEE 0
#define INTERFACEBUZZER_INACTIVE 0
#define INTERFACEBUZZER_ACTIVE  1
#define INTERFACEBUZZER_PAS_EN_FONCTION 2


#define INTERFACEBUZZER_AUCUNBRUIT 0
#define INTERFACEBUZZER_25POURCENT 1
#define INTERFACEBUZZER_50POURCENT 2
#define INTERFACEBUZZER_75POURCENT 3
#define INTERFACEBUZZER_100POURCENT 4
#define INTERFACEBUZZER_MAXSTATE 5
/// @brief Structure public qui permet de savoir et de changer l'état du module  
typedef struct
{
  unsigned char etatDuModule;  
  unsigned char  valeurBruit;
  bool RequeteActive;
  unsigned int dureeActive;
} INTERFACEBUZZER;
void interfaceBuzzer_initalise();



extern INTERFACEBUZZER interfaceBuzzer;

#endif
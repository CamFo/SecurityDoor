#ifndef PROCESSUSTEST_H
#define PROCESSUSTEST_H

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


//INFORMATION PUBLIQUE:
//Definitions publiques:
//pas de definitions publiques

//Fonctions publiques:
void processusDeTest_initialise();
void processusDeTest_I2C_Delai1Sec();
void processusDeTest_RGB_Delai1Sec();
void processusDeTest_TestI2C();
void processusDeTest_TestRGB();
void processusDeTest_GPIO14_en_input();
void processusDeTest_Buzzer();
void processusDeTest_Buzzer_Delai1Sec();
//Variables publiques:
//pas de variables publiques

#endif

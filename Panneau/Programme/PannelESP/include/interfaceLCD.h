/**
 * @file interfaceLCD.h
 * @author CamFo Camille Fortin (camfortin2022@gmail.com)
 * @brief pour s'interfacer avec le LCD RGB du panneau ADAM. L'interface 
 *  utilise le piloteLCD pour commmuniquer avec l'écran. 
 * @version 0.1
 * @date 2022-11-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef INTERFACELCD_H
#define INTERFACELCD_H

//MODULE: interfaceLCD
//DESCRIPTION: pour s'interfacer avec le LCD. 


//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")


//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
//pas de dependances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
//pas de definitions publiques

//Fonctions publiques:
void interfaceLCD_initialise(void);

void interfaceLCD_ligneVertical(int positionX, int positionY, int longueur, unsigned int bColor);
void interfaceLCD_afficheChar(unsigned int x,unsigned int y,unsigned char value,unsigned int dcolor,unsigned int bgcolor);
void interfaceLCD_afficheString(unsigned int x,unsigned int y,unsigned char *str,unsigned int dcolor,unsigned int bgcolor);
void interfaceLCD_ClearScreen(unsigned int bColor);

void inttostr(int dd,unsigned char *str);

//Variables publiques:
//pas de variables publiques

#endif

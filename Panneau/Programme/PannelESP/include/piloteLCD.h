/**
 * @file piloteLCD.h
 * @author Camille Fortin
 * @brief Fichier permettant d'utiliser un LCD contrôler par un lil9488. 
 * @version 0.1
 * @date 2023-05-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef PILOTELCD_H
#define PILOTELCD_H 

#define TFT_CS         21   //GPIO 21 pin 
#define TFT_DC         33   //GPIO 33
#define TFT_MOSI       18   //GPIO18
#define TFT_MISO       19   //GPIO19
#define TFT_CLK        5    //GPIO5
#define TFT_RST        26



//#####################  DÉFINITION DE FONCTION PUBLIC ##################

void Write_Cmd(unsigned char CMD);
void Write_Cmd_Data (unsigned char CMDP);
void Write_Data(unsigned char DH,unsigned char DL);
void Write_Data_U16(unsigned int y);
void LCD_SetPos(unsigned int xs,unsigned int xe,unsigned int ys,unsigned int ye);

void piloteLCD_initialise(void);

#endif
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


//######################## DEFINE DES COULEURS DE BASE ########################

#define PURERED       0xF800
#define PUREGREEN     0x07E0
#define PUREBLUE      0x001F
#define BLACK         0x0000
#define WHITE         0xFFFFs
#define YELLOW        0xFFE0
#define MAGENTA       0xF81F
#define CYAN 	      0x07FF

//########################    DEFINE AUTRES COULEURS   ########################

#define Navy            0x000F      /*   0,   0, 128 */
#define DarkGreen       0x03E0      /*   0, 128,   0 */
#define DarkCyan        0x03EF      /*   0, 128, 128 */
#define Maroon          0x7800      /* 128,   0,   0 */
#define Purple          0x780F      /* 128,   0, 128 */
#define Olive           0x7BE0      /* 128, 128,   0 */
#define LightGrey       0xC618      /* 192, 192, 192 */
#define DarkGrey        0x7BEF      /* 128, 128, 128 */
#define Orange          0xFD20      /* 255, 165,   0 */
#define GreenYellow     0xAFE5      /* 173, 255,  47 */
#define Pink            0xF81F


//#####################  DÉFINITION DE FONCTION PUBLIC ##################


void ClearScreen(unsigned int bColor);
void LCD_FULL(unsigned int i);

void piloteLCD_initialise(void);
void piloteLCD_ligneVertical(int positionX, int positionY, int longueur, unsigned int bColor);

#endif
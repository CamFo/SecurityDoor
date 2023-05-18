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


#define TFT_CS         21
#define TFT_DC         33
#define TFT_MOSI       18
#define TFT_MISO       19
#define TFT_CLK        5
#define TFT_RST        2
//#define TFT_LED        PB0
//#define TFT_RST        PB4



void piloteLCD_initialise(void);
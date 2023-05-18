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


#define TFT_CS         21   //GPIO 21 pin 
#define TFT_DC         33   //GPIO 33
#define TFT_MOSI       18   //GPIO18
#define TFT_MISO       19   //GPIO19
#define TFT_CLK        5    //GPIO5
#define TFT_RST        



void piloteLCD_initialise(void);
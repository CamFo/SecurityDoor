/**
 * @file interfaceLCD.h
 * @author CamFo Camille Fortin (camfortin2022@gmail.com)
 * @brief Pour s'interfacer avec le LCD RGB du panneau ADAM. L'interface 
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
#define INTERFACELCD_INFORMATION_DISPONIBLE 1
#define INTERFACELCD_INFORMTAION_TRAITEE 0

#define CAPTEURSTATE_ON  1
#define CAPTEURSTATE_OFF 0
#define DOORSTATE_ON  1
#define DOORSTATE_OFF 0
//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
//pas de dependances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
//pas de definitions publiques

//######################## DEFINE DES COULEURS DE BASE ########################

#define PURERED       0xF800
#define PUREGREEN     0x07E0
#define PUREBLUE      0x001F
#define BLACK         0x0000
#define WHITE         0xFFFF
#define YELLOW        0xFFE0
#define MAGENTA       0xF81F
#define CYAN 	      0x07FF

// Autres Couleurs

#define Navy            0x000F      /*   0,   0, 128 */
#define DarkGreen       0x03E0      /*   0, 128,   0 */
#define DarkCyan        0x03EF      /*   0, 128, 128 */
#define Maroon          0x7800      /* 128,   0,   0 */
#define Purple          0x780F      /* 128,   0, 128 */
#define Olive           0x7BE0      /* 128, 128,   0 */
#define LightGrey       0xC618      /* 192, 192, 192 */
#define DarkGrey        0x39c7      
#define Orange          0xFD20      /* 255, 165,   0 */
#define GreenYellow     0xAFE5      /* 173, 255,  47 */
#define Pink            0xF81F


typedef struct
{
    unsigned char DoorState = 2;
    unsigned char CapteurState = 2;
    int x;
    int y;
    unsigned int couleur;
    unsigned int bgcolor;
    unsigned char information;
    
}INTERFACELCD;

extern INTERFACELCD interfaceLCD;



//Fonctions publiques:
void interfaceLCD_initialise(void);

void interfaceLCD_rectangle(unsigned int positionX,unsigned  int positionY,unsigned  int longueur,unsigned  int epaisseur, unsigned int bColor);
void interfaceLCD_afficheChar(unsigned int x,unsigned int y,unsigned char value,unsigned int dcolor,unsigned int bgcolor);
void interfaceLCD_afficheString(unsigned int x,unsigned int y,unsigned char *str,unsigned int dcolor,unsigned int bgcolor);
void interfaceLCD_ClearScreen(unsigned int bColor);

void BRS_LCD_Draw_Pixel(unsigned int x, unsigned int y, unsigned int color);
void BRS_LCD_Draw_Line(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int color);
void BRS_LCD_Draw_CirclePixel(unsigned int x, unsigned int y, double radius, double radian, unsigned int color);
void BRS_LCD_Draw_Shape_Circle(unsigned int x, unsigned int y, double radius, unsigned int color);
void BRS_LCD_Draw_Shape_CircleF(unsigned int x, unsigned int y, unsigned int radius, unsigned int color);
void inttostr(int dd,unsigned char *str);

//Variables publiques:
//pas de variables publiques

#endif

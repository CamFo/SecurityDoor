/**
 * @file interfaceLCD.cpp
 * @author CamFo Camille Fortin (camfortin2022@gmail.com)
 * @brief Interface qui contrôle le LCD du panneau du projet Adam
 * @version 0.1
 * @date 2022-11-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//INCLUSIONS
#include <Arduino.h>

#include "main.h"
#include "word.h"
#include "interfaceLCD.h"
#include "piloteLCD.h"


void interfaceLCD_initialise(void)
{
  interfaceLCD_ClearScreen(DarkGrey);  // Dark Font
  
  unsigned char Headstring[] = "Temperature:    C -- Humidite:   %          MAC  70:B8:F6:F0:C6:B0";
  interfaceLCD_afficheString(10, 3, Headstring, 0, WHITE, DarkGrey);
  BRS_LCD_Draw_Shape_Circle(118, 6, 2, WHITE);
  interfaceLCD_rectangle(10, 17, 460, 2, BLACK);  // Ligne Header


  //INTERFACE SERRURE 
  unsigned char ESstring[] = "ETAT SERRURE";
  interfaceLCD_afficheString(70, 32, ESstring, 1,GreenYellow, DarkGrey);
  interfaceLCD_rectangle(20, 85, 100, 70, 0x9000); // Bouttton Rouge Barre
  interfaceLCD_rectangle(140, 85, 100, 70, DarkGreen);  //Boutton Vert Debarre

  // CADENAS BOUTTON BARRE
  interfaceLCD_rectangle(50, 110, 38, 34, BLACK);
  for(int i=10; i<=14; i++)
  {
    BRS_LCD_Draw_Shape_Circle(70, 110, i, BLACK);
  }
  // FIN DU CADENAS
  //FIN DE L'INTERFACE SERRURE

  // ÉTAT DE LA COMMUNICATION
  unsigned char hstring[] = "COMMUNICATIONS";
  interfaceLCD_afficheString(365, 32, hstring, 1, GreenYellow, DarkGrey);
  unsigned char Dstring[] = "Porte:";
  interfaceLCD_afficheString(360, 60, Dstring, 0, WHITE, DarkGrey);
  unsigned char Cstring[] = "Capteur:";
  interfaceLCD_afficheString(360, 82, Cstring, 0, WHITE, DarkGrey);
  BRS_LCD_Draw_Shape_CircleF(450, 66, 8, LightGrey);  // Led RGB qui indique l'état de la COM
  BRS_LCD_Draw_Shape_CircleF(450, 88, 8, LightGrey);  // Led RGB qui indique l'état de la COM
  // FIN ÉTAT DE LA COMMUNICATION

  // ETAT DE LA PORTE
//interfaceLCD_afficheString(365, 32, hstring, GreenYellow, DarkGrey);
//  unsigned char Dstring[] = "PORTE";

  //FIN ÉTAT DE LA PORTE

  unsigned char Sstring[] = "ADAM project TSO 2023";
  interfaceLCD_afficheString(324, 304, Sstring, 0, YELLOW, DarkGrey);
  Serial.print("#####  LCD INTERFACE INITIALISED  #####");
}

/**
 * @brief Fonction qui met le LCD complet en une couleur uni.
 * 
 * @param bColor // Couleur sur 16 bit 
 */
void interfaceLCD_ClearScreen(unsigned int bColor)
{
    unsigned int i,j;
    LCD_SetPos(0,479,0,319);
    for (i=0;i<480;i++)
    {

        for (j=0;j<320;j++)
            Write_Data_U16(bColor);
    }
}
void interfaceLCD_rectangle(unsigned int positionX,unsigned  int positionY, unsigned int longueur, unsigned int epaisseur, unsigned int bColor)
{
    unsigned int i,j;
    unsigned int Xe = positionX + longueur; // loongeur de a ligne horizontal
    unsigned int Ye = positionY + epaisseur; 

    if(Xe >= 479) Xe = 479; // Pour s'assurer de pas etre off coordinate
    
    LCD_SetPos(positionX, Xe, positionY, Ye);
	for (j = 0; j < epaisseur; j++)
	{
	  for (i=0;i<=longueur;i++)
	  {
	    Write_Data_U16(bColor);
	  }
	}
}
void interfaceLCD_afficheChar(unsigned int x,unsigned int y,unsigned char value,bool gras,unsigned int dcolor,unsigned int bgcolor)	
{  
	unsigned char i,j;
  unsigned char *temp;

  if(gras)  // SI on est en gras on prend l'autre tableau
  {
    temp=Gzifu;
  }
  else
  {
    temp=zifu;
  }
  LCD_SetPos(x,x+7,y,y+11);      
	temp+=(value-32)*12;
	for(j=0;j<12;j++)
	{
		for(i=0;i<8;i++)
		{ 		     
		 	if((*temp&(1<<(7-i)))!=0)
			{
				Write_Data(dcolor>>8,dcolor);
			} 
			else
			{
				Write_Data(bgcolor>>8,bgcolor);
			}   
		}
		temp++;
	 }
}

void interfaceLCD_afficheString(unsigned int x,unsigned int y,unsigned char *str,bool gras,unsigned int dcolor,unsigned int bgcolor)	  
{  
	unsigned int x1,y1;
	x1=x;
	y1=y;
	while(*str!='\0')
	{	
		interfaceLCD_afficheChar(x1,y1,*str,gras,dcolor,bgcolor);
		x1+=7;
		str++;
	}	
}
// DRAW PIXEL

void BRS_LCD_Draw_Pixel(unsigned int x, unsigned int y, unsigned int color)
{
	LCD_SetPos(x, x, y, y);
	Write_Data_U16(color);
}
//��������������������������������������������������������������������������������������������������
void BRS_LCD_Draw_CirclePixel(unsigned int x, unsigned int y, double radius, double radian, unsigned int color)
//__________________________________________________________________________________________________
//  	Creator:	|Shawn Couture
//	Date made:	| 31/03/2022
//__________________________________________________________________________________________________
//	Function:	| Draws a pixel at a wanted radian value
//__________________________________________________________________________________________________
//	Entry:		| x,y (0-127|0-63) radius, angle(radian), state
//��������������������������������������������������������������������������������������������������
{  
   BRS_LCD_Draw_Pixel(ceil((sin(radian)*radius)+x),ceil((cos(radian)*radius)+y), color);
}
//��������������������������������������������������������������������������������������������������
void BRS_LCD_Draw_Shape_Circle(unsigned int x, unsigned int y, double radius, unsigned int color)
//__________________________________________________________________________________________________
//  	Creator:	|Shawn Couture
//	Date made:	| 31/03/2022
//__________________________________________________________________________________________________
//	Function:	| Draws a circle border from a starting radian, to an ending radian
//                      | To draw a complete circle, simply put (x,y,radius,0,6.28,1)
//__________________________________________________________________________________________________
//	Entry:		| x,y (0-127|0-63) radius, state
//��������������������������������������������������������������������������������������������������
{
  
  //Find the increment necessary in order to avoid  holes or overlapping pixels for no reasons
  double increment = (12.56/(2*3.1*(radius*radius)));
  
  //For loop from starting radian to ending radian incrementing in 0.01
  for(double i = 0; i <= 6.28; i += increment)
     {
        BRS_LCD_Draw_Pixel(floor(sin(i)*radius)+x, floor(cos(i)*radius)+y, color);
     }
}
//��������������������������������������������������������������������������������������������������
void BRS_LCD_Draw_Shape_CircleF(unsigned int x, unsigned int y, unsigned int radius, unsigned int color)
//__________________________________________________________________________________________________
//  	Creator:	| Shawn Couture
//	Date made:	| 19/04/2022
//__________________________________________________________________________________________________
//	Function:	| Draws a full circle without using sin or cos
//                      | 
//__________________________________________________________________________________________________
//	Entry:		| x,y (0-127|0-63) radius, state
//��������������������������������������������������������������������������������������������������
{
  unsigned int leftTopX = ((unsigned int) x) - (unsigned int) radius;
  unsigned int leftTopY = ((unsigned int) y) - (unsigned int) radius;
  
  unsigned int widthCoord = (leftTopX+((unsigned int)radius*2));
  unsigned int heigthCoord = (leftTopY+((unsigned int)radius*2));
  
  //Save memory by reusing input parameters
  unsigned int RadiusSquared = (radius*radius);        //Avoids doing exponents of radius
    
  //Fill in a circle inside a rectangle area of diameter width starting at the coords defined above
  for(unsigned int checkX = leftTopX; checkX <= widthCoord; checkX++)
     {
      for(unsigned int checkY = leftTopY; checkY <= heigthCoord; checkY++)
         {
           if(RadiusSquared < (((checkX - x)*(checkX - x)) + ((checkY - y)*(checkY - y))))
             {
               //BRS_LCD_Draw_Pixel(checkX, checkY, !state);
             }
           else
             {
               BRS_LCD_Draw_Pixel(checkX, checkY, color);             
             }
         }
     }
}
//��������������������������������������������������������������������������������������������������
void BRS_LCD_Draw_Line(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int color)
//__________________________________________________________________________________________________
//  	Creator:	|Shawn Couture
//	Date made:	| 24/03/2022
//__________________________________________________________________________________________________
//	Function:	| Draws a line inbetween 2 coordinates.
//			| coordinates range from x(0-127) and y(0-127). Then input on/off (1/0) 
//__________________________________________________________________________________________________
//	Entry:		| start coordinates (x,y) end coordinates (x,y) wanted state (state)
//��������������������������������������������������������������������������������������������������
{
 //##########################################//####################################_Local Variables_ 
   double lenght      = 0;                   // distance inbetween the 2 coordinates
   double ratioX      = 0.0;                 // difference between x1 and x2 divided by lenght.
   double ratioY      = 0.0;                 // difference between y1 and y2 divided by lenght.
 //##########################################//####################################_Local Variables_    
  
//////////////////////////////////////////////////////////////////////////////////////////////[MATH]
// Distance in between the 2 pixels.   
   lenght = (sqrt(((x1-x2)*(x1-x2))+((y1-y2)*(y1-y2))));

// Difference in between the 2 X coordinates.   
   ratioX = (x2-x1)/lenght;// -0.71
   ratioY = (y2-y1)/lenght;// -0.71
 
//////////////////////////////////////////////////////////////////////////////////////////////[LOOP]
// loop form 0 to the distance inbetween the 2 points
   for(unsigned int i = 0; i<=ceil(lenght); i++)
      {
        BRS_LCD_Draw_Pixel((x1 + (i*ratioX)), (y1 + (i*ratioY)), color);
      }
}





//

void inttostr(int dd,unsigned char *str)
{
	str[0]=dd/10000+48;
	str[1]=(dd/1000)-((dd/10000)*10)+48;
	str[2]=(dd/100)-((dd/1000)*10)+48;
	str[3]=(dd/10)-((dd/100)*10)+48;
	str[4]=dd-((dd/10)*10)+48;
	str[5]=0;
}
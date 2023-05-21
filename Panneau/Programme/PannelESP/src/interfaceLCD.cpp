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
  interfaceLCD_ClearScreen(DarkGrey);
  interfaceLCD_rectangle(20, 15, 440, 3, BLACK);

  unsigned char Sstring[] = "ADAM project TSO 2023";
  interfaceLCD_afficheString(320, 300, Sstring, YELLOW, DarkGrey);

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
void interfaceLCD_afficheChar(unsigned int x,unsigned int y,unsigned char value,unsigned int dcolor,unsigned int bgcolor)	
{  
	unsigned char i,j;
	unsigned char *temp=zifu;    
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

void interfaceLCD_afficheString(unsigned int x,unsigned int y,unsigned char *str,unsigned int dcolor,unsigned int bgcolor)	  
{  
	unsigned int x1,y1;
	x1=x;
	y1=y;
	while(*str!='\0')
	{	
		interfaceLCD_afficheChar(x1,y1,*str,dcolor,bgcolor);
		x1+=7;
		str++;
	}	
}


void inttostr(int dd,unsigned char *str)
{
	str[0]=dd/10000+48;
	str[1]=(dd/1000)-((dd/10000)*10)+48;
	str[2]=(dd/100)-((dd/1000)*10)+48;
	str[3]=(dd/10)-((dd/100)*10)+48;
	str[4]=dd-((dd/10)*10)+48;
	str[5]=0;
}
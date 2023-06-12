/**
 * @file piloteLCD.cpp
 * @author Camille Fortin
 * @brief 
 * @version 0.1
 * @date 2023-05-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <Arduino.h>

#include "main.h"
#include "piloteLCD.h"


//########### DÉCLARATION DES FONCTIONS ######################

void piloteLCD_initialise(void)
{
    pinMode(TFT_CS, OUTPUT);
    pinMode(TFT_MOSI, OUTPUT);
    pinMode(TFT_MISO, OUTPUT);
    pinMode(TFT_CLK, OUTPUT);
    pinMode(TFT_RST, OUTPUT);

    digitalWrite(TFT_RST, HIGH);//RES=1;
    sleep(0.005);//delayms(5);
    digitalWrite(TFT_RST, LOW);//RES=0;
    sleep(0.01);//delayms(10);
    digitalWrite(TFT_RST, HIGH);//RES=1;
    sleep(0.12);//delayms(120);   


    Write_Cmd(0xE0);
    Write_Cmd_Data(0x00);
    Write_Cmd_Data(0x03);
    Write_Cmd_Data(0x09);
    Write_Cmd_Data(0x08);
    Write_Cmd_Data(0x16);
    Write_Cmd_Data(0x0A);
    Write_Cmd_Data(0x3F);
    Write_Cmd_Data(0x78);
    Write_Cmd_Data(0x4C);
    Write_Cmd_Data(0x09);
    Write_Cmd_Data(0x0A);
    Write_Cmd_Data(0x08);
    Write_Cmd_Data(0x16);
    Write_Cmd_Data(0x1A);
    Write_Cmd_Data(0x0F);


    Write_Cmd(0XE1);
    Write_Cmd_Data(0x00);
    Write_Cmd_Data(0x16);
    Write_Cmd_Data(0x19);
    Write_Cmd_Data(0x03);
    Write_Cmd_Data(0x0F);
    Write_Cmd_Data(0x05);
    Write_Cmd_Data(0x32);
    Write_Cmd_Data(0x45);
    Write_Cmd_Data(0x46);
    Write_Cmd_Data(0x04);
    Write_Cmd_Data(0x0E);
    Write_Cmd_Data(0x0D);
    Write_Cmd_Data(0x35);
    Write_Cmd_Data(0x37);
    Write_Cmd_Data(0x0F);


    Write_Cmd(0XC0);      //Power Control 1 
    Write_Cmd_Data(0x17);    //Vreg1out 
    Write_Cmd_Data(0x15);    //Verg2out 

    Write_Cmd(0xC1);      //Power Control 2     
    Write_Cmd_Data(0x41);    //VGH,VGL 

    Write_Cmd(0xC5);      //Power Control 3 
    Write_Cmd_Data(0x00); 
    Write_Cmd_Data(0x12);    //Vcom 
    Write_Cmd_Data(0x80);

    Write_Cmd(0x36);      //Memory Access 
    Write_Cmd_Data(0xE8);   // SCREEN orientation 

    Write_Cmd(0x3A);      // Interface Pixel Format 
    Write_Cmd_Data(0x66); 	  //18 bit    

    Write_Cmd(0XB0);      // Interface Mode Control 
    Write_Cmd_Data(0x80);     			 //SDO NOT USE

    Write_Cmd(0xB1);      //Frame rate 
    Write_Cmd_Data(0xA0);    //60Hz 

    Write_Cmd(0xB4);      //Display Inversion Control 
    Write_Cmd_Data(0x02);    //2-dot 

    Write_Cmd(0XB6);      //Display Function Control  RGB/MCU Interface Control 

    Write_Cmd_Data(0x02);    //MCU 
    Write_Cmd_Data(0x02);    //Source,Gate scan dieection 

    Write_Cmd(0XE9);      // Set Image Functio
    Write_Cmd_Data(0x00);    // Disable 24 bit data

    Write_Cmd(0xF7);      // Adjust Control 
    Write_Cmd_Data(0xA9);     
    Write_Cmd_Data(0x51);     
    Write_Cmd_Data(0x2C);     
    Write_Cmd_Data(0x82);    // D7 stream, loose 

    Write_Cmd(0x11); //Sleep out
    sleep(0.12);//delayms(120);
    Write_Cmd(0x29);
}

void LCD_SetPos(unsigned int xs,unsigned int xe,unsigned int ys,unsigned int ye)
{
    Write_Cmd(0x2A);
	Write_Cmd_Data(xs>>8);
	Write_Cmd_Data(xs&0xff);
	Write_Cmd_Data(xe>>8);
	Write_Cmd_Data(xe&0xff);
	Write_Cmd(0x2B);
	Write_Cmd_Data(ys>>8);
	Write_Cmd_Data(ys&0xff);
	Write_Cmd_Data(ye>>8);
	Write_Cmd_Data(ye&0xff);

    Write_Cmd(0x2C);
}

// LOW LEVEL SERIAL WRITE FUNCTION
void Write_Cmd(unsigned char CMD)
{ 
    unsigned char i;
 	 
    digitalWrite(TFT_CS, LOW);  
  	digitalWrite(TFT_CLK, LOW);
 	digitalWrite(TFT_MOSI, LOW);   //SDI=1;COMMAND
    digitalWrite(TFT_CLK, HIGH);
    for(i=0;i<8;i++)
     {  digitalWrite(TFT_CLK, LOW);
        if(CMD&0x80) digitalWrite(TFT_MOSI, HIGH);
       	else digitalWrite(TFT_MOSI, LOW);
       	digitalWrite(TFT_CLK, HIGH);
        CMD=CMD<<1;
     }
   	digitalWrite(TFT_CS, HIGH);
}

void Write_Cmd_Data (unsigned char CMDP)
{ 
    unsigned char i;
    digitalWrite(TFT_CS, LOW);
  	digitalWrite(TFT_CLK, LOW);
 	digitalWrite(TFT_MOSI, HIGH);   //SDI=1;DATA OR PARAMETER
    digitalWrite(TFT_CLK, HIGH);
    for(i=0;i<8;i++)
     {  digitalWrite(TFT_CLK, LOW);
        if(CMDP&0x80) digitalWrite(TFT_MOSI, HIGH);
       	else digitalWrite(TFT_MOSI, LOW);
       	digitalWrite(TFT_CLK, HIGH);
        CMDP=CMDP<<1;
     }
   	digitalWrite(TFT_CS, HIGH);

}

void Write_Data(unsigned char DH,unsigned char DL)
{
    unsigned char R1,G1,b1,i;unsigned int LD=0;

    // RGB565 TO RGB666
    LD=DH<<8;
    LD|=DL;

        R1=(0x1f&(LD>>11))*2; R1<<=2;
    G1=0x3f&(LD>>5);   		G1<<=2;
    b1=	(0x1f&LD)*2; 	b1<<=2;

        
    digitalWrite(TFT_CS, LOW);
    digitalWrite(TFT_CLK, LOW);
    digitalWrite(TFT_MOSI, HIGH);   //SDI=1;DATA OR PARAMETER
    digitalWrite(TFT_CLK, HIGH);
    for(i=0;i<8;i++)
    {  digitalWrite(TFT_CLK, LOW);
        if(R1&0x80) digitalWrite(TFT_MOSI, HIGH);
        else digitalWrite(TFT_MOSI, LOW);
        digitalWrite(TFT_CLK, HIGH);
        R1=R1<<1;
    }

    digitalWrite(TFT_CLK, LOW);
    digitalWrite(TFT_MOSI, HIGH);   //SDI=1;DATA OR PARAMETER
    digitalWrite(TFT_CLK, HIGH);
        for(i=0;i<8;i++)
        {  digitalWrite(TFT_CLK, LOW);
        if(G1&0x80) digitalWrite(TFT_MOSI, HIGH);
        else digitalWrite(TFT_MOSI, LOW);
        digitalWrite(TFT_CLK, HIGH);
        G1=G1<<1;
        }


    digitalWrite(TFT_CLK, LOW);
    digitalWrite(TFT_MOSI, HIGH);   //SDI=1;DATA OR PARAMETER
    digitalWrite(TFT_CLK, HIGH);
        for(i=0;i<8;i++)
        {  digitalWrite(TFT_CLK, LOW);
        if(b1&0x80) digitalWrite(TFT_MOSI, HIGH);
        else digitalWrite(TFT_MOSI, LOW);
        digitalWrite(TFT_CLK, HIGH);
        b1=b1<<1;
        }

    digitalWrite(TFT_CS, HIGH);

}

void  Write_Data_U16(unsigned int y)
{
	unsigned char m,n;
	m=y>>8;
	n=y;
	Write_Data(m,n);

}

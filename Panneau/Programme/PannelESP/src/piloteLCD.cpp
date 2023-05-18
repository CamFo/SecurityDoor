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
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

//#include <SPI.h>

#include "piloteLCD.h"

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

unsigned long printHeader(void);


void piloteLCD_initialise(void)
{
    tft.begin();
    tft.setRotation(1);
    tft.fillScreen(0xA0);
    //printHeader();
}


unsigned long printHeader(void)
{
  tft.fillRect(0,0,240, 64,ILI9341_GREEN);
  tft.fillRect(0,64,240, 64,ILI9341_RED);
  tft.fillRect(0,128,240, 64,ILI9341_CYAN);
  tft.fillRect(0,192,240, 64,ILI9341_YELLOW);
  tft.fillRect(0,256,240, 64,ILI9341_ORANGE);

  unsigned long start = micros();
  tft.setTextColor(ILI9341_BLACK);   
  tft.setTextSize(3);
  //
  tft.setCursor(50,0+20);
  tft.print("CELCIUS");

  //
  tft.setCursor(50,64+20);
  tft.print("FAHRENHEIT");
  //
  tft.setCursor(50,128+20);
  tft.print("KELVIN");

    //
  tft.setCursor(50,192+20);
  tft.print("RANKIN");

   //
  tft.setCursor(50,256+20);
  tft.print("HUMIDITY");
  
  return micros() - start;
    
}



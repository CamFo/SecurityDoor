/**
 * @file interfaceSHT4X.cpp
 * @author Camille Fortin
 * @brief 
 * @version 0.1
 * @date 2023-05-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <Arduino.h>
#include <Adafruit_SHT4x.h>
#include <SPI.h>

#include "main.h"
#include "serviceBaseDeTemps.h"
#include "piloteESPNOW.h"
#include "interfaceSHT4X.h"

// Déclaration privé
Adafruit_SHT4x sht4 = Adafruit_SHT4x();
unsigned long compteurA;

//Déclaration fonction privé
void interfaceSHT4X_lecture(void);


//Définition de Fontions
void interfaceSHT4X_lecture(void)
{
  if(compteurA <= 1000)
  {
    compteurA++;
    return;
  }
  compteurA = 0;
  sensors_event_t humidity, temp;
  
  uint32_t timestamp = millis();
  sht4.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data
  timestamp = millis() - timestamp;

  Serial.print("Temperature: "); Serial.print(temp.temperature); Serial.println(" degrees C");
  ValeurEnvoie.Temperature = static_cast<unsigned char>(temp.temperature);
  Serial.print("Humidity: "); Serial.print(humidity.relative_humidity); Serial.println("% rH");
  ValeurEnvoie.Humiditee = static_cast<unsigned char>(humidity.relative_humidity);

  Serial.print("Read duration (ms): ");
  Serial.println(timestamp);

}

void interfaceSHT4X_initialise(void)
{
  if (! sht4.begin()) 
  {
    Serial.println("Couldn't find SHT4x");
    return;
  }
  Serial.println("Found SHT4x sensor");
  Serial.print("Serial number 0x");
  Serial.println(sht4.readSerial(), HEX);
    // You can have 3 different precisions, higher precision takes longer
  sht4.setPrecision(SHT4X_HIGH_PRECISION);
  switch (sht4.getPrecision()) {
     case SHT4X_HIGH_PRECISION: 
       Serial.println("High precision");
       break;
     case SHT4X_MED_PRECISION: 
       Serial.println("Med precision");
       break;
     case SHT4X_LOW_PRECISION: 
       Serial.println("Low precision");
       break;
  }

  // You can have 6 different heater settings
  // higher heat and longer times uses more power
  // and reads will take longer too!
  sht4.setHeater(SHT4X_NO_HEATER);
  switch (sht4.getHeater()) {
     case SHT4X_NO_HEATER: 
       Serial.println("No heater");
       break;
     case SHT4X_HIGH_HEATER_1S: 
       Serial.println("High heat for 1 second");
       break;
     case SHT4X_HIGH_HEATER_100MS: 
       Serial.println("High heat for 0.1 second");
       break;
     case SHT4X_MED_HEATER_1S: 
       Serial.println("Medium heat for 1 second");
       break;
     case SHT4X_MED_HEATER_100MS: 
       Serial.println("Medium heat for 0.1 second");
       break;
     case SHT4X_LOW_HEATER_1S: 
       Serial.println("Low heat for 1 second");
       break;
     case SHT4X_LOW_HEATER_100MS: 
       Serial.println("Low heat for 0.1 second");
       break;
  }
 
  serviceBaseDeTemps_executeDansLoop[INTERFACESHT4X_PHASE] = interfaceSHT4X_lecture;
}





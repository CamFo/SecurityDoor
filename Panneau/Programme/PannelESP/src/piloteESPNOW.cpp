/**
 * @file piloteESPNOW.cpp
 * @author Camille Fortin (camfortin2022@gmail.com)
 * @brief  Pilote qui permet la communication ESP-NOW entre chaque modules
 * 
 * @version 0.1
 * @date 2023-05-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */
// #############################################################
#include <esp_now.h>
#include <wifi.h>
#include "piloteESPNOW.h"



// Définiion privée

esp_now_peer_info_t peerInfo;


// Fonction publique

/**
 * @brief 
 * 
 * @param mac_addr 
 * @param status 
 */
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) 
{
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void piloteESPNOW_send(void)
{
    // Set values to send

    ValueEnvoie.States = 0x08;
    ValueEnvoie.Commande = 0x45;
    ValueEnvoie.ValeurA = false;
    ValueEnvoie.ValeurB = false;
    ValueEnvoie.ValeurC = false;
  
    // Send message via ESP-NOW
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &ValueEnvoie, sizeof(ValueEnvoie));
   
    if (result == ESP_OK)
    {
        Serial.println("Sent with success");
    }
    else 
    {
        Serial.println("Error sending the data");
    }
}

void piloteESPNOW_Pair(void)
{
  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}


/**
 * @brief Fonction d'initialisation du ESPNOW
 * 
 */
void piloteESPNOW_initialise(void)
{
    Serial.begin(115200);
    WiFi.mode(WIFI_MODE_STA);
    Serial.println(WiFi.macAddress());


    if (esp_now_init() != ESP_OK) 
    {
        Serial.println("Error initializing ESP-NOW");
        return;
    }
}

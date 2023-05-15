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

#include "main.h"
#include "piloteESPNOW.h"


// Définiion privée
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len);

esp_now_peer_info_t peerInfo;
stReceived ValueRecu;
stSend ValueEnvoie;
// Fonction Privée

/**
 * @brief Fonction qui est executer quand on envoie un message ESPNOW
 * 
 * @param mac_addr 
 * @param status 
 */
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) 
{
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
/**
 * @brief Fonciton executer quand un message ESP now est recu
 * 
 * @param mac 
 * @param incomingData 
 * @param len 
 */
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) 
{
  memcpy(&ValueRecu, incomingData, sizeof(ValueRecu));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("State: ");
  Serial.println(ValueRecu.States);
  Serial.print("Command: ");
  Serial.println(ValueRecu.Commande);
  Serial.print("Valeur A: ");
  Serial.println(ValueRecu.ValeurA);
  Serial.print("Valeur B: ");
  Serial.println(ValueRecu.ValeurB);
  Serial.print("Valeur C: ");
  Serial.println(ValueRecu.ValeurC);
  Serial.println();
}



// Fonction PUBLIC



void piloteESPNOW_send(unsigned char adresse[])
{
    // Set values to send

    ValueEnvoie.States = 0x08;
    ValueEnvoie.Commande = 0x45;
    ValueEnvoie.ValeurA = false;
    ValueEnvoie.ValeurB = false;
    ValueEnvoie.ValeurC = false;
  
    // Send message via ESP-NOW
    esp_err_t result = esp_now_send(adresse, (uint8_t *) &ValueEnvoie, sizeof(ValueEnvoie));
   
    if (result == ESP_NOW_SEND_SUCCESS)
    {
        Serial.println("Sent with success");
    }
    else 
    {
        Serial.println("Error sending the data");
    }
}



void piloteESPNOW_Pair(unsigned char adresse[])
{
  // Register peer
  memcpy(peerInfo.peer_addr, adresse, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  Serial.print('\n');
  Serial.println("####################    Paired to feather    ####################");
  Serial.print('\n');
}


/**
 * @brief Fonction d'initialisation du ESPNOW
 * 
 */
void piloteESPNOW_initialise(void)
{
  Serial.begin(115200);
  WiFi.mode(WIFI_MODE_STA);
  Serial.println("\n##################    HARDWARE MAC ADDRESS    ##################");
  Serial.print(  "                        ");
  Serial.print(WiFi.macAddress());
  Serial.println("                      \n");

  if (esp_now_init() != ESP_OK) 
  {
      Serial.println("Error initializing ESP-NOW");
      return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  // Fonction that will be called when a ESPNOW message is received
  esp_now_register_recv_cb(OnDataRecv);

  unsigned char adr[] = {0xC4, 0xDD, 0x57, 0x9C, 0xD3, 0x6C};   //  FeatherMAC  C4:DD:57:9C:D3:6C         PanneauMAC  70:B8:F6:F0:C6:B0  0x70, 0xB8, 0xF6, 0xF0, 0xC6, 0xB0
  piloteESPNOW_Pair(adr);

}

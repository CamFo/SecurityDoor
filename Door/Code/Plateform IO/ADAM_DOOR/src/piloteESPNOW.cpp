// ###########################################################
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


// Définition privée
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len);

PILOTEESPNOW piloteESPNOW;

esp_now_peer_info_t peerInfo;
//stReceived ValueRecu;
//stSend ValueEnvoie;


/**
 * @brief Tableau à changer pour chaques module du projet. Chaque module du projet qui parle
 *      en ESPNOW avec le panneau doit avoir un fichier pilote différent et cette adresse doit 
 *      corresponde à l'adresse mac du processeur ESP utilisé.
 * 
 *    Feather Cegep: 94:B9:7E:6B:84:C4
 *    Feather Appart: C4:DD:57:9C:D3:6C
 *    Pannel : 70:B8:F6:F0:C6:B0
 */ 
unsigned char MACadresse[] = {0x70, 0xB8, 0xF6, 0xF0, 0xC6, 0xB0};   //  FeatherMAC  C4:DD:57:9C:D3:6C         PanneauMAC  70:B8:F6:F0:C6:B0  0x70, 0xB8, 0xF6, 0xF0, 0xC6, 0xB0


// FONCTION PRIVÉE

/**
 * @brief Fonction qui est executer quand on envoie un message ESPNOW
 * 
 * @param mac_addr 
 * @param status 
 */
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) 
{
  Serial.print("\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
  Serial.println(status);
}
/**
 * @brief Fonction executer quand un message ESP now est recu
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

  piloteESPNOW.information = PILOTEESPNOW_INFORMATION_DISPONIBLE;
}

//########################### Fonction PUBLIC ################################

/**
 * @brief Send a mesage via ESPNOW to the MAC address specified in top
 *  of the driver source file
 * 
 */
void piloteESPNOW_send(void)
{
    // Send message via ESP-NOW
    esp_err_t result = esp_now_send(MACadresse, (uint8_t *) &ValueEnvoie, sizeof(ValueEnvoie));
    // Check for error
    if (result == ESP_NOW_SEND_SUCCESS)
    {
        Serial.println("Sent with success");
    }
    else 
    {
        Serial.println("Error sending the data");
    }
}


/**
 * @brief Fonction qui paire un board a un autre via ESPNOW 
 * 
 */
void piloteESPNOW_Pair(void)
{
  // Register peer
  memcpy(peerInfo.peer_addr, MACadresse, 6);
  peerInfo.channel = PILOTEESPNOW_CHANNEL;    // Canal de la communication ESPNOW
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK)
  {
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
  //esp_now_register_send_cb(OnDataSent);  // Callback
  // Fonction that will be called when a ESPNOW message is received
  esp_now_register_recv_cb(OnDataRecv);  // Callback
  piloteESPNOW.etatDuModule = PILOTEESPNOW_MODULE_EN_FONCTION;
}

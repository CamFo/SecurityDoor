// ###########################################################
/**
 * @file piloteESPNOWDoor.cpp
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
#include "piloteESPNOWDoor.h"


// Définition privée
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len);

PILOTEESPNOWDOOR piloteESPNOWDoor;

esp_now_peer_info_t peerInfoD;
DOOR_ADAM_R ValeurRecuDoor;
DOOR_ADAM_S ValeurEnvoieDoor;

/**
 * @brief Tableau à changer pour chaques module du projet. Chaque module du projet qui parle
 *      en ESPNOW avec le panneau doit avoir un fichier pilote différent et cette adresse doit 
 *      corresponde à l'adresse mac du processeur ESP utilisé.
 * 
 *    Feather Cegep: 94:B9:7E:6B:84:C4
 *    Feather Appart: C4:DD:57:9C:D3:6C
 *    Pannel : 70:B8:F6:F0:C6:B0
 *    Feather Door: FC:F5:C4:0A:05:C8
 *    Porte : 70:B8:F6:A7:35:34
 */ 
unsigned char MACadresseDoor[] = {0x70, 0xB8, 0xF6, 0xA7, 0x35, 0x34};   //  FeatherMAC  C4:DD:57:9C:D3:6C         PanneauMAC  70:B8:F6:F0:C6:B0  0x70, 0xB8, 0xF6, 0xF0, 0xC6, 0xB0


// FONCTION PRIVÉE
void OnDataSentD(const uint8_t *mac_addr, esp_now_send_status_t status);
void OnDataRecvD(const uint8_t * mac, const uint8_t *incomingData, int len);

/**
 * @brief Fonction qui est executer quand on envoie un message ESPNOW
 * 
 * @param mac_addr 
 * @param status 
 */
void OnDataSentD(const uint8_t *mac_addr, esp_now_send_status_t status) 
{
  Serial.print("\nLast Packet Door:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
/**
 * @brief Fonction executer quand un message ESP now est recu
 * 
 * @param mac 
 * @param incomingData 
 * @param len 
 */
void OnDataRecvD(const uint8_t * mac, const uint8_t *incomingData, int len) 
{
  memcpy(&ValeurRecuDoor, incomingData, sizeof(ValeurRecuDoor));
  Serial.println(" ====  PiloteESPNOW Door Recu ! ==== ");

  piloteESPNOWDoor.information = PILOTEESPNOWDOOR_INFORMATION_DISPONIBLE;
}

//########################### Fonction PUBLIC ################################

/**
 * @brief Send a mesage via ESPNOW to the MAC address specified in top
 *  of the driver source file
 * 
 */
void piloteESPNOWDoor_send(void)
{
    // Send message via ESP-NOW
    esp_err_t result = esp_now_send(MACadresseDoor, (uint8_t *) &ValeurEnvoieDoor, sizeof(ValeurEnvoieDoor));
    // Check for error
    if (result == ESP_NOW_SEND_SUCCESS)
    {
        //Serial.println("Sent with success");
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
void piloteESPNOWDoor_Pair(void)
{
  // Register peer
  memcpy(peerInfoD.peer_addr, MACadresseDoor, 6);
  peerInfoD.channel = PILOTEESPNOWDOOR_CHANNEL;    // Canal de la communication ESPNOW
  peerInfoD.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfoD) != ESP_OK)
  {
    Serial.println("######### Failed to add peer Door #########");
    return;
  }
  Serial.print('\n');
  Serial.println("####################    Paired to Door    ####################");
  Serial.print('\n');
}

/**
 * @brief Fonction d'initialisation du ESPNOW
 * 
 */
void piloteESPNOWDoor_initialise(void)
{
  WiFi.mode(WIFI_MODE_STA);

  if (esp_now_init() != ESP_OK) 
  {
      Serial.println("Error initializing ESP-NOW");
      return;
  }
  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSentD);  // Callback
  // Fonction that will be called when a ESPNOW message is received
  esp_now_register_recv_cb(OnDataRecvD);  // Callback
  piloteESPNOWDoor.etatDuModule = PILOTEESPNOWDOOR_MODULE_EN_FONCTION;
}

// ###########################################################
/**
 * @file piloteESPNOWCapteur.cpp
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
#include "piloteESPNOWCapteur.h"


// Définition privée
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len);

PILOTEESPNOWCAPTEUR piloteESPNOWCapteur;

esp_now_peer_info_t peerInfoC;
CAPTEUR_ADAM_R ValeurRecuCapteur;
CAPTEUR_ADAM_S ValeurEnvoieCapteur;


/**
 * @brief Tableau à changer pour chaques module du projet. Chaque module du projet qui parle
 *      en ESPNOW avec le panneau doit avoir un fichier pilote différent et cette adresse doit 
 *      corresponde à l'adresse mac du processeur ESP utilisé.
 * 
 *    Feather Cegep: 94:B9:7E:6B:84:C4
 *    Feather Appart: C4:DD:57:9C:D3:6C  0xC4, 0xDD, 0x57, 0x9C, 0xD3, 0x6C
 *    Pannel : 70:B8:F6:F0:C6:B0      0x70, 0xB8, 0xF6, 0xA7, 0x35, 0x34
 *    Feather Door: FC:F5:C4:0A:05:C8
 *    Porte : 70:B8:F6:A7:35:34
 */ 
unsigned char MACadresseCapteur[] = {0xC4, 0xDD, 0x57, 0x9C, 0xD3, 0x6C};   //  FeatherMAC  C4:DD:57:9C:D3:6C         PanneauMAC  70:B8:F6:F0:C6:B0  0x70, 0xB8, 0xF6, 0xF0, 0xC6, 0xB0


// FONCTION PRIVÉE
void OnDataSentC(const uint8_t *mac_addr, esp_now_send_status_t status);
void OnDataRecvC(const uint8_t * mac, const uint8_t *incomingData, int len);

/**
 * @brief Fonction qui est executer quand on envoie un message ESPNOW
 * 
 * @param mac_addr 
 * @param status 
 */
void OnDataSentC(const uint8_t *mac_addr, esp_now_send_status_t status) 
{
  Serial.print("Last Packet Capteur:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
  Serial.flush();
}
/**
 * @brief Fonction executer quand un message ESP now est recu
 * 
 * @param mac 
 * @param incomingData 
 * @param len 
 */
void OnDataRecvC(const uint8_t * mac, const uint8_t *incomingData, int len) 
{
  if(mac[1] == MACadresseCapteur[1])  // TEMRORY FIX
  {
    memcpy(&ValeurRecuCapteur, incomingData, sizeof(ValeurRecuCapteur));
    piloteESPNOWCapteur.information = PILOTEESPNOWCAPTEUR_INFORMATION_DISPONIBLE;
  }
}

//########################### Fonction PUBLIC ################################

/**
 * @brief Send a mesage via ESPNOW to the MAC address specified in top
 *  of the driver source file
 * 
 */
void piloteESPNOWCapteur_send(void)
{
    // Send message via ESP-NOW
    esp_err_t result = esp_now_send(MACadresseCapteur, (uint8_t *) &ValeurEnvoieCapteur, sizeof(ValeurEnvoieCapteur));
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
void piloteESPNOWCapteur_Pair(void)
{
  // Register peer
  memcpy(peerInfoC.peer_addr, MACadresseCapteur, 6);
  peerInfoC.channel = 0;    // Canal de la communication ESPNOW
  peerInfoC.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfoC) != ESP_OK)
  {
    Serial.println("X=X=X Failed to add peer Capteur X=X=X");
    return;
  }
  Serial.print('\n');
  Serial.println("====    Paired to Capteur   ====");
  Serial.print('\n');
  Serial.flush();
}

/**
 * @brief Fonction d'initialisation du ESPNOW
 * 
 */
void piloteESPNOWCapteur_initialise(void)
{
  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSentC);  // Callback
  // Fonction that will be called when a ESPNOW message is received
  esp_now_register_recv_cb(OnDataRecvC);  // Callback
  piloteESPNOWCapteur.etatDuModule = PILOTEESPNOWCAPTEUR_MODULE_EN_FONCTION;
}

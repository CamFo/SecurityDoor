/**
 * @file xmain.h
 * @author CamFo Camille Fortin (camfortin2022@gmail.com)
 * 
 * @brief Le fichier xmain.h est nécessaire pour les includions global qui
 *   contien les defines essentiel au fonctionnement du véhicule 
 *  fesant partie du projet de 5e session de TSO. Le processeur utilisé
 *  pour la gestion du véhicule est un ESP32. Voir le document de projet
 *  pour plus d'information sur le fonctionnement du véhicule. 
 *      
 *  Le programme suivant fonctionne avec une base de temps et des machine d'état.
 *  Le processus principale du programme est le \ref xprocessusVehicule.h 
 * 
 *   
 * @version 0.1
 * @date 2022-11-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef MAIN_H
#define MAIN_H

//PROGRAMME: ESP véhicule Projet 5e Session
//DESCRIPTION: programme qui sert de base pour l'introduction au HTML, Javascript, etc

//HISTORIQUE:
/* Historique du programme gèrer par git et publier sur github au lien suivant
*
*       https://github.com/LyamBRS/Projet-5e-Session.git 
*/
  
//  *** INFORMATION PUBLIQUE ***


//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles:

/**
 * @brief definition des broches I2C sur esp32 
 * 
 */
#define PILOTEI2C_SDA1   (23)
/**
 * @brief definition des broches I2C sur esp32 
 * 
 */
#define PILOTEI2C_SCL1   (22)
/**
 * @brief Frequence de oscillation pour I2C1
 * 
 */
#define PILOTEI2C1_FREQ1 100000
/**
 * @brief Définition qui permet de modifier un état de la broche 14 du esp32 
 * 
 */
#define PILOTEIOT2_BROCHE 14

/**
 * @brief Définition qui permet de modifier un état de la broche 2 du esp32 
 * 
*/
#define PILOTEIOT1_BROCHE 13

/**
 * @brief Définitoon qui permet de modifer un état de la broche 12 du esp32
 * 
 */
#define PILOTEIOT3_BROCHE 12

/**
 * @brief Définition qui permet de modifer l'état de la pin 4 du esp32 
 * 
 */
#define PILOTEIOM2_BROCHE 4 // 37 et 24 sont pas bon

/**
 * @brief Définition qui permet de modifier l'état de la pin 2 du esp32
 * 
 */
#define PILOTEIOM1_BROCHE 2

/**
 * @brief Définition qui permet de modifier l'état de la pin 37 du esp32 
 * 
 */
#define PILOTEIOEA1_BROCHE 23

/**
 * @brief Définition qui permet de modifer l'état de la pin du buzzer
 * 
 */
#define PILOTEBUZZER_BROCHE 26
/**
 * @brief Définition qui permet de lire l'état de la pin du infrarouge recepteur
 * 
 */
#define PILOTEIOIR1_BROCHE 34
/**
 * @brief Définition qui permet de mmodifier l'état de la pin du transmettteur infrarrouge
 * 
 */
#define PILOTEIOIR2_BROCHE 32

#define PILOTEIOT1_ETAT_INITIAL_A_ZERO
#define PILOTEIOT2_ETAT_INITIAL_A_ZERO
#define PILOTEIOT3_ETAT_INITIAL_A_ZERO
#define PILOTEIOM1_ETAT_INITIAL_A_ZERO
#define PILOTEIOM2_ETAT_INITIAL_A_ZERO
#define PILOTEIOEA1_ETAT_INITIAL_A_ZERO
#define PILOTEBUZZER_ETAT_INITIAL_A_ZERO
#define PILOTEIOIR1_MODE_FLOTTANT_SANS_PULL_UP
//#define PILOTEIOIR2_ETAT_INITIAL_A_ZERO
#define PILOTEIOEA_ETAT_INITIAL_A_ZERO

/***  DÉFINITION NÉCESSAIRE À LA BASE DE TEMPS  ***/
/**
 * @brief Période en microsecondes à laquelle le TaskServer exécute sa fonction 
 *  qui fait apelle au service Base de temps pour gêrer plusieur tache a la fois
 * 
 */
#define SERVICETASKSERVER_PERIODE_EN_US (1000L)
/**
 * @brief Fréquence en Hz de la base de temps
 * 
 */
#define SERVICEBASEDETEMPS_FREQUENCE_EN_HZ 1000
/**
 * @brief Nombre de phase dans une période de la base de temps (1 si pas utilisé)
 */
#define SERVICEBASEDETEMPS_NOMBRE_DE_PHASES_DANS_LOOP 1
/**
 * @brief Nombre de phase de la base de temps \ref xserviceBaseDeTemps.h
 * 
 */
#define SERVICEBASEDETEMPS_NOMBRE_DE_PHASES 10

// Phase 0 et 1 sont utilisé et défini par ServiceCommunication.h

#define INTERFACERGB_PHASE 0
/**
 * @brief Numéro de phase de l'interface du buzzer
 * 
 */
#define INTERFACEMOTEUR_PHASE 1
/**
 * @brief Numéro de phase de l'interface infrarouge  
 * 
 */
#define INTERFACEINFRAROUGE_PHASE 2
/**
 * @brief Numéro de phase la lecture de l'Entrée 1 
 */
#define INTERFACEBUZZER_PHASE 3
/**
 * @brief Numéro de phase du service de communication ESP-NOW 
 * 
 */
#define SERVICECOMMUNICATION_PHASE 4
/**
 * @brief Numéro de phase du processus de gestion de la communcation
 */
#define PROCESSUSTESTS_PHASE 5
/**
 * @brief Numéro de phase du processus de gestion de la porte
 * 
*/
#define PROCESSUSVERIFIEOUVERTURE_PHASE 6
/**
 * @brief Numéro de phase du processus de gestion des indicateurs lumineux et buzzers
 * 
 */
#define PROCESSUSGESTIONINDICATEURS_PHASE 7

/**
 * @brief Numéro de phase du processus gestion de pairing avec le server 
 * 
*/
#define PROCESSUSGESTIONPAIRING_PHASE 8
/**
 * @brief Numéro de phase du processus control de moteur DC
 * 
 */
#define PROCESSUSCONTROLMOTEUR_PHASE 9

/**
 * @brief  Numéro de phase de l'interface du PN523
 * 
 */
//#define INTERFACEPN523_PHASE 


#define PROCESSUSPOURTEST_COMPTE_EN_MS 500
#define INTERFACEMOTEUR_COMPTE_EN_MS 500
#define INTERFACEBUZZER_COMPTE_EN_MS 500
#define INTERFACEINFRAROUGE_COMPTE_EN_MS 500
#define PROCESSUSVERIFIEOUVERTURE_COMPTE_EN_MS 500
#define PROCESSUSPOURGESTIONPAIRING_COMPTE_EN_MS 500
#define PROCESSUSCONTROLMOTEUR_COMPTE_EN_MS 500
#define PROCESSUSGESTIONINIDCATEUR_COMPTE_EN_MS 500
#define SERVICECOMMUNICATION_COMPTE_EN_MS 500

#define I2C_ADR_NFC (0x24)
#define CONFIG_DISABLE_HAL_LOCKS

#define TRUE true
#define FALSE false

//#define MODE_DEBUG_ESPNOW
#define MODEDEBUG
#endif



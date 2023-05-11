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
 * @brief Définition pour choisir le mode de lecture de PIN
 * 
 */
#define PILOTEENTREE1_MODE_FLOTTANT_AVEC_PULL_UP
/**
 * @brief Définition qui undique le numéro de broche du ESP32 utilisé par l'entrée1
 * 
 */
#define PILOTEENTREE1_BROCHE 34

/**
 * @brief Définition qui permet de modifier un état de la broche 13 du esp32 
 * 
 */
#define PILOTEIOT14_BROCHE 13

/**
 * @brief Définition qui permet de modifier un état de la broche 16 du esp32 
 * 
*/
#define PILOTEIOT13_BROCHE 16

/**
 * @brief Définitoon qui permet de modifer un état de la broche 14 du esp32
 * 
 */
#define PILOTEIOT12_BROCHE 14



#define PILOTEIOT14_ETAT_INITIAL_A_ZERO
#define PILOTEIOT13_ETAT_INITIAL_A_ZERO
#define PILOTEIOT12_ETAT_INITIAL_A_ZERO

/**
 * @brief Défini la valeur lu quand l'entré 1 est active (quand la switch est pesé)
 */
#define INTERFACEENTREE1_VALEUR_LUE_SI_ACTIVE  0   
/**
 * @brief Défini la valeur lu quand l'entré 1 est inactive (quand la switch est relaché)
 */
#define INTERFACEENTREE1_VALEUR_LUE_SI_INACTIVE 1
/**
 * @brief Défini la fréquence en Hz des lectures de l'entré 1 
 * 
 */
#define INTERFACEENTREE1_FREQUENCE_DES_LECTURES_EN_HZ  125
/**
 * @brief Défini le nombre de lectures de l'entré avant d'avoir une valeur fiable
 * 
 */
#define INTERFACEENTREE1_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION 10

/** Définition pour le témoin 1 **/
/**
 * @brief Valeur pour allumer le témoin 1
 */
#define INTERFACET1_VALEUR_POUR_ALLUMER  1
/**
 * @brief Valeur pour éteindre le témoin 1
 */
#define INTERFACET1_VALEUR_POUR_ETEINDRE 0

#define INTERFACERGB_VALEUR_POUR_ALLUMER 1

#define INTERFACERGB_VALEUR_POUR_ETEINDRE 0

#define INTERFACERGB_VALEUR_ROUGE 0
#define INTERFACERGB_VALEUR_BLEU  1
#define INTERFACERGB_VALEUR_VERT  2
#define INTERFACERGB_VALEUR_JAUNE 3
#define INTERFACERGB_VALEUR_BLEUP 4
#define INTERFACERGB_VALEUR_MAUVE 5
#define INTERFACERGB_VALEUR_BLANC 6

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
#define SERVICEBASEDETEMPS_NOMBRE_DE_PHASES 3//4

// Phase 0 et 1 sont utilisé et défini par ServiceCommunication.h
#define PROCESSUSTESTS_PHASE 2
/**
 * @brief Numéro de phase la lecture de l'Entrée 1 
 */
#define INTERFACEENTREE1_PHASE 1
/**
 * @brief Numéro de phase du processus de gestion de la benne
 */
#define PROCESSUSCLIGNOTANT_PHASE 0
/**
 * @brief  Numéro de phase de l'interface du PN523
 * 
 */
//#define INTERFACEPN523_PHASE 3


#define PROCESSUSCLIGNOTANT_TEMPS_ALLUME_EN_MS 500
#define PROCESSUSCLIGNOTANT_TEMPS_ETEINT_EN_MS 500
#define PROCESSUSPOURTEST_COMPTE_EN_MS 500

#define I2C_ADR_NFC (0x24)
#define CONFIG_DISABLE_HAL_LOCKS
//***************************************************BUS I2C*************************************************    

#define BUS_I2C1 
#define FREQ1 100000
#define SDA1   (23)
#define SCL1   (27)

//#define BUS_I2C2
//#define BUS_I2C3
#define TRUE true
#define FALSE false
#endif
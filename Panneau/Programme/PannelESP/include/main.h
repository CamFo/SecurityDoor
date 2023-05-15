/**
 * @file main.h
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
 * @brief Définition qui assigne le bon numéro de broche du ESP32 au témoin 1
 * 
 */
#define PILOTEIOT1_BROCHE 13
/**
 * @brief Définition qui permet de modifier un état initiale au témoin 1
 * 
 */
#define PILOTEIOT1_ETAT_INITIAL_A_ZERO

/*** DEFINITION DU PILOTE I2C ***/
/**
 * @brief Définition qui assigne le bon numéro de broche à la ligne SCL du \ref xpiloteI2C1.h
*/
#define PILOTEI2C1_SCL    22
/**
 * @brief Définition qui assigne le bon numéro de broche à la ligne SDA du \ref xpiloteI2C1.h
*/
#define PILOTEI2C1_SDA    23
/**
 * @brief Défini la fréquence en Hz de l'horloge I2C
 * 
 */
#define PILOTEI2C1_FREQUENCE_D_HORLOGE_EN_HZ 400000

//#define PILOTEESPNOW_BRODCASTADRESS[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};


//*** Define pour les interfaces ***//

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
#define SERVICEBASEDETEMPS_NOMBRE_DE_PHASES 2


/**
 * @brief Numéro de phase la lecture de l'Entrée 1 
 */
#define INTERFACEENTREE1_PHASE 0
/**
 * @brief Numéro de phase du processus clignotant
 */
#define PROCESSUSCLIGNOTANT_PHASE 1


#define PROCESSUSCLIGNOTANT_TEMPS_ALLUME_EN_MS 500
#define PROCESSUSCLIGNOTANT_TEMPS_ETEINT_EN_MS 500


#endif
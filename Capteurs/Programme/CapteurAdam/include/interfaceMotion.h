#ifndef INTERFACEMOTION_H
#define INTERFACEMOTION_H

//MODULE: interfaceMotion
//DESCRIPTION: pour s'interfacer avec l'entree 1
//L'etat de l'entree est lu periodiquement et les decisions rendues par rapport a
//son etat se basent sur un nombre minimum de lectures afin de reduire les risques
//d'erreurs causees par des rebondissements ou du bruit.
//La periode de la frequence INTERFACEMOTION_FREQUENCE_DES_LECTURES_EN_HZ des lectures 
//du bouton doit etre un multiple de la periode frequence de la base de temps utilisee.
//Dit autrement, la frequence de la base de temps utilisee doit etre un multiple de
//la frequence INTERFACEMOTION_FREQUENCE_DES_LECTURES_EN_HZ
//Le nombre minimum de lectures est donne par
//INTERFACEMOTION_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION

//HISTORIQUE:
// 2021-04-04, Yves Roy, creation

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define INTERFACEMOTION_VALEUR_LUE_SI_ACTIVE  1   
//#define INTERFACEMOTION_VALEUR_LUE_SI_INACTIVE 0
//#define INTERFACEMOTION_FREQUENCE_DES_LECTURES_EN_HZ  250
//#define INTERFACEMOTION_NOMBRE_MINIMUM_DE_LECTURES_PAR_DECISION 10

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define INTERFACEMOTION_PHASE 0

//INFORMATION PUBLIQUE:
//Definitions publiques:


#define INTERFACEMOTION_MODULE_EN_FONCTION 1
#define INTERFACEMOTION_MODULE_PAS_EN_FONCTION 0
#define INTERFACEMOTION_INFORMATION_DISPONIBLE 1
#define INTERFACEMOTION_INFORMATION_TRAITEE 0
#define INTERFACEMOTION_INACTIVE 0
#define INTERFACEMOTION_ACTIVE  1
#define INTERFACEMOTION_PAS_EN_FONCTION 2

/// @brief Structure public qui permet de savoir et de changer l'état du module  
typedef struct
{
  unsigned char etatDuModule;  
  unsigned char information;
  unsigned char etatDeLEntree;
} INTERFACEMOTION;

//Fonctions publiques:
void interfaceMotion_initialise(void);

//Variables publiques:
extern INTERFACEMOTION interfaceMotion;

#endif

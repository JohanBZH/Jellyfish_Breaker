#pragma once  //lire une seule fois le fichier
#include <stdlib.h>
#include <SDL2/SDL.h>

//structure dimensions de l'écran
typedef struct {
	int height;
	int width;
	int center;
	int middle;
}ScreenSize;

extern ScreenSize screenSize;
extern SDL_Rect screenRect;


//Lancement du jeu
extern int launch;

//Position du background
extern float xBackground;


//position de la balle dessiné dans drawGame()
extern float x;
extern float y;
extern float vx;
extern float vy;
//position de la balle dessiné dans tutoBall()
extern int xTuto;
extern int yTuto;
extern int vxTuto;
extern int vyTuto;
//Position initiale des briques
extern int xScan;
extern int yScan;
//position de la tortue
extern int xRect;
extern int yRect;
//position bouton level easy
extern int xeasy;
extern int yeasy;
//position bouton level medium
extern int xmedium;
extern int ymedium;
//position bouton level hard
extern int xhard;
extern int yhard;
//position bouton quit
extern int xquit;
extern int yquit;
//position bouton Settings
extern int xSettings;
extern int ySettings;
//position bouton retour
extern int xReturn;
extern int yReturn;
//position bouton retour depuis jeu
extern int xReturnGame;
extern int yReturnGame;

//table des positions de la balle
extern int positionEcho[2][1000];

//vitesse de la tortue
extern int speedTortue;
//vitesse de la balle
extern int speedVar;
//angle du rebond en degrés. Initialisation à 60°
extern double angle;
//angle de la direction de la balle
extern double angleBall;
//Nombre de vies
extern int nbVie;
extern int xheartInit;
extern int xheart;
extern int yheart;
//Level choisi
extern int numLevel;
//index briques supprimées par les briques rouges
extern int indexBoum;

//compteur nombre de comètes
extern int nbComet;
//position compteur comètes
extern int xCometInit;
extern int xComet;
extern int yComet;
//activation pouvoir brique verte
extern int compteurGreen;
extern int boucleSonComet;
extern int sonCometJoue;
//compteur de boucle
extern int loop;
extern int loopMoove;
//Décalage des briques dans le niveau 2
extern int decalage;
//variable d'activation de la fonction pause
extern int pauseSwitch;

//active ou désactive la musique de background
extern int backgroundMusicSwitch;

//active ou non le déplacement de la tortue via keyPressed et keyUp
extern int deplacementGauche;
extern int deplacementDroite;

//Structure pour récupérer les dimensions de l'image
SDL_Rect hitBoxSizeJellyfish();
SDL_Rect hitBoxSizeTurtle();
SDL_Rect hitBoxSizeBackground();

//Initialise toutes les variables de position
void initPositions();
#include <stdlib.h>
#include <SDL2/SDL.h>

#pragma once  //lire une seule fois le fichier

//Lancement du jeu
extern int launch;
//position de la balle dessiné dans drawGame()
extern float x;
extern float y;
extern float vx;
extern float vy;
//Position initiale des briques
extern int xScan;
extern int yScan;
//position de la tortue
extern int xRect;
extern int yRect;
//position bouton level easy
extern int xeasy;
extern int yeasy;
//position bouton level hard
extern int xhard;
extern int yhard;
//couleur de la balle de base
extern int r;
extern int g;
extern int b;
//variable de la vitesse
extern int speedVar;
//angle du rebond en degrés. Initialisation à 60°
extern float angle;
//Nombre de vies
extern int nbVie;
extern int xheart;
extern int yheart;
//Level choisi
extern int numLevel;

//active ou non le déplacement de la tortue via keyPressed et keyUp
extern int deplacementGauche;
extern int deplacementDroite;

//Structure pour récupérer les dimensions de l'image
SDL_Rect hitBoxSizeJellyfish();
SDL_Rect hitBoxSizeTurtle();
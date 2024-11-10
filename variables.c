#include "variables.h"
#include "sdl_helper/function.h"
#include "niveaux.h"
#include "game.h"
#include <stdlib.h>
#include <SDL2/SDL.h>

//Dimensions de l'écran
int largeurEcran = 1400;
int hauteurEcran = 1000;
//Lancement du jeu
int launch=0;
//position de la balle dessiné dans drawGame()
float x = 700;
float y = 700;
float vx=cos(60*(3.14/180))*5;
float vy=-(60*(3.14/180))*5;
//Position initiale des briques
int xScan=250;
int yScan=100;
//position de la tortue
int xRect=600;
int yRect=920;
//position bouton level easy
int xeasy=500;
int yeasy=750;
//position bouton level medium
int xmedium=675;
int ymedium=750;
//position bouton level hard
int xhard=850;
int yhard=750;
//position bouton quit
int xquit=1200;
int yquit=900;
//variable de la vitesse
int speedVar=9;
//angle du rebond en degrés. Initialisation à 60°
float angle=60;
//Nombre de vies
int nbVie=3;
int xheart=10;
int yheart=10;
//Level choisi
int numLevel;
//index briques supprimées par les briques rouges
int indexBoum;
//compteur nombre de comètes
int nbComet;
//position compteur comètes
int xComet=1350;
int yComet=10;
//activation pouvoir brique verte
int compteurGreen=0;
//compteur de boucle
int loop=0;
//variable d'activation de la fonction pause
int pauseSwitch=1;

//active ou non le déplacement de la tortue via keyPressed et keyUp
int deplacementGauche=0;
int deplacementDroite=0;

//Structure pour récupérer les dimensions des images
SDL_Rect hitBoxSizeJellyfish(){
    SDL_Rect hitBox;
    sprite3(0,0,"sdl_helper/sprites/jellyfish.bmp",&hitBox.w, &hitBox.h);
    return hitBox;
}

SDL_Rect hitBoxSizeTurtle(){
    SDL_Rect hitBox;
    sprite3(0,0,"sdl_helper/sprites/turtle.bmp",&hitBox.w, &hitBox.h);
    return hitBox;
}
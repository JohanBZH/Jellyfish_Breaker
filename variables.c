#include "variables.h"
#include "niveaux.h"
#include "function.h"
#include <stdlib.h>
#include <SDL2/SDL.h>

//Lancement du jeu
int launch=0;
//position de la balle dessiné dans drawGame()
float x = 500;
float y = 700;
float vx=cos(60*(3.14/180))*5;
float vy=-(60*(3.14/180))*5;
//Position initiale des briques
int xScan=50;
int yScan=100;
//position de la tortue
int xRect=400;
int yRect=920;
//position bouton level easy
int xeasy=300;
int yeasy=750;
//position bouton level medium
int xmedium=475;
int ymedium=750;
//position bouton level hard
int xhard=650;
int yhard=750;
//position bouton quit
int xquit=500;
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

//active ou non le déplacement de la tortue via keyPressed et keyUp
int deplacementGauche=0;
int deplacementDroite=0;

//Structure pour récupérer les dimensions des images
SDL_Rect hitBoxSizeJellyfish(){
    SDL_Rect hitBox;
    sprite3(0,0,"jellyfish.bmp",&hitBox.w, &hitBox.h);
    return hitBox;
}

SDL_Rect hitBoxSizeTurtle(){
    SDL_Rect hitBox;
    sprite3(0,0,"turtle.bmp",&hitBox.w, &hitBox.h);
    return hitBox;
}
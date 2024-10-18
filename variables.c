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
int xeasy=100;
int yeasy=600;
//position bouton level hard
int xhard=500;
int yhard=600;
//couleur de la balle de base
int r=247;
int g=146;
int b=1;
//variable de la vitesse
int speedVar=5;
//angle du rebond en degrés. Initialisation à 60°
float angle=60;
//Nombre de vies
int nbVie=3;
int xheart=10;
int yheart=10;

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

SDL_Rect hitBoxLevelEasy(){
    SDL_Rect hitBox;
    sprite3(0,0,"easy.bmp",&hitBox.w, &hitBox.h);
    return hitBox;
}

SDL_Rect hitBoxLevelHard(){
    SDL_Rect hitBox;
    sprite3(0,0,"hard.bmp",&hitBox.w, &hitBox.h);
    return hitBox;
}
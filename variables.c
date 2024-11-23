#include "variables.h"
#include "sdl_helper/function.h"
#include "niveaux.h"
#include "game.h"
#include <stdlib.h>
#include <SDL2/SDL.h>

//Milieu de l'écran
float screenCenter=0;

//Lancement du jeu
int launch;

//Position du background
float xBackground;
//position de la balle dessiné dans drawGame()
float x;
float y = 700;
float vx=cos(60*(3.14/180))*10;
float vy=-(60*(3.14/180))*10;
//position de la balle dessiné dans tutoBall()
int xTuto;
int yTuto = 400;
int vxTuto=1;
int vyTuto=0;
//Position initiale des briques
int xScan;
int yScan=100;
//position de la tortue
int xRect;
int yRect=920;
//position bouton level easy
int xeasy;
int yeasy=750;
//position bouton level medium
int xmedium;
int ymedium=750;
//position bouton level hard
int xhard;
int yhard=750;
//position bouton quit
int xquit;
int yquit=900;
//position bouton Settings
int xSettings;
int ySettings=920;
//position bouton retour depuis settings
int xReturn;
int yReturn=50;
//position bouton retour depuis jeu
int xReturnGame;
int yReturnGame=850;

//table des positions de la balle
int positionEcho[2][1000];

//vitesse de la tortue
int speedTortue =15;
//vitesse de la balle
int speedVar=10;
//angle du rebond en degrés. Initialisation à 60°
double angle=60;
//angle de la direction de la balle
double angleBall;
//Nombre de vies
int nbVie=3;
int xheartInit;
int xheart;
int yheart=10;
//Level choisi
int numLevel;
//index briques supprimées par les briques rouges
int indexBoum;
//compteur nombre de comètes
int nbComet;
//position compteur comètes
int xCometInit;
int xComet;
int yComet=10;
//activation pouvoir brique verte
int compteurGreen=0;
int boucleSonComet=1;
int sonCometJoue=1;

//compteur de boucle
int loop;
int loopMoove;
//Décalage des briques dans le niveau 2
int decalage=25;
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

void initPositions(){
    x = screenCenter;
    xTuto = screenCenter-300;
    xScan=screenCenter-450;
    xRect=screenCenter-100;
    xeasy=screenCenter-200;
    xmedium=screenCenter-25;
    xhard=screenCenter+150;
    xquit=screenCenter+520;
    xSettings=screenCenter-670;
    xReturn=screenCenter-715;
    xReturnGame=screenCenter+525;
    xheartInit=screenCenter-715;
    xCometInit=screenCenter+675;
    xBackground=screenCenter-700;
}
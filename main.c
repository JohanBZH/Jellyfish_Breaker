#include <SDL2/SDL.h>
#include <unistd.h>
#include "function.h"
#include "variables.h"
#include "niveaux.h"
#include <time.h>
#include <math.h>

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000
#define FPS 60

/*Compiler :
gcc main.c function.c variables.c niveaux.c -o main.out -lSDL2main -lSDL2 -lm
lm pour la librairie "math"

//faire une barre de score, incrémenter un score pour chaque brique cassée. Briques rouges points *10
//créer différents niveaux
// créer des balles avec des super pouvoir (genre traverser les briques et les supprimer jusqu'à retoucher la tortue 
*/

//imprime les briques
void jellyfish(int a, int b){   
    sprite(a,b,"jellyfish.bmp");   
}

void jellyfishPrint(){
    for (int j=0;j<100;j++){
      if (niveau1[2][j]==1){
        jellyfish(niveau1[0][j],niveau1[1][j]);        
      }
    }
}

//fait rebondir contre la brique et la supprime

void interaction(){
   SDL_Rect hitBoxJellyfish = hitBoxSizeJellyfish(); //va récupérer les dimensions de l'image pour les hitBox
   SDL_Rect hitBoxTurtle = hitBoxSizeTurtle();

    for (int j=0;j<100;j++){
//coordonnées du coin haut gauche de la brique
      int xtest=niveau1[0][j]; 
      int ytest=niveau1[1][j];
//position précédente de la balle
      int a=x-vx;
      int b=y-vy;
//chemin entre les 2 positions de la balle
      float R = sqrt(pow((x-a),2)+(pow((y-b),2)));
//tester toutes les positions intermédiaires
      for (int i=0;i<=(int)R;i++){
          a=a+i;
          b=b+i;
        //contact par le bas
          if ((vy<0) && ((b<=(ytest+hitBoxJellyfish.h)) && ((((a+10)>=(xtest)) && ((a+10)<=(xtest+hitBoxJellyfish.w)))))){   
              if ((niveau1[2][j])==1){
               printf("Bas atteint\n");
               printf("Bas a :%d b :%d xtest : %d ytest : %d \n", a,b,xtest,ytest );
                vy=vy*-1;
                niveau1[2][j]=0;
                y=(ytest+hitBoxJellyfish.h+1);
                x=a;
              }
          }
        //contact par le haut
          else if ((vy>0) && ((b+20)<=(ytest)) && (((a+10)>=(xtest)) && ((a+10)<=(xtest+hitBoxJellyfish.w)))){
              if ((niveau1[2][j])==1){  
          printf("Haut atteint\n");
           printf("Haut a :%d b :%d xtest : %d ytest : %d \n", a,b,xtest,ytest );
                vy=vy*-1;
                niveau1[2][j]=0;
                y=(ytest-21);
                x=a;
              }
          }
        //contact par la gauche
          else if ((vx>0) && (((a+20)>=(xtest)) && ((a+10)<=(xtest+hitBoxJellyfish.w))) && (((b+10)>=(ytest)) && ((b+10)<=(ytest+hitBoxJellyfish.h)))){
              if ((niveau1[2][j])==1){  
                        printf("Gauche atteint\n");
               printf("Gauche a :%d b :%d xtest : %d ytest : %d \n", a,b,xtest,ytest );
                vx=vx*-1;
                niveau1[2][j]=0;
                x=(xtest-21);
                y=b;
              }                                  
          }
        //contact par la droite
          else if ((vx<0) && ((a>=(xtest)) && (a<=(xtest+hitBoxJellyfish.w))) && (((b+10)>=(ytest)) && ((b+10)<=(ytest+hitBoxJellyfish.h)))){
              if ((niveau1[2][j])==1){  
                        printf("Droite atteint\n");
               printf("Droite a :%d b :%d xtest : %d ytest : %d \n", a,b,xtest,ytest );
                vx=vx*-1;
                niveau1[2][j]=0;
                x=(xtest+hitBoxJellyfish.w+1);
                y=b;
              }                
          }
          else{}
      }
    }
}

void gameEnd(){
    int gameOn=0;
    for (int j=0;j<100;j++){
      if (niveau1[2][j]==1){
        gameOn=1;
      }     
    }
    switch (gameOn){
      case 1:
      gameOn=0;
      break;
      case 0:
          sprite (0,0,"win.bmp");
          actualize();
          usleep(200000000 / FPS);
          freeAndTerminate(); 
      }
}

void background(){
    sprite(0,0,"background.bmp");
}

void vie(){
    nbVie=nbVie-1;
        if (nbVie>=0){
        x=500;
        y=800;
        sprite (0,0,"goAgain.bmp");  //image à créer
        actualize();
        usleep(100000000 / FPS);
        vx=4;
        vy=-4;
        speedVar=5;
      }  
      else{
        sprite (0,0,"lost.bmp");
        actualize();
        usleep(200000000 / FPS);
        freeAndTerminate();
      }
}
void printVie(){
    for (int i=0;i<=(nbVie);i++){
        xheart=10+50*i;
        sprite(xheart,yheart,"heart.bmp");
    }
}

//vecteur de déplacement. Angle en degré converti en radians
void vecteurSpeed(){
    float rad = angle*(3.14/180);  
    vx=cos(rad)*speedVar;
    vy=sin(rad)*speedVar;
}

void speed(){
    x=x+vx;
    y=y+vy;
}
//interactions avec les bords et la tortue.
  //faire évoluer la fonction speed en fonction des rebonds     
    //créer un gradient de 0 à 100 pour modifier l'angle entre 30° et 60°, utiliser la fonction speed
    
void rebondTortue(){
    if(y>(yRect-8) && y<(yRect+10) && x>(xRect-20) && x<=(xRect+80)){
      float posRebond;
      posRebond = (x-xRect) / 100;
      angle=30+posRebond*30;   //fait évoluer l'angle entre 30 et 60 suivant la position sur la barre
      vecteurSpeed();
      vy=vy*-1;
        if (vx>0){
          vx=vx*-1;
        }
        else {}
      y=yRect-10;
    }
    
    //centre, pas de modification de la direction
    else if((y>(yRect-8)) && y<(yRect+10) && x>(xRect+80) && x<(xRect+120)){
      angle=60;
      vecteurSpeed();
      vy=vy*-1;
      y=yRect-10;
    }
    //droite, renvoyer vers la droite
    else if(y>(yRect-8) && y<(yRect+10) && x>=(xRect+120) && x<(xRect+200)){
      float posRebond;
      posRebond = (x-(xRect+120)) / 80;
      angle=30+posRebond*30;   //fait évoluer l'angle entre 30 et 60 suivant la position sur la barre
      vecteurSpeed();
      vy=vy*-1;
        if (vx<0){
          vx=vx*-1;
        }
        else {}
      y=yRect-10;
    }
}

void rebondBords(){
    if (x>(979)){   //window_width-rayon de la balle-1 pour éviter le contact
      vx=vx*-1;         //renvoie dans l'autre sens
      x=979;
    }
    else if(x<1){
      vx=vx*-1;
      x=1;
    }
    else if(y<11){
      vy=vy*-1;
      y=11;
    }

    else if (y>(yRect-8) && y<(yRect+10) && x>(xRect-20) && x<=(xRect+200)) {
      rebondTortue();
    }
    else if (y>1000){
      vie();
    }
    else {}
}


//Déplacement de la raquette
void turtle(){
    int vMax=30;
    int vMin=10;
    int vTurtle=vMin;
    if (deplacementGauche==1){
      xRect=xRect-2*vTurtle;
    }
    else if (deplacementDroite==1){
      xRect=xRect+2*vTurtle;    
    }
    if(xRect<0){
      xRect=0;
    }
    else if(xRect>800){
      xRect=800;
    }
    sprite(xRect,yRect,"turtle.bmp");
}

void waterDrop(){
    if (vx<0 && vy<0){
        sprite(x,y,"waterDrophg.bmp");
    }
    else if (vx<0 && vy>0){
        sprite(x,y,"waterDropbg.bmp");
    }
    if (vx>0 && vy<0){
        sprite(x,y,"waterDrophd.bmp");
    }
    else if (vx>0 && vy>0){
        sprite(x,y,"waterDropbd.bmp");
    }
}

void drawGame(){
    clear();
    background();
    printVie();
    speed();
    jellyfishPrint();
    interaction();
    rebondBords();
    waterDrop();
    turtle();
    actualize();
    usleep(1000000 / FPS); // 60 images par seconde | 1000000 = 1 seconde
    gameEnd();
}
void KeyPressed(SDL_Keycode touche){
   
    switch (touche) {
        case SDLK_q:
            deplacementGauche=1;
            break;
        case SDLK_d:
            deplacementDroite=1;
            break;         
                    
        case SDLK_p:
            speedVar=speedVar+1;
            if (speedVar>=21){
              speedVar=20;
            }
              if(vx<0){
                vecteurSpeed();
                vx=vx*-1;
              }
              if(vy<0){
                vecteurSpeed();
                vy=vy*-1;
              }
            break;
        case SDLK_m:
            speedVar=speedVar-1;
            if (speedVar<=5){
              speedVar=5;
            }
              if(vx<0){
                vecteurSpeed();
                vx=vx*-1;
              }
              if(vy<0){
                vecteurSpeed();
                vy=vy*-1;
              }
            break;
        case SDLK_SPACE:
            launch=1;
            ;
            break;
        case SDLK_ESCAPE:
            freeAndTerminate();
            break;
        default:
            break;
    }
}

void KeyUp(SDL_Keycode touche){
   
    switch (touche) {
        case SDLK_q:
            deplacementGauche=0;
            break;
        case SDLK_d:
            deplacementDroite=0;
            break;
        default:
            break;
    }
}

void gameLauncher (){
    if (launch==0) {
        sprite (0,0,"launch.bmp");
        actualize();
    }
    else{drawGame();
    }
}

void gameLoop() {   //pour gérer de façon plus fluide le déplacement de la tortue et éviter le buffer de keydown, modifier une variable à keydown ET keyup.
    int programLaunched = 1;
    while (programLaunched == 1) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    // quand on clique sur fermer la fénêtre en haut à droite
                    programLaunched = 0;
                    break;
                case SDL_KEYDOWN:
                    KeyPressed(event.key.keysym.sym);
                    break;
                case SDL_KEYUP:
                    KeyUp(event.key.keysym.sym);
                    break;
                default:
                    break;
            }
        }
        gameLauncher();
    }
}



int main(){
    /** @description 3 fonctions dans le main qui permettent de créer l'application et la maintenir ouverte :
     *  init(...) : initialiser la SDL/ fenêtre
     *  gameLoop() : boucle de jeu dans laquelle l'application reste ouverte
     *  freeAndTerminate() : quitte le programme proprement
     */
    init(WINDOW_WIDTH, WINDOW_HEIGHT);
    init_game();
    gameLoop();
    printf("Fin du programme\n");
    freeAndTerminate();
}

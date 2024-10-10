#include <SDL2/SDL.h>
#include <unistd.h>
#include "function.h"
#include <time.h>

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000
#define FPS 60

//créer des briques et faire disparaître les briques au rebond (tableau)
//sectoriser la barre (rebond normal sur la moitiée du milieu et renvoi dans la même direction pour les quarts des côtés.
//pb : flickering

//position de la balle dessiné dans drawGame()
int x = 500;
int y = 800;
int vx=2;
int vy=-2;
//position du rectangle
int xRect=10;
int yRect=920;
int vxRect=1;  //vitesse de la raquette
//couleur de la balle de base
int r=247;
int g=146;
int b=1;
//position de la raquette
int a=10;
//variable de la vitesse
int speedVar=1;

int presenceObjet[3][100];   //table pour stocker les coordonnées et présence d'ennemis sur la case
int nbEnemy; //défini si rocher, enemy ou rien
int indexInteraction; //index pour générer une interaction avec les obstacles

void couleurAleatoire(){
      r=rand()%256;
      g=rand()%256;
      b=rand()%256;
}

void init_game(){
  int index=0;
  int xScan=0;
  int yScan=0;
  for (int i=0;i<5;i++){  //deux boucles de for pour scanner la grille (10x10)
    yScan=yScan+50*i;
    for (int j=0;j<20;j++){
      xScan=xScan+50*j;
      for (int i=0;i<3;i++){   //pour chaque cellule, enregistre les coordonnées et initialise présence d'une brique
        if (i==0){       
          presenceObjet[i][index]=xScan;
        }
        else if(i==1){
          presenceObjet[i][index]=yScan; 
        }
        else{
          presenceObjet[i][index]=1;
        }
      }
    index=index+1;
    xScan=0;
    }
  yScan=0;
  }
}

void jellyfish(int a, int b){
    sprite(a,b,"jellyfish.bmp");
}
//imprimer les briques. Pb première cellule ne s'affiche pas. dans le tableau presence, bien mis à 1
void jellyfishPrint(){
    for (int j=0;j<100;j++){
      if (presenceObjet[2][j]==1){
        jellyfish(presenceObjet[0][j],presenceObjet[1][j]);
      }
    }
  actualize();
}

void interaction(){  //fait rebondir contre la brique et la supprime
    for (int j=0;j<100;j++){
      int xtest=presenceObjet[0][j];  //passage par des variables pour éviter un bug dans le if
      int ytest=presenceObjet[1][j];
        if (x>=xtest && x<(xtest+50) && y>=ytest && y<(ytest+50)){
          indexInteraction=j;
        if ((presenceObjet[2][indexInteraction])==1){ 
          presenceObjet[2][indexInteraction]=0;
        }
      }
    }
}

void background(){
    sprite(0,0,"background.bmp");
}

void speed(){
    x=x+vx*speedVar;
    y=y+vy*speedVar;
}

//interactions avec les bords, créer interaction avec briques
void rebond(){
    if (x>(989)){   //window_width-rayon de la balle-1 pour éviter le contact
      vx=vx*-1;         //renvoyer dans l'autre sens
      couleurAleatoire();
      vxRect=vxRect*-1;
    }
    else if(x<11){
      vx=vx*-1;
      vxRect=vxRect*-1;
      couleurAleatoire();
    }
    else if(y<11){
      couleurAleatoire();
      vy=vy*-1;
    }
    else if(y>(yRect-8) && x>xRect && x<(xRect+200)){  //hit box à affiner
      vy=vy*-1;
      couleurAleatoire();
    }
    else if(y>1000){
      sprite (350,395,"Lost.bmp");
      actualize();
      usleep(100000000 / FPS);
      freeAndTerminate();
    }
}

void raquette(){
    changeColor(247,146,1);
    if(xRect<0){
      xRect=0;
    }
    else if(xRect>800){
      xRect=800;
    }
    sprite(xRect,yRect,"turtle.bmp");
    usleep(100000 / FPS);
}

void drawGame(){
    clear();
    background();
    speed();
    jellyfishPrint();
    interaction();
    rebond();
    changeColor(r,g,b);
    drawCircle(x,y,10);
    raquette();
    actualize();
    usleep(500000 / FPS); // 60 images par seconde | 1000000 = 1 seconde
}
void KeyPressed(SDL_Keycode touche){
   
    switch (touche) {
        case SDLK_q:
            xRect=xRect-40;
            break;
        case SDLK_d:
            xRect=xRect+40;
            break;
        case SDLK_p:
            speedVar=speedVar+2;
            if (speedVar>=15){
              speedVar=14;
            }
            break;
        case SDLK_m:
            speedVar=speedVar/2;
            if (speedVar==0){
              speedVar=1;
            }
            break;
        case SDLK_ESCAPE:
            freeAndTerminate();
            break;
        default:
            break;
    }
}

void gameLoop() {
    int programLaunched = 1;
    while (programLaunched == 1) {
        /* Boucle pour garder le programme ouvert lorsque programLaunched est different de 1
        on sort de la boucle, donc de la fonction*/
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            // boucle pour la gestion d'évenement
            switch (event.type) {
                /** event.type renvoi le type d'evenement qui se passe
                 * (si on appuie sur une touche, clique de souris...)
                 * en fonction du type d'évènement on à alors
                 * différentes information accessibles
                 * voir doc pour plus d'event https://wiki.libsdl.org/SDL_EventType
                 */
                case SDL_QUIT:
                    // quand on clique sur fermer la fénêtre en haut à droite
                    programLaunched = 0;
                    break;
                case SDL_KEYDOWN:
                    KeyPressed(event.key.keysym.sym);
                    break;
                default:
                    break;
            }
        }
        drawGame();
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

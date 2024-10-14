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
int vx=4;
int vy=-4;
//position de la tortue
int xRect=10;
int yRect=920;
//couleur de la balle de base
int r=247;
int g=146;
int b=1;
//variable de la vitesse
int speedVar=1;

//active ou non le déplacement de la tortue via keyPressed et keyUp
int deplacementGauche=0;
int deplacementDroite=0;

int presenceObjet[3][100];   //table pour stocker les coordonnées et présence d'ennemis sur la case
int nbEnemy; //défini si rocher, enemy ou rien

void couleurAleatoire(){
      r=rand()%256;
      g=rand()%256;
      b=rand()%256;
}
//crée le tableau qui enregistre la position des briques et pilote leur présence
void init_game(){
  int index=0; //n° de cellule
  //coordonnées de la cellule
  int xScan=0;
  int yScan=100;
  for (int i=0;i<5;i++){  //deux boucles de for pour scanner la grille
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
  yScan=100;
  }
}

//imprimer les briques. Pb première cellule ne s'affiche pas. Dans le tableau présence, la première cellule indique bien une brique
void jellyfish(int a, int b){
    sprite(a,b,"jellyfish.bmp");
}

void jellyfishPrint(){
    for (int j=0;j<100;j++){
      if (presenceObjet[2][j]==1){
        jellyfish(presenceObjet[0][j],presenceObjet[1][j]);
      }
    }
}
//fait rebondir contre la brique et la supprime
//hitbox de la balle : rect de 20 de large (coordonnées x et y + ou -10)

void interaction(){
   
    for (int j=0;j<100;j++){
      int xtest=presenceObjet[0][j];  //coordonnées du coin haut gauche de la brique
      int ytest=presenceObjet[1][j];  //passage par des variables pour éviter un bug dans le if. Scanne bien tout le tableau. Border X ET Y pour la condition de rebond
      //contact par le bas
               //       printf("bas x %d, y %d xtest %d et ytest %d\n",x,y,xtest,ytest);
        if ((vy<1) && ((y-10)<=(ytest+50)) && (((x-10)>=(xtest)) && ((x-10)<=(xtest+50)))){                         
          if ((presenceObjet[2][j])==1){          
            vy=vy*-1;
            presenceObjet[2][j]=0;
            y=(ytest+61); 
          }
        }
      //contact par le haut
        if ((vy>1) && ((y-10)<=(ytest)) && (((x-10)>=(xtest-10)) && ((x-10)<=(xtest+50)))){
          if ((presenceObjet[2][j])==1){          
            vy=vy*-1;
            presenceObjet[2][j]=0;
            y=(ytest-11); 
          }
        }
      //contact par la gauche
        if ((vx>1) && ((x+10)>=(xtest)) && ((x+10)<=(xtest+50)) && (((y-10)>=(ytest)) && ((y-10)<=(ytest+50)))){
          if ((presenceObjet[2][j])==1){          
            vx=vx*-1;
            presenceObjet[2][j]=0;
            x=(xtest-11);
          }                                  
        }
      //contact par la droite
        if ((vx<1) && ((x+10)>=(xtest)) && ((x-10)<=(xtest+50)) && (((y-10)>=(ytest)) && ((y-10)<=(ytest+50)))){
          if ((presenceObjet[2][j])==1){          
            vx=vx*-1;
            presenceObjet[2][j]=0;
            x=(xtest+61);
          }                
        } 
    }
}

void gameEnd(){
    int gameOn=0;
    for (int j=0;j<100;j++){
      if (presenceObjet[2][j]==1){   //ici 
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

void speed(){
    x=x+vx*speedVar;
    y=y+vy*speedVar;
}

//interactions avec les bords et la tortue
void rebond(){
    if (x>(989)){   //window_width-rayon de la balle-1 pour éviter le contact
      vx=vx*-1;         //renvoye dans l'autre sens
      x=989;
      //couleurAleatoire();
    }
    else if(x<11){
      vx=vx*-1;
      x=11;
      //couleurAleatoire();
    }
    else if(y<11){
      //couleurAleatoire();
      vy=vy*-1;
      y=11;
    }
    //comportement différent suivant là où on rebondi sur la tortue
    //quart à gauche, renvoyer vers la gauche
    else if(y>(yRect-8) && y<(yRect+10) && x>xRect && x<=(xRect+50)){
      vy=vy*-1;
        if (vx>0){
          vx=vx*-1;
        }
        else {}
      y=yRect-10;
      //couleurAleatoire();
    }
    //centre, pas de modification de la direction
    else if(y>(yRect-8) && y<(yRect+10) && x>(xRect+50) && x<(xRect+150)){
      vy=vy*-1;
      y=yRect-10;
      //couleurAleatoire();
    }
    //droite, renvoyer vers la droite
    else if(y>(yRect-8) && y<(yRect+10) && x>=(xRect+150) && x<(xRect+200)){
      vy=vy*-1;
        if (vx<0){
          vx=vx*-1;
        }
        else {}
      y=yRect-10;
      //couleurAleatoire();
    }
    else if(y>1000){
      sprite (0,0,"lost.bmp");
      actualize();
      usleep(200000000 / FPS);
      freeAndTerminate();
    }
}

void turtle(){
    changeColor(247,146,1);
    if (deplacementGauche==1){
      xRect=xRect-20;
    }
    else if (deplacementDroite==1){
      xRect=xRect+20;    
    }
    if(xRect<0){
      xRect=0;
    }
    else if(xRect>800){
      xRect=800;
    }
    sprite(xRect,yRect,"turtle.bmp");
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
    turtle();
    actualize();
    usleep(500000 / FPS); // 60 images par seconde | 1000000 = 1 seconde
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
            if (speedVar>=15){
              speedVar=14;
            }
            break;
        case SDLK_m:
            speedVar=speedVar-1;
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

void gameLoop() {   //pour gérer de façon plus fluide le déplacement de la tortue et éviter le buffer de keydown, modifier une variable à keydown ET keyup.
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
                case SDL_KEYUP:
                    KeyUp(event.key.keysym.sym);
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

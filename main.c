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

// créer des balles avec des super pouvoir (genre traverser les briques et les supprimer jusqu'à retoucher la tortue
//faire une barre de score, incrémenter un score pour chaque brique cassée.
*/



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

//selectionne le niveau en cliquant
void mouse(int xMouse, int yMouse){
   
    if (xMouse>=xeasy && xMouse<=(xeasy+50) && yMouse>=yeasy && yMouse<=yeasy+50) {
            launch=1;
            numLevel=0;
    }
    else if (xMouse>=xmedium && xMouse<=(xmedium+50) && yMouse>=ymedium && yMouse<=ymedium+50){
            launch=1;
            numLevel=1;
    }
    else if (xMouse>=xhard && xMouse<=(xhard+50) && yMouse>=yhard && yMouse<=yhard+50){
            launch=1;
            numLevel=2;
    }
    else if (xMouse>=xquit && xMouse<=(xquit+500) && yMouse>=yquit && yMouse<=yquit+100){
            freeAndTerminate();
    }
    else{
            launch=0;
    }
}

void gameLauncher (){
    if (launch==0) {
        sprite (0,0,"launch.bmp");
        sprite (300,600,"choose.bmp");
        sprite (xeasy,yeasy,"jellyfishGreen.bmp");
        sprite (xmedium,ymedium,"jellyfish.bmp");       
        sprite (xhard,yhard,"jellyfishRed.bmp");
        sprite (xquit,yquit,"quit.bmp");
        actualize();
    }
    else {
        drawGame();
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
                case SDL_MOUSEBUTTONUP:
                    mouse(event.motion.x, event.motion.y);
                    break;
                default:
                    break;
            }
        }
        gameLauncher();
    }
}



int main(){
    srand(time(NULL));
    init(WINDOW_WIDTH, WINDOW_HEIGHT);
    init_game();
    gameLoop();
    printf("Fin du programme\n");
    freeAndTerminate();
}

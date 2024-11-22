#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <unistd.h>
#include <time.h>
#include <math.h>

#include "game.h"
#include "variables.h"
#include "niveaux.h"
#include "menu.h"
#include "sdl_helper/function.h"
#include "sdl_helper/text_functions.h"
#include "sdl_helper/audio_functions.h"
#include "sdl_helper/constants.h"

/*Compiler :
gcc main.c game.c variables.c niveaux.c menu.c sdl_helper/audio_functions.c sdl_helper/constants.c sdl_helper/function.c sdl_helper/text_functions.c -o main.out -lSDL2main -lSDL2 -lm -lSDL2_mixer -lSDL2_ttf

lm > librairie "math"
 lSDL2_mixer > librairie audio
 lSDL2_ttf >librairie texte

Features à dev

Créer un écho de la comète

*/

void drawGame(){
    clear();
    convertAngle();
    background();
    printVie();
    echo();
    speed();
    jellyfishPrint();
    gameEnd();
    choixInteraction();
    rebondBords();
    waterDrop();
    sonComet();
    turtle();
    printNbComet();
    sprite (xquit,yquit,"sdl_helper/sprites/quit.bmp");
    textDrawText("Return Menu",1205,850,comfortaaFont_28);
    actualize();
    levelMoove();
    loop++;
    usleep(1000000 / FPS); // 60 images par seconde | 1000000 = 1 seconde

}

void KeyPressed(SDL_Keycode touche){
   
    switch (touche) {
        //pour gérer de façon fluide le déplacement de la tortue et éviter le buffer de keydown, Le déplacement de la tortue est activé à keyDown et neutralisé à keyUp
        case SDLK_q:
            deplacementGauche=1;
            break;
        case SDLK_d:
            deplacementDroite=1;
            break;  
        //activation du pouvoir de la comète
        case SDLK_s:
            if (nbComet>0){
                compteurGreen = vy<0 ? 1 : 2;
            }
            nbComet = (nbComet == 0) ? nbComet : nbComet-1;
            break; 

        //touche debug forçage comète
            case SDLK_g:
            compteurGreen=1;
            break;  

        //gestion de la vitesse de la balle          
        case SDLK_p:
            speedVar=speedVar+1;
            if (speedVar>=21){
                speedVar=20;
            }
            if(vx<0 && vy>0){
                vecteurSpeed();
                vx*=-1;
            }
            if(vx<0 && vy<0){
                vecteurSpeed();
                vx*=-1;
                vy*=-1;
            }
            break;
        case SDLK_m:
            speedVar=speedVar-1;
            if (speedVar<=10){
                speedVar=10;
            }
            if(vx<0 && vy>0){
                vecteurSpeed();
                vx*=-1;
            }
            if(vx<0 && vy<0){
                vecteurSpeed();
                vx*=-1;
                vy*=-1;
            }
            break;
        //Met en pause ou reprend
        case SDLK_SPACE:
            pauseSwitch*=-1;
            break;
        case SDLK_ESCAPE:
        audioCleanup();
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
   
    if (xMouse>=xeasy && xMouse<=(xeasy+75) && yMouse>=yeasy && yMouse<=yeasy+75) {
            launch=1;
            numLevel=0;
            fileLog(numLevel);
    }
    else if (xMouse>=xmedium && xMouse<=(xmedium+75) && yMouse>=ymedium && yMouse<=ymedium+75){
            launch=1;
            numLevel=1;
            fileLog(numLevel);
    }
    else if (xMouse>=xhard && xMouse<=(xhard+75) && yMouse>=yhard && yMouse<=yhard+75){
            launch=1;
            numLevel=2;
            fileLog(numLevel);
    }
    else if (xMouse>=xSettings && xMouse<=(xSettings+400) && yMouse>=ySettings && yMouse<=ySettings+100){
            launch=2;
    }
    else if (xMouse>=xquit && xMouse<=(xquit+500) && yMouse>=yquit && yMouse<=yquit+100){
            audioCleanup();
            freeAndTerminate();
    }
    //retour au menu depuis les settings
    else if (xMouse>=xReturn && xMouse<=(xReturn+400) && yMouse>=yReturn && yMouse<=yReturn+100){
            init_game();
    }
    //retour au menu depuis le jeu
    else if (xMouse>=1200 && xMouse<=(1400) && yMouse>=800 && yMouse<=900){
            init_game();
            nbVie=3;
    }
    else{}
}

void gameLauncher (){
    if (launch==0) {
        sprite (0,0,"sdl_helper/sprites/background.bmp");
        centeredText("WELCOME",300,comfortaaFont_52);    
        centeredText("TO",370,comfortaaFont_52);  
        centeredText("JELLYFISHY BREAKER",440,comfortaaFont_52);     
        centeredText("CHOOSE YOUR LEVEL",650,comfortaaFont_36);
        textDrawText("SETTINGS",xSettings,ySettings,comfortaaFont_36);
        sprite (xeasy,yeasy,"sdl_helper/sprites/jellyfishGreenBig.bmp");
        sprite (xmedium,ymedium,"sdl_helper/sprites/jellyfishBig.bmp");       
        sprite (xhard,yhard,"sdl_helper/sprites/jellyfishRedBig.bmp");
        sprite (xquit,yquit,"sdl_helper/sprites/quit.bmp");
        actualize();
    }
    else if (launch==2){
        settings();
    }
    else {
        drawGame();
    }
}

void gameLoop() {   
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

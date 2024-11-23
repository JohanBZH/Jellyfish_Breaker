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


void settings(){
    clear();
    background();
    turtle();
    tutoBall();
    spriteTuto();
    actualize();
    usleep(1000000 / FPS); // 60 images par seconde | 1000000 = 1 seconde
}

//tous les sprites et textes
void spriteTuto(){
    sprite (xquit,yquit,"sdl_helper/sprites/quit.bmp");
    sprite ((screenCenter-100),800,"sdl_helper/sprites/qKey.bmp");
    sprite (screenCenter,800,"sdl_helper/sprites/dKey.bmp");
    sprite ((screenCenter-250),200,"sdl_helper/sprites/speedTuto.bmp");
    sprite ((screenCenter-80),625,"sdl_helper/sprites/sKey.bmp");
    sprite ((screenCenter+20),650,"sdl_helper/sprites/comet.bmp"); 
    textDrawText("Return MENU",xReturn,yReturn,comfortaaFont_28);
    centeredText("'SPACE' to pause the game",550,comfortaaFont_36);
    drawLine((screenCenter-299), 400, (screenCenter-299),430);
    drawLine((screenCenter+300), 400, (screenCenter+300),430);
}

//faire rebondir la balle / activer comète
void tutoBall(){
    speedTuto();
    rebondBordsTuto();
    nbComet=1;
    if (compteurGreen==1){
        if (vxTuto>0 ){
            sprite(xTuto,yTuto,"sdl_helper/sprites/cometRight.bmp");
        }
        else if (vxTuto<0){
            sprite(xTuto,yTuto,"sdl_helper/sprites/cometLeft.bmp");
        }
    }
    else {
        if (vxTuto<0){
            sprite(xTuto,yTuto,"sdl_helper/sprites/waterDropLeft.bmp");
        }
        else if (vxTuto>0){
            sprite(xTuto,yTuto,"sdl_helper/sprites/waterDropRight.bmp");
        }
    }
}


//position de la balle
void speedTuto(){
    if (pauseSwitch==1){
		xTuto+=vxTuto*speedVar;        
    }
    else if (pauseSwitch==-1){
        fullCenteredText("PAUSED",comfortaaFont_52);
    }
    sprite ((screenCenter+100),250, "sdl_helper/sprites/speed.bmp");
    char speedChar[50];
    sprintf(speedChar,"%d",speedVar);
    textDrawText(speedChar,(screenCenter+170),258,comfortaaFont_28);
}

//Rebonds balle
void rebondBordsTuto(){
    if (xTuto>(screenCenter+270)){
      vxTuto*=-1;
      xTuto=(screenCenter+269);
    }
    else if(xTuto<(screenCenter-299)){
      vxTuto*=-1;
      xTuto=(screenCenter-299);
    }
}

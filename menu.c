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
    sprite ((screenSize.center-100),800,"sdl_helper/sprites/qKey.bmp");
    sprite (screenSize.center,800,"sdl_helper/sprites/dKey.bmp");
    sprite ((screenSize.center-250),200,"sdl_helper/sprites/speedTuto.bmp");
    sprite ((screenSize.center-80),625,"sdl_helper/sprites/sKey.bmp");
    sprite ((screenSize.center+20),650,"sdl_helper/sprites/comet.bmp"); 
    textDrawText("Return MENU",xReturn,yReturn,comfortaaFont_28);
    centeredText("'SPACE' to pause the game",550,comfortaaFont_36);
    drawLine((screenSize.center-299), 400, (screenSize.center-299),430);
    drawLine((screenSize.center+300), 400, (screenSize.center+300),430);
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
    sprite ((screenSize.center+100),250, "sdl_helper/sprites/speed.bmp");
    char speedChar[50];
    sprintf(speedChar,"%d",speedVar);
    textDrawText(speedChar,(screenSize.center+170),258,comfortaaFont_28);
}

//Rebonds balle
void rebondBordsTuto(){
    if (xTuto>(screenSize.center+270)){
      vxTuto*=-1;
      xTuto=(screenSize.center+269);
    }
    else if(xTuto<(screenSize.center-299)){
      vxTuto*=-1;
      xTuto=(screenSize.center-299);
    }
}

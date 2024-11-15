#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <unistd.h>
#include <time.h>
#include <math.h>

#include "game.h"
#include "variables.h"
#include "niveaux.h"
#include "sdl_helper/function.h"
#include "sdl_helper/text_functions.h"
#include "sdl_helper/audio_functions.h"
#include "sdl_helper/constants.h"


//menu à créer : retour à l'accueil / contrôle de la tortue / balle qui rebondi / pause
void settings();

//tous les sprites et textes
void spriteTuto();

//faire rebondir la balle / activer comète
void tutoBall();


//position de la balle
void speedTuto();
void rebondBordsTuto();

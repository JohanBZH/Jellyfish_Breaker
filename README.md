# Jellyfish breaker

Jellyfish breaker run on the [SDL_lib_v2](https://gitlab.com/ilanlo/sdl_lib_v2.git)

# Libs to install

    sudo aptitude install libsdl2-dev
    sudo aptitude install libsdl2-mixer-dev
    sudo aptitude install libsdl2-ttf-dev

SDL2 - for the display  
SDL2_mixer - for the sound  
SDL2_ttf - for the text  

To run the game the easy way, bash
    ./lancement.sh

To compile exemple.c:

Set yourself in Jellyfish breaker, then run :  
    gcc exemple.c sdl_helper/audio_functions.c sdl_helper/constants.c sdl_helper/function.c sdl_helper/text_functions.c -o main.out -lSDL2 -lSDL2main -lSDL2_mixer -lSDL2_ttf

To run the program :

    ./main.out

How to use it ?

In the file where you've put your main function, at the very beginning :

    #include "sdl_helper/function.h"
    #include "sdl_helper/text_functions.h"
    #include "sdl_helper/audio_functions.h"
    #include "sdl_helper/constants.h"

See directly in the sdl_helper files for the differents functions.

## NOTE 1

Only one audio can be played by channel. If you need multiple audio being played at the same time, you'll need to use different channels. The max channel number is set at 8 by default. It can be changed line 19 of constant.h : #define MAX_AUDIO_CHANNELS (int)  

When you play an audio and set the channel to -1, it will be set to the first free channel.  
Another way to do it is to use, audioSimpleLoadAndPlay(char* cheminVersFichierWAV).

## NOTE 2

audioCleanup() is to be used to correctly shutdown the sound manager. It is integrated to freeAndTerminate().
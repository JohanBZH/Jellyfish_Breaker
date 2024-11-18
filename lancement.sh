
#!/usr/bin/env bash
gcc main.c game.c variables.c niveaux.c menu.c sdl_helper/audio_functions.c sdl_helper/constants.c sdl_helper/function.c sdl_helper/text_functions.c -o main.out -lSDL2main -lSDL2 -lm -lSDL2_mixer -lSDL2_ttf
./main.out

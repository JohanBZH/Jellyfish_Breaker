
#include <stdlib.h>
#include <SDL2/SDL.h>

#ifndef SDL_CESI_FUNCTION_H //équivalent à dire "Si ce n'est pas fait, faire ce qu'il y a jusqu'au end". Equivalent à écrire #pragma once
#define SDL_CESI_FUNCTION_H

typedef struct Point {
    int x;
    int y;
} Point;


void init(int windowWidth, int windowHeight);

void freeWindow();

void freeRenderer();

void freeTexture(SDL_Texture *texture);

void freeAndTerminate();

void actualize();

void changeColor(int r, int g, int b);

void clear();

void drawSquare(int posX, int posY, int longueur);

void drawRect(int posX, int posY, int longueur, int hauteur);

void drawCircle(int centerX, int centerY, int rayon);

void drawPoint(int x, int  y);

void drawLine(int x0, int y0, int x1, int y1);

void drawLinePoints(Point point1, Point point2);

void sprite(int posX, int posY, char *imgSrc);

void sprite2(int posX, int posY, char *imgSrc, int *w,int *h);

void sprite3(int posX, int posY, char *imgSrc, int *w,int *h);

void lastKeyPressed(SDL_Event *event);

void jellyfish(int a, int b, int choixBrique);

void jellyfishPrint();

void interaction();

int indexBriquesCollisionRed (int xBriqueExplose, int yBriqueExplose);

void collisionRed();

void gameEnd();

void background();

void vie();

void printVie();

void vecteurSpeed();

void speed();

void rebondTortue();

void rebondBords();

void turtle();

void waterDrop();

#endif //SDL_CESI_FUNCTION_H

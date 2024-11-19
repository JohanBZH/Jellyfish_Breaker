#pragma once

void level0();

void level1();

void level2();

void redBricks();

void greenBricks();

//crée la structure des tableaux qui enregistrent la position des briques et pilote leur présence
struct Level {
  int tableLevel[3][100];
};

extern struct Level level[3];

//initialise la table des positions de la balle
void initPositionEcho();

//initialise la position de début de jeu
void initVar();

void init_game();
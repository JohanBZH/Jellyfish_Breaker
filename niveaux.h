#pragma once

void init_game();

void level0();

void level1();

void level2();

void redBricks();

//crée la structure des tableaux qui enregistrent la position des briques et pilote leur présence
struct Level {
  int tableLevel[3][100];
};

extern struct Level level[3];
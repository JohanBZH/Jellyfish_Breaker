#pragma once

extern int niveau1[3][72];   //table pour stocker les coordonnées et présence d'ennemis sur la case
extern int niveau2[3][90];

//crée le tableau qui enregistre la position des briques et pilote leur présence
void init_game();

void levelHard();

void levelEasy();
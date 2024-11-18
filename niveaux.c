#include "niveaux.h"
#include "variables.h"
#include "game.h"

//Déclare le nombre de niveaux
struct Level level[3];
//Table des index des briques rouges (10% des briques totales, max 100 briques)
  int indexredBricks[10];
//Table des index des briques vertes
  int indexgreenBricks[10];

//Génère aléatoirement un index compris dans le nombre de briques
void redBricks(int nbBrickMax){
  indexredBricks[0]=rand()%nbBrickMax;
  for (int i=1;i<(nbBrickMax*0.1);i++){
    indexredBricks[i]=rand()%nbBrickMax;
      for (int j=0;j<i;j++){
        while (indexredBricks[j]==indexredBricks[i]){
          indexredBricks[i]=rand()%nbBrickMax;
        }
      }
  }
}

//Génère aléatoirement un index compris dans le nombre de briques
void greenBricks(int nbBrickMax){
  //reset la table
  for (int i=0;i<10;i++){
    indexgreenBricks[i]=-1;
  }
  int intnbBrickMax=nbBrickMax*0.05; 

  for (int i=0;i<=(intnbBrickMax);i++){
    indexgreenBricks[i]= rand()%nbBrickMax; 

      for (int j=0;j<i;j++){
        if (indexgreenBricks[j]==indexgreenBricks[i] || indexgreenBricks[i] == indexredBricks[j]){
          indexgreenBricks[i]=rand()%nbBrickMax;
        }
      }
  }
}

void level0 (){
  int index=0;
  for (int i=0;i<4;i++){
    if (i%2==0){
      xScan=200;
      yScan=yScan+50*i;
      for (int j=0;j<9;j++){
        xScan=xScan+(2*50);
        for (int i=0;i<3;i++){
          if (i==0){
            level[0].tableLevel[i][index]=xScan;
          }
          else if(i==1){
            level[0].tableLevel[i][index]=yScan; 
          }
          else{
            level[0].tableLevel[i][index]=1;
          }
        }
      index=index+1;
      }
    }
    else{
      xScan=150;
      yScan=yScan+50*i;
      for (int j=0;j<9;j++){
        xScan=xScan+(2*50);
        for (int i=0;i<3;i++){
          if (i==0){
            level[0].tableLevel[i][index]=xScan;
          }
          else if(i==1){
            level[0].tableLevel[i][index]=yScan; 
          }
          else{
            level[0].tableLevel[i][index]=1;
          }
        }
      index=index+1;
      }
    }
  yScan=100;
  }
  //intégration des briques rouges
  redBricks(36);
  for (int i=0;i<(36*0.1);i++){
    level[0].tableLevel[2][indexredBricks[i]]=2;
  }
  //intégration des briques greens
  greenBricks(36);
  for (int i=0;i<(36*0.05);i++){
    level[0].tableLevel[2][indexgreenBricks[i]]=3;
  }
}


//table niveau medium
void level1 (){
  int index=0; //n° de cellule
  for (int i=0;i<3;i++){  //deux boucles de for pour scanner la grille
    xScan=250;
    yScan=yScan+100*i;
    for (int j=0;j<18;j++){
      xScan=xScan+50*j;
      for (int i=0;i<3;i++){   //pour chaque cellule, enregistre les coordonnées et initialise présence d'une brique
        if (i==0){
          level[1].tableLevel[i][index]=xScan;
        }
        else if(i==1){
          level[1].tableLevel[i][index]=yScan; 
        }
        else{
          level[1].tableLevel[i][index]=1;
        }
      }
    index=index+1;
    xScan=250;
    }
  yScan=100;
  }
  //intégration des briques rouges
  redBricks(54);
  for (int i=0;i<(54*0.1);i++){
    level[1].tableLevel[2][indexredBricks[i]]=2;
  }
 //intégration des briques greens
  greenBricks(54);
  for (int i=0;i<(54*0.05);i++){
    level[1].tableLevel[2][indexgreenBricks[i]]=3;
  }
}

//table niveau mobile
void level2 (){
  int index=0; //n° de cellule
  for (int i=0;i<4;i++){  //deux boucles de for pour scanner la grille
    xScan = (i%2==0) ? 250 : 500;
    yScan=yScan+80*i;
    for (int j=0;j<13;j++){
      xScan=xScan+50*j;
      for (int i=0;i<3;i++){   //pour chaque cellule, enregistre les coordonnées et initialise présence d'une brique
        if (i==0){
          level[2].tableLevel[i][index]=xScan;
        }
        else if(i==1){
          level[2].tableLevel[i][index]=yScan; 
        }
        else{
          level[2].tableLevel[i][index]=1;
        }
      }
    index=index+1;
    xScan = (i%2==0) ? 250 : 500;
    }
  yScan=100;
  }
  //intégration des briques rouges
  redBricks(52);
  for (int i=0;i<(52*0.1);i++){
    level[2].tableLevel[2][indexredBricks[i]]=2;
  }
 //intégration des briques greens
  greenBricks(52);
  for (int i=0;i<(52*0.05);i++){
    level[2].tableLevel[2][indexgreenBricks[i]]=3;
  }
}

void init_game(){
  level0();
  level1();
  level2();
  x = 700;
  y = 700;
  vx=cos(60*(3.14/180))*10;
  vy=-(60*(3.14/180))*10;
  launch=0;
  compteurGreen=0;
  nbComet=0;
  loop=1;
  loopMoove=0;
  speedVar=10;
}

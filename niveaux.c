#include "niveaux.h"
#include "variables.h"

//Déclare le nombre de niveaux
struct Level level[3];

void level0 (){
  int index=0;
  for (int i=0;i<4;i++){
    if (i%2==0){
      xScan=0;
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
      xScan=-50;
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
      //xScan=50;
      }
    }
  yScan=100;
  }
  for (int i=72;i<100;i++){ //complète le reste de la table pour éviter des valeurs erronnées
      for (int i=0;i<3;i++){   
        if (i==0){
          level[0].tableLevel[i][index]=0;
        }
        else if(i==1){
          level[0].tableLevel[i][index]=0; 
        }
        else{
          level[0].tableLevel[i][index]=0;
        }
      }
  index=index+1;
  }
}


//table niveau medium
void level1 (){
  int index=0; //n° de cellule
  for (int i=0;i<3;i++){  //deux boucles de for pour scanner la grille
    xScan=50;
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
    xScan=50;
    }
  yScan=100;
  }
  for (int i=54;i<100;i++){ //complète le reste de la table pour éviter des valeurs erronnées
      for (int i=0;i<3;i++){   
        if (i==0){
          level[1].tableLevel[i][index]=0;
        }
        else if(i==1){
          level[1].tableLevel[i][index]=0; 
        }
        else{
          level[1].tableLevel[i][index]=0;
        }
      }
  index=index+1;
  }
}

//table niveau hard
void level2 (){
  int index=0; //n° de cellule
  for (int i=0;i<5;i++){  //deux boucles de for pour scanner la grille
    xScan=50;
    yScan=yScan+50*i;
    for (int j=0;j<18;j++){
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
    xScan=50;
    }
  yScan=100;
  }
  for (int i=90;i<100;i++){ //complète le reste de la table pour éviter des valeurs erronnées
      for (int i=0;i<3;i++){   
        if (i==0){
          level[2].tableLevel[i][index]=0;
        }
        else if(i==1){
          level[2].tableLevel[i][index]=0; 
        }
        else{
          level[2].tableLevel[i][index]=0;
        }
      }
  index=index+1;
  }
}

void init_game(){
  level0();
  level1();
  level2();
  x = 500;
  y = 700;
  vx=cos(60*(3.14/180))*5;
  vy=-(60*(3.14/180))*5;
}

#include "niveaux.h"
#include "variables.h"

int niveau1[3][100];   //table pour stocker les coordonnées et présence d'ennemis sur la case
int niveau2[3][100]; 

//créer un tableau par niveau. Dans le main, créer un sprite et des évènements pour lancer les niveaux.

//coordonnées de la cellule
// xScan=50;
// yScan=100;

void level1 (){
  int index=0;
  for (int i=0;i<4;i++){
    if (i%2==0){
      xScan=0;
      yScan=yScan+50*i;
      for (int j=0;j<9;j++){
        xScan=xScan+(2*50);
        for (int i=0;i<3;i++){
          if (i==0){
            niveau1[i][index]=xScan;
          }
          else if(i==1){
            niveau1[i][index]=yScan; 
          }
          else{
            niveau1[i][index]=1;
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
            niveau1[i][index]=xScan;
          }
          else if(i==1){
            niveau1[i][index]=yScan; 
          }
          else{
            niveau1[i][index]=1;
          }
        }
      index=index+1;
      //xScan=50;
      }
    }
  yScan=100;
  }
}

//table niveau hard
void level2 (){
  int index=0; //n° de cellule
  for (int i=0;i<5;i++){  //deux boucles de for pour scanner la grille
    yScan=yScan+50*i;
    for (int j=0;j<18;j++){
      xScan=xScan+50*j;
      for (int i=0;i<3;i++){   //pour chaque cellule, enregistre les coordonnées et initialise présence d'une brique
        if (i==0){
          niveau2[i][index]=xScan;
        }
        else if(i==1){
          niveau2[i][index]=yScan; 
        }
        else{
          niveau2[i][index]=1;
        }
      }
    index=index+1;
    xScan=50;
    }
  yScan=100;
  }
}

void init_game(){
  level1();
  level2();
}
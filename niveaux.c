#include "niveaux.h"
#include "variables.h"

int presenceObjet[3][100];   //table pour stocker les coordonnées et présence d'ennemis sur la case

//crée le tableau qui enregistre la position des briques et pilote leur présence
void init_game(){
  int index=0; //n° de cellule
  //coordonnées de la cellule
 // xScan=50;
 // yScan=100;
  for (int i=0;i<5;i++){  //deux boucles de for pour scanner la grille
    yScan=yScan+50*i;
    for (int j=0;j<18;j++){
      xScan=xScan+50*j;
      for (int i=0;i<3;i++){   //pour chaque cellule, enregistre les coordonnées et initialise présence d'une brique
        if (i==0){
          presenceObjet[i][index]=xScan;
        }
        else if(i==1){
          presenceObjet[i][index]=yScan; 
        }
        else{
          presenceObjet[i][index]=1;
        }
      }
    index=index+1;
    xScan=50;
    }
  yScan=100;
  }

  for(int i=0;i<=100;i++){
    printf("x :%d, y :%d, Brique :%d  \n",presenceObjet[0][i],presenceObjet[1][i],presenceObjet[2][i]);
  }
}
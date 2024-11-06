#include "game.h"
#include "niveaux.h"
#include "variables.h"
#include <unistd.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <time.h>
#include <math.h>
#include "sdl_helper/constants.h"
#include "sdl_helper/function.h"
#include "sdl_helper/text_functions.h"
#include "sdl_helper/audio_functions.h"

void jellyfish(int a, int b, int choixBrique){ 
    if(choixBrique==0){
        sprite(a,b,"sdl_helper/sprites/jellyfish.bmp"); 
    }  
    else if(choixBrique==1){
        sprite(a,b,"sdl_helper/sprites/jellyfishRed.bmp"); 
    } 
    else if(choixBrique==2){
        sprite(a,b,"sdl_helper/sprites/jellyfishGreen.bmp"); 
    } 
    else if(choixBrique==3){
        sprite(a,b,"sdl_helper/sprites/jellyfishOrange.bmp"); 
    } 
}

void jellyfishPrint(){
    for (int j=0;j<100;j++){
        if (level[numLevel].tableLevel[2][j]==1){
            jellyfish(level[numLevel].tableLevel[0][j],level[numLevel].tableLevel[1][j],0);        
        }
        else if(level[numLevel].tableLevel[2][j]==2){
            jellyfish(level[numLevel].tableLevel[0][j],level[numLevel].tableLevel[1][j],1);        
        }
        else if(level[numLevel].tableLevel[2][j]==3){
            jellyfish(level[numLevel].tableLevel[0][j],level[numLevel].tableLevel[1][j],2);     
        }
        else if(level[numLevel].tableLevel[2][j]==4){
            jellyfish(level[numLevel].tableLevel[0][j],level[numLevel].tableLevel[1][j],3);     
        }
    }
}

//fait rebondir contre la brique et la supprime
void interaction(){
    //récupère les dimensions de l'image pour les hitBox (int)
    SDL_Rect hitBoxJellyfish = hitBoxSizeJellyfish(); 
    SDL_Rect hitBoxTurtle = hitBoxSizeTurtle();
    for (int j=0;j<100;j++){
    //coordonnées du coin haut gauche de la brique
            int xtest;
            int ytest;
            xtest=level[numLevel].tableLevel[0][j]; 
            ytest=level[numLevel].tableLevel[1][j];

    //position précédente de la balle
        float a=x-vx;
        float b=y-vy;
    //distance entre les 2 positions de la balle
        float R = sqrt(((x-a)*(x-a))+((y-b)*(y-b)));
    //calcul du nombre d'itérations à faire
        float iteration=1/R;
    //tester toutes les positions intermédiaires
        for (float i=0;i<=1;i+=iteration){
            int collision=0;
            if (collision==0){
    //déplacement de la balle entre les 2 positions
                a=a+(iteration*(x-a));
                b=b+(iteration*(y-b));

                //contact par le bas
                if ((vy<0) && 
                    (b<=(ytest+hitBoxJellyfish.h)) && 
                    (b>=(ytest)) && 
                    ((a+10)>=(xtest)) && 
                    ((a+10)<=(xtest+hitBoxJellyfish.w))){  
                    //teste la brique
                    if ((level[numLevel].tableLevel[2][j])==1 || level[numLevel].tableLevel[2][j]==2 || (level[numLevel].tableLevel[2][j])==3){
                        vy*=-1;
                        //collision avec une brique bleue ou verte
                        if ((level[numLevel].tableLevel[2][j])==1 || (level[numLevel].tableLevel[2][j])==3){
                            level[numLevel].tableLevel[2][j]=0;
                        }
                        //collision avec une brique rouge
                        else if ((level[numLevel].tableLevel[2][j])==2){
                            level[numLevel].tableLevel[2][j]=4;
                        }
                        y=(ytest+hitBoxJellyfish.h+1);
                        x=a;
                        collision=1;
                        audioLoadAndPlay("sdl_helper/sound/ping_brick.wav", -1);
                    }
                    //collision avec une brique orange
                    else if ((level[numLevel].tableLevel[2][j])==4){
                        vy*=-1;
                        level[numLevel].tableLevel[2][j]=0;
                        y=(ytest+hitBoxJellyfish.h+1);
                        x=a;
                        collision=1;
                        collisionOrange(xtest,ytest);
                    }
                }
                //contact par le haut
                else if ((vy>0) && 
                        ((b+20)>=(ytest)) && 
                        ((b+20)<=(ytest+hitBoxJellyfish.h)) && 
                        ((a+10)>=(xtest)) && 
                        ((a+10)<=(xtest+hitBoxJellyfish.w))){
                    if ((level[numLevel].tableLevel[2][j])==1 || (level[numLevel].tableLevel[2][j])==2 || (level[numLevel].tableLevel[2][j])==3){  
                        vy*=-1;
                        //collision avec une brique bleue ou verte
                        if ((level[numLevel].tableLevel[2][j])==1 || (level[numLevel].tableLevel[2][j])==3){
                            level[numLevel].tableLevel[2][j]=0;
                        }
                        //collision avec une brique rouge
                        else if ((level[numLevel].tableLevel[2][j])==2){
                            level[numLevel].tableLevel[2][j]=4;
                        }
                        y=(ytest-21);
                        x=a;
                        collision=1;
                        audioLoadAndPlay("sdl_helper/sound/ping_brick.wav", -1);
                    }
                    else if ((level[numLevel].tableLevel[2][j])==4){  
                        vy=vy*-1;
                        level[numLevel].tableLevel[2][j]=0;
                        y=(ytest-21);
                        x=a;
                        collision=1; 
                        collisionOrange(xtest,ytest);
                    }                   
                }
                //contact par la gauche
                else if ((vx>0) && 
                        ((a+20)>=(xtest)) && 
                        ((a+10)<=(xtest+hitBoxJellyfish.w)) && 
                        ((b+10)>=(ytest)) && 
                        ((b+10)<=(ytest+hitBoxJellyfish.h))){
                    if ((level[numLevel].tableLevel[2][j])==1 || (level[numLevel].tableLevel[2][j])==2 || (level[numLevel].tableLevel[2][j])==3){  
                        vx*=-1;
                        //collision avec une brique bleue ou verte
                        if ((level[numLevel].tableLevel[2][j])==1 || (level[numLevel].tableLevel[2][j])==3){
                            level[numLevel].tableLevel[2][j]=0;
                        }
                        //collision avec une brique rouge
                        else if ((level[numLevel].tableLevel[2][j])==2){
                            level[numLevel].tableLevel[2][j]=4;
                        }
                        x=(xtest-21);
                        y=b;
                        collision=1;
                        audioLoadAndPlay("sdl_helper/sound/ping_brick.wav", -1);
                    }           
                    else if ((level[numLevel].tableLevel[2][j])==4){  
                        vx*=-1;
                        level[numLevel].tableLevel[2][j]=0;
                        x=(xtest-21);
                        y=b;
                        collision=1;
                        collisionOrange(xtest,ytest);
                    }                             
                }
                //contact par la droite
                else if ((vx<0) && 
                        (a>=(xtest)) && 
                        (a<=(xtest+hitBoxJellyfish.w)) && 
                        ((b+10)>=(ytest)) && 
                        ((b+10)<=(ytest+hitBoxJellyfish.h))){
                    if ((level[numLevel].tableLevel[2][j])==1 || (level[numLevel].tableLevel[2][j])==2 || (level[numLevel].tableLevel[2][j])==3){  
                        vx*=-1;
                        //collision avec une brique bleue ou verte
                        if ((level[numLevel].tableLevel[2][j])==1 || (level[numLevel].tableLevel[2][j])==3){
                            level[numLevel].tableLevel[2][j]=0;
                        }
                        //collision avec une brique rouge
                        else if ((level[numLevel].tableLevel[2][j])==2){
                            level[numLevel].tableLevel[2][j]=4;
                        }
                        x=(xtest+hitBoxJellyfish.w+1);
                        y=b;
                        collision=1;
                        audioLoadAndPlay("sdl_helper/sound/ping_brick.wav", -1);
                    }     
                    else if ((level[numLevel].tableLevel[2][j])==4){  
                        vx*=-1;
                        level[numLevel].tableLevel[2][j]=0;
                        x=(xtest+hitBoxJellyfish.w+1);
                        y=b;
                        collision=1;
                        collisionOrange(xtest,ytest);
                    }             
                }
                else{}
            }
        }
    }
}

//remonte l'index à partir des coordonnées
int indexBriquesCollision (int xBriqueCollision, int yBriqueCollision){
    for (int i=0;i<=100;i++){
        if (level[numLevel].tableLevel[0][i]==xBriqueCollision && level[numLevel].tableLevel[1][i]==yBriqueCollision){
            indexBoum=i;
            return indexBoum;
        }
    }
}

//supprime toutes les briques sur une croix de -50px autour de la brique orange avec effet de propagation.
void collisionOrange(int xtest,int ytest){
    int propagation;
    int compteur=1;
    audioLoadAndPlay("sdl_helper/sound/ping_redbrick.wav", -1);

    //supprime la brique dessus
    indexBriquesCollision(xtest,ytest-50);
    if (level[numLevel].tableLevel[2][indexBoum]==4){
        propagation=1;
        level[numLevel].tableLevel[2][indexBoum]=0;
    }    
    else if (level[numLevel].tableLevel[2][indexBoum]==2){
        level[numLevel].tableLevel[2][indexBoum]=4;
    }
    else if (level[numLevel].tableLevel[2][indexBoum]==1 || level[numLevel].tableLevel[2][indexBoum]==3){
        level[numLevel].tableLevel[2][indexBoum]=0;
    }
    //supprime la brique dessous
    indexBriquesCollision(xtest,ytest+50);
    if (level[numLevel].tableLevel[2][indexBoum]==4){
        propagation=2;
        level[numLevel].tableLevel[2][indexBoum]=0;
    }    
    else if (level[numLevel].tableLevel[2][indexBoum]==2){
        level[numLevel].tableLevel[2][indexBoum]=4;
    }
    else if (level[numLevel].tableLevel[2][indexBoum]==1 || level[numLevel].tableLevel[2][indexBoum]==3){
        level[numLevel].tableLevel[2][indexBoum]=0;
    }
    //supprime la brique de gauche
    indexBriquesCollision(xtest-50,ytest);
    if (level[numLevel].tableLevel[2][indexBoum]==4){
        propagation=3;
        level[numLevel].tableLevel[2][indexBoum]=0;
    }
    else if (level[numLevel].tableLevel[2][indexBoum]==2){
        level[numLevel].tableLevel[2][indexBoum]=4;
    }
    else if (level[numLevel].tableLevel[2][indexBoum]==1 || level[numLevel].tableLevel[2][indexBoum]==3){
        level[numLevel].tableLevel[2][indexBoum]=0;
    }
    //supprime la brique de droite
    indexBriquesCollision(xtest+50,ytest);
    if (level[numLevel].tableLevel[2][indexBoum]==4){
        propagation=4;
        level[numLevel].tableLevel[2][indexBoum]=0;
    }    
    else if (level[numLevel].tableLevel[2][indexBoum]==2){
        level[numLevel].tableLevel[2][indexBoum]=4;
    }
    else if (level[numLevel].tableLevel[2][indexBoum]==1 || level[numLevel].tableLevel[2][indexBoum]==3){
        level[numLevel].tableLevel[2][indexBoum]=0;
    }
    //propagation de l'effet
    compteur++;
    if (compteur>5){
        propagation=5;
    }
    switch (propagation){
        case 1 :
            collisionOrange(xtest,ytest-50);
        break;
        case 2 :
            collisionOrange(xtest,ytest+50);   
        break;
        case 3 :
            collisionOrange(xtest-50,ytest);
        break;
        case 4 :
            collisionOrange(xtest+50,ytest);
        break;
        default: //do nothing
    }
    if (numLevel==0 || numLevel==1){
            switch (propagation){
                case 1 :
                    collisionOrange(xtest,ytest-100);
                break;
                case 2 :
                    collisionOrange(xtest,ytest+100);   
                break;
                case 3 :
                    collisionOrange(xtest-100,ytest);
                break;
                case 4 :
                    collisionOrange(xtest+100,ytest);
                break;
                default: //do nothing
            }
    }
}

void gameEnd(){
    int gameOn=0;
    for (int j=0;j<100;j++){
        if (level[numLevel].tableLevel[2][j]==1 ||
        level[numLevel].tableLevel[2][j]==2 ||
        level[numLevel].tableLevel[2][j]==3 ||
        level[numLevel].tableLevel[2][j]==4){
            gameOn=1;
        }     
    }
    switch (gameOn){
      case 1:
      gameOn=0;
      break;
      case 0:
          sprite (0,0,"sdl_helper/sprites/win.bmp");
          actualize();
          usleep(200000000 / FPS);
          nbVie=3;
          launch=0; 
          init_game();
    }
}

void background(){
    sprite(0,0,"sdl_helper/sprites/background.bmp");
}

void vie(){
    nbVie--;
        if (nbVie>=0){
        x=500;
        y=800;
        sprite (0,0,"sdl_helper/sprites/goAgain.bmp");
        actualize();
        usleep(100000000 / FPS);
        vx=4;
        vy=-4;
        speedVar=5;
      }  
      else{
        sprite (0,0,"sdl_helper/sprites/lost.bmp");
        actualize();
        usleep(200000000 / FPS);
        nbVie=3;
        launch=0;
        init_game();
      }
}
void printVie(){
    for (int i=0;i<=(nbVie);i++){
        xheart=10+50*i;
        sprite(xheart,yheart,"sdl_helper/sprites/heart.bmp");
    }
}

//vecteur de déplacement. Angle en degré converti en radians
void vecteurSpeed(){
    float rad = angle*(3.14/180);  
    vx=cos(rad)*speedVar;
    vy=sin(rad)*speedVar;
}

void speed(){
    x=x+vx;
    y=y+vy;
}
//interactions avec les bords et la tortue.  
//crée un gradient de 0 à 100 pour modifier l'angle entre 30° et 80°, utiliser la fonction speed 
void rebondTortue(){
    if(y>(yRect-8) && y<(yRect+10) && x>(xRect-20) && x<=(xRect+80)){
        audioLoadAndPlay("sdl_helper/sound/ping_turtle.wav", -1);
        float posRebond;
        posRebond = (x-xRect) / 100;
        angle=30+posRebond*30;   //fait évoluer l'angle entre 30 et 80 suivant la position sur la barre
        vecteurSpeed();
        vy*=-1;
            if (vx>0){
            vx*=-1;
            }
            else {}
        y=yRect-10;
    }
    
    //centre, pas de modification de la direction
    else if((y>(yRect-8)) && y<(yRect+10) && x>(xRect+80) && x<(xRect+120)){
        audioLoadAndPlay("sdl_helper/sound/ping_turtle.wav", -1);
        angle=80;
        vecteurSpeed();
        vy*=-1;
        y=yRect-10;
    }
    //droite, renvoyer vers la droite
    else if(y>(yRect-8) && y<(yRect+10) && x>=(xRect+120) && x<(xRect+200)){
        audioLoadAndPlay("sdl_helper/sound/ping_turtle.wav", -1);
        float posRebond;
        posRebond = (x-(xRect+120)) / 80;
        angle=30+posRebond*30;
        vecteurSpeed();
        vy*=-1;
            if (vx<0){
            vx*=-1;
            }
            else {}
        y=yRect-10;
    }
}

void rebondBords(){
    if (x>(979)){   //window_width-hitbox-1 pour éviter le contact
      vx*=-1;        //renvoie dans l'autre sens
      x=979;
    }
    else if(x<1){
      vx*=-1;
      x=1;
    }
    else if(y<11){
      vy*=-1;
      y=11;
    }

    else if (y>(yRect-8) && y<(yRect+10) && x>(xRect-20) && x<=(xRect+200)) {
      rebondTortue();
    }
    else if (y>1000){
        audioLoadAndPlay("sdl_helper/sound/lost.wav", -1);
        vie();
    }
    else {}
}


//Déplacement de la raquette
void turtle(){
    if (deplacementGauche==1){
      xRect-=20;
    }
    else if (deplacementDroite==1){
      xRect+=20;    
    }
    if(xRect<0){
      xRect=0;
    }
    else if(xRect>800){
      xRect=800;
    }
    sprite(xRect,yRect,"sdl_helper/sprites/turtle.bmp");
}

void waterDrop(){
    if (vx<0 && vy<0){
        sprite(x,y,"sdl_helper/sprites/waterDrophg.bmp");
    }
    else if (vx<0 && vy>0){
        sprite(x,y,"sdl_helper/sprites/waterDropbg.bmp");
    }
    if (vx>0 && vy<0){
        sprite(x,y,"sdl_helper/sprites/waterDrophd.bmp");
    }
    else if (vx>0 && vy>0){
        sprite(x,y,"sdl_helper/sprites/waterDropbd.bmp");
    }
}
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

//sélectionne l'interaction
void choixInteraction(){
    if (compteurGreen==1){
        collisionGreen();
    }
    else {
        interaction();
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
    //teste toutes les positions intermédiaires
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
                        //collision avec une brique bleue
                        if ((level[numLevel].tableLevel[2][j])==1){
                            level[numLevel].tableLevel[2][j]=0;
                        }
                        //collision avec une brique verte
                        if ((level[numLevel].tableLevel[2][j])==3){
                            level[numLevel].tableLevel[2][j]=0;                            
                            nbComet++;
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
                        //collision avec une brique bleue
                        if ((level[numLevel].tableLevel[2][j])==1){
                            level[numLevel].tableLevel[2][j]=0;
                        }
                        //collision avec une brique verte
                        if ((level[numLevel].tableLevel[2][j])==3){
                            level[numLevel].tableLevel[2][j]=0;                            
                            nbComet++;
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
                        //collision avec une brique bleue
                        if ((level[numLevel].tableLevel[2][j])==1){
                            level[numLevel].tableLevel[2][j]=0;
                        }
                        //collision avec une brique verte
                        if ((level[numLevel].tableLevel[2][j])==3){
                            level[numLevel].tableLevel[2][j]=0;                            
                            nbComet++;
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
                        //collision avec une brique bleue
                        if ((level[numLevel].tableLevel[2][j])==1){
                            level[numLevel].tableLevel[2][j]=0;
                        }
                        //collision avec une brique verte
                        if ((level[numLevel].tableLevel[2][j])==3){
                            level[numLevel].tableLevel[2][j]=0;                            
                            nbComet++;
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
    //Défini le range de l'explosion en fonction du niveau
    int xExplosionG, xExplosionD, yExplosionH, yExplosionB;
    if (numLevel==0){
        xExplosionG=xtest-100;
        xExplosionD=xtest+100;
        yExplosionH=ytest-100;
        yExplosionB=ytest+100;
    }
    else if (numLevel==1){
        xExplosionG=xtest-50;
        xExplosionD=xtest+50;
        yExplosionH=ytest-100;
        yExplosionB=ytest+100;
    }
    else if (numLevel==2){
        xExplosionG=xtest-50;
        xExplosionD=xtest+50;
        yExplosionH=ytest-80;
        yExplosionB=ytest+80;
    }

    //supprime la brique dessus
    indexBriquesCollision(xtest,yExplosionH);
    if (level[numLevel].tableLevel[2][indexBoum]==4){
        propagation=1;
        level[numLevel].tableLevel[2][indexBoum]=0;
    }    
    else if (level[numLevel].tableLevel[2][indexBoum]==2){
        level[numLevel].tableLevel[2][indexBoum]=4;
    }
    else if (level[numLevel].tableLevel[2][indexBoum]==1){
        level[numLevel].tableLevel[2][indexBoum]=0;
    }
    else if (level[numLevel].tableLevel[2][indexBoum]==3){
        level[numLevel].tableLevel[2][indexBoum]=0;
        nbComet++;
    }
    //supprime la brique dessous
    indexBriquesCollision(xtest,yExplosionB);
    if (level[numLevel].tableLevel[2][indexBoum]==4){
        propagation=2;
        level[numLevel].tableLevel[2][indexBoum]=0;
    }    
    else if (level[numLevel].tableLevel[2][indexBoum]==2){
        level[numLevel].tableLevel[2][indexBoum]=4;
    }
    else if (level[numLevel].tableLevel[2][indexBoum]==1){
        level[numLevel].tableLevel[2][indexBoum]=0;
    }
    else if (level[numLevel].tableLevel[2][indexBoum]==3){
        level[numLevel].tableLevel[2][indexBoum]=0;
        nbComet++;
    }
    //supprime la brique de gauche
    indexBriquesCollision(xExplosionG,ytest);
    if (level[numLevel].tableLevel[2][indexBoum]==4){
        propagation=3;
        level[numLevel].tableLevel[2][indexBoum]=0;
    }
    else if (level[numLevel].tableLevel[2][indexBoum]==2){
        level[numLevel].tableLevel[2][indexBoum]=4;
    }
    else if (level[numLevel].tableLevel[2][indexBoum]==1){
        level[numLevel].tableLevel[2][indexBoum]=0;
    }
    else if (level[numLevel].tableLevel[2][indexBoum]==3){
        level[numLevel].tableLevel[2][indexBoum]=0;
        nbComet++;
    }
    //supprime la brique de droite
    indexBriquesCollision(xExplosionD,ytest);
    if (level[numLevel].tableLevel[2][indexBoum]==4){
        propagation=4;
        level[numLevel].tableLevel[2][indexBoum]=0;
    }    
    else if (level[numLevel].tableLevel[2][indexBoum]==2){
        level[numLevel].tableLevel[2][indexBoum]=4;
    }
    else if (level[numLevel].tableLevel[2][indexBoum]==1){
        level[numLevel].tableLevel[2][indexBoum]=0;
    }
    else if (level[numLevel].tableLevel[2][indexBoum]==3){
        level[numLevel].tableLevel[2][indexBoum]=0;
        nbComet++;
    }
    //propagation de l'effet
    compteur++;
    if (compteur>10){
        propagation=5;
    }
    //if (numLevel==0){
        switch (propagation){
            case 1 :
                collisionOrange(xtest,yExplosionH);
            break;
            case 2 :
                collisionOrange(xtest,yExplosionB); 
            break;
            case 3 :
                collisionOrange(xExplosionG,ytest);
            break;
            case 4 :
                collisionOrange(xExplosionD,ytest);
            break;
            default: //do nothing
        }
}

//traverse les briques et les supprime
void collisionGreen (){
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
                        //collision avec une brique bleue
                        if ((level[numLevel].tableLevel[2][j])==1){
                            level[numLevel].tableLevel[2][j]=0;
                        }
                        //collision avec une brique verte
                        if ((level[numLevel].tableLevel[2][j])==3){
                            level[numLevel].tableLevel[2][j]=0;                           
                            nbComet++;
                        }
                        //collision avec une brique rouge
                        else if ((level[numLevel].tableLevel[2][j])==2){
                            level[numLevel].tableLevel[2][j]=4;
                        }
                        y=b;
                        x=a;
                        collision=1;
                        audioLoadAndPlay("sdl_helper/sound/ping_brick.wav", -1);
                    }
                    //collision avec une brique orange
                    else if ((level[numLevel].tableLevel[2][j])==4){
                        level[numLevel].tableLevel[2][j]=0;
                        y=b;
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
                        //collision avec une brique bleue
                        if ((level[numLevel].tableLevel[2][j])==1){
                            level[numLevel].tableLevel[2][j]=0;
                        }
                        //collision avec une brique verte
                        if ((level[numLevel].tableLevel[2][j])==3){
                            level[numLevel].tableLevel[2][j]=0;                            
                            nbComet++;
                        }
                        //collision avec une brique rouge
                        else if ((level[numLevel].tableLevel[2][j])==2){
                            level[numLevel].tableLevel[2][j]=4;
                        }
                        y=b;
                        x=a;
                        collision=1;
                        audioLoadAndPlay("sdl_helper/sound/ping_brick.wav", -1);
                    }
                    else if ((level[numLevel].tableLevel[2][j])==4){  
                        level[numLevel].tableLevel[2][j]=0;
                        y=b;
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
                        //collision avec une brique bleue
                        if ((level[numLevel].tableLevel[2][j])==1){
                            level[numLevel].tableLevel[2][j]=0;
                        }
                        //collision avec une brique verte
                        if ((level[numLevel].tableLevel[2][j])==3){
                            level[numLevel].tableLevel[2][j]=0;                            
                            nbComet++;
                        }
                        //collision avec une brique rouge
                        else if ((level[numLevel].tableLevel[2][j])==2){
                            level[numLevel].tableLevel[2][j]=4;
                        }
                        x=a;
                        y=b;
                        collision=1;
                        audioLoadAndPlay("sdl_helper/sound/ping_brick.wav", -1);
                    }           
                    else if ((level[numLevel].tableLevel[2][j])==4){  
                        level[numLevel].tableLevel[2][j]=0;
                        x=a;
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
                        //collision avec une brique bleue
                        if ((level[numLevel].tableLevel[2][j])==1){
                            level[numLevel].tableLevel[2][j]=0;
                        }
                        //collision avec une brique verte
                        if ((level[numLevel].tableLevel[2][j])==3){
                            level[numLevel].tableLevel[2][j]=0;                            
                            nbComet++;
                        }
                        //collision avec une brique rouge
                        else if ((level[numLevel].tableLevel[2][j])==2){
                            level[numLevel].tableLevel[2][j]=4;
                        }
                        x=a;
                        y=b;
                        collision=1;
                        audioLoadAndPlay("sdl_helper/sound/ping_brick.wav", -1);
                    }     
                    else if ((level[numLevel].tableLevel[2][j])==4){  
                        vx*=-1;
                        level[numLevel].tableLevel[2][j]=0;
                        x=a;
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

// Victoire
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
        fullCenteredText("WIN",comfortaaFont_52);
        audioLoadAndPlay("sdl_helper/sound/win.wav",7);
        actualize();
        usleep(6000000);
        nbVie=3;
        launch=0; 
        init_game();
    }
}

void background(){
    spriteBackground(0,0,"sdl_helper/sprites/background.bmp");
    changeColor( 88, 174, 245 );
    drawLine((screenSize.center-500),0,(screenSize.center-500),screenSize.height);
    drawLine((screenSize.center+500),0,(screenSize.center+500),screenSize.height);
}

//Défaite
void vie(){
    nbVie--;
        if (nbVie>=0){
        fullCenteredText("TRY AGAIN",comfortaaFont_52);
        actualize();
        usleep(100000000 / FPS);
        initVar();
      }  
      else{
        fullCenteredText("GAME OVER",comfortaaFont_52);
        actualize();
        usleep(200000000 / FPS);
        nbVie=3;
        launch=0;
        init_game();
      }
}
void printVie(){
    for (int i=0;i<(nbVie);i++){
        xheart=xheartInit+(50*i);
        sprite(xheart,yheart,"sdl_helper/sprites/heart.bmp");
    }
}

void printNbComet(){
    if(nbComet>0){
        for (int i=0;i<(nbComet);i++){
        xComet=xCometInit-(50*i);
        sprite(xComet,yComet,"sdl_helper/sprites/comet.bmp");
        }
    }
}

//vecteur de déplacement. Angle en degré converti en radians
void vecteurSpeed(){
    float rad = angle*(3.14/180);  
    vx=cos(rad)*speedVar;
    vy=sin(rad)*speedVar;
}

//position de la balle
void speed(){
    if (pauseSwitch==1){
            x=x+vx;
            y=y+vy;           
    }
    else if (pauseSwitch==-1){
        fullCenteredText("PAUSED",comfortaaFont_52);
    }
    //affiche la vitesse de la balle
    sprite ((screenSize.center-690),100, "sdl_helper/sprites/speed.bmp");
    char speedChar[50];
    sprintf(speedChar,"%d",speedVar);
    textDrawText(speedChar,screenSize.center-620,108,comfortaaFont_28);
}

//interactions avec les bords et la tortue.  
void rebondTortue(){
    //Gauche
    if(y>(yRect-18) && y<(yRect+10) && x>(xRect-20) && x<=(xRect+70)){
        audioLoadAndPlay("sdl_helper/sound/ping_turtle.wav", -1);
        float posRebond;
        //crée un gradient de 0 à 1 suivant la position d'impact
        posRebond = (x-xRect+20)/80;
        angle=30+posRebond*50;   //fait évoluer l'angle entre 30 et 80 suivant la position sur la barre
        vecteurSpeed();
        vy*=-1;
            if (vx>0){
            vx*=-1;
            }
            else {}
        y=yRect-20;
    }
    //centre gauche, pas de modification de la direction
    else if((y>(yRect-28)) && y<(yRect+10) && x>(xRect+70) && x<(xRect+90)){
        audioLoadAndPlay("sdl_helper/sound/ping_turtle.wav", -1);
        angle=80;
        vecteurSpeed();
        vy*=-1;
        vx*=-1;
        y=yRect-30;
    }    
    //centre droit, pas de modification de la direction
    else if((y>(yRect-28)) && y<(yRect+10) && x>(xRect+90) && x<(xRect+110)){
        audioLoadAndPlay("sdl_helper/sound/ping_turtle.wav", -1);
        angle=80;
        vecteurSpeed();
        vy*=-1;
        y=yRect-30;
    }
    //droite, renvoyer vers la droite
    else if(y>(yRect-8) && y<(yRect+10) && x>=(xRect+110) && x<(xRect+200)){
        audioLoadAndPlay("sdl_helper/sound/ping_turtle.wav", -1);
        float posRebond;
        posRebond = (x-(xRect+110))/90;
        angle=80-posRebond*50;
        vecteurSpeed();
        vy*=-1;
            if (vx<0){
            vx*=-1;
            }
            else {}
        y=yRect-10;
    }
    if (compteurGreen==1){
        compteurGreen--;
    }
    else if (compteurGreen==2){
        compteurGreen=1;
    }
}

void rebondBords(){
    if (x>(screenSize.center+479)){   //window_width-hitbox-1 pour éviter le contact
      vx*=-1;        //renvoie dans l'autre sens
      x=(screenSize.center+479);
    }
    else if(x<(screenSize.center-499)){
      vx*=-1;
      x=(screenSize.center-499);
    }
    else if(y<11){
      vy*=-1;
      y=11;
    }

    else if ((y>(yRect-18) && y<(yRect+10) && x>(xRect-20) && x<=(xRect+70)) || 
    (y>(yRect-28)) && y<(yRect+10) && x>(xRect+70) && x<(xRect+90) ||
    (y>(yRect-28)) && y<(yRect+10) && x>(xRect+90) && x<(xRect+110) ||
    y>(yRect-8) && y<(yRect+10) && x>=(xRect+110) && x<(xRect+200)) {
      rebondTortue();
    }
    else if (y>screenSize.height){
        audioLoadAndPlay("sdl_helper/sound/lost.wav", -1);
        vie();
    }
    else {}
}


//Déplacement de la raquette
void turtle(){
    if (deplacementGauche==1){
      xRect-=speedTortue;
    }
    else if (deplacementDroite==1){
      xRect+=speedTortue;    
    }
    if(xRect<(screenSize.center-500)){
      xRect=(screenSize.center-500);
    }
    else if(xRect>(screenSize.center+300)){
      xRect=(screenSize.center+300);
    }
    sprite(xRect,yRect,"sdl_helper/sprites/turtle.bmp");
}

float convertAngle(){
        if (vx<0 && vy<0){
            angleBall=angle+180;
        }
        else if (vx<0 && vy>0){
            angleBall=180-angle;
        }
        if (vx>0 && vy<0){
            angleBall=-angle;
        }
        else if (vx>0 && vy>0){
            angleBall=angle;
        }
}

void echo(){
    positionEcho[0][0]=x;
    positionEcho[1][0]=y;
    for (int i=1;i<=1000;i++){
        positionEcho[0][i]=positionEcho[0][i-1] ;
        positionEcho[1][i]=positionEcho[1][i-1] ;
    }
}

void waterDrop(){
    if (compteurGreen==1){
        spriteRotate(x,y,"sdl_helper/sprites/cometRight.bmp",angleBall);
        spriteRotate((positionEcho[0][500]+5),(positionEcho[1][500]+5),"sdl_helper/sprites/cometEcho1Right.bmp",angleBall);
        spriteRotate((positionEcho[0][999]+7.5),(positionEcho[1][999]+7.5),"sdl_helper/sprites/cometEcho2Right.bmp",angleBall);
    }
    else {
        spriteRotate(x,y,"sdl_helper/sprites/waterDropRight.bmp",angleBall);
    }
}

// fait bouger les briques dans le level 2
void levelMoove(){
    if (loop%15==0){
        loopMoove++;
            for (int i=0;i<13;i++){
                level[2].tableLevel[0][i]+=decalage;
                level[2].tableLevel[0][i+26]+=decalage;

                level[2].tableLevel[0][i+13]-=decalage;
                level[2].tableLevel[0][i+39]-=decalage;
            }            
        if(loopMoove%10==0){
            decalage*=-1;
        } 
    }
}

//activation son de la comète. Durée son comet = 7s.
void sonComet(){
    if (compteurGreen!=1){
        audioLoadAndPlay("sdl_helper/sound/silence.wav",7);
        boucleSonComet=1;
    }
    else if (compteurGreen==1){
        if (boucleSonComet%7==1 ){
            audioLoadAndPlay("sdl_helper/sound/comet.wav", 7);
            boucleSonComet++;
        }
    }
}

//création d'un log
void fileLog(int numLevel){
    FILE *logLevelPlayed = fopen("logLevelPlayed.txt", "a+");
        if (logLevelPlayed == NULL) {
            perror("Erreur d'ouverture du fichier");
        }
    fprintf(logLevelPlayed,"Niveau numéro : %d\n",numLevel);
    fclose(logLevelPlayed);
}
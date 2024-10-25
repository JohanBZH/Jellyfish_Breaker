#include "function.h"
#include "niveaux.h"
#include "variables.h"
#include <unistd.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <time.h>
#include <math.h>

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000
#define FPS 60

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static int window_width = 0;
static int window_height = 0;
static char* name = "SDL app";

void out(){
    printf("Vous dessinez en dehors de la fenetre\n");
}

void checkPos(int x, int y){
    /** @brief verifie que x et y sont bien dans l'ecran initialisé
     *  @param x position à verifier
     *  @param y position à verifier
     */
    if (x < 0) {
        printf("ATTENTION position x < 0 (x = %d)\n", x);
        out();
    }
    if (x > window_width) {
        printf("ATTENTION position x > largeur de la fenetre (x = %d > %d)\n", x, window_width);
        out();
    }
    if (y < 0) {
        printf("ATTENTION position y < 0 (y = %d)\n", x);
        printf("ATTENTION position y > hauteur de la fenetre (y = %d > %d)\n", y, window_height);
        out();
    }
    if (y > window_height) {
        printf("ATTENTION position y > hauteur de la fenetre (y = %d > %d)\n", y, window_height);
        out();
    }
}

void init(int windowWidth, int windowHeight) {
    /** @brief initialise la fenêtre window et le renderer (moteur de rendu) renderer
     *  @param windowWidth la largeur de la fenêtre
     *  @param windowHeight la hauteur de la fenêtre
     */
    window_width = windowWidth;
    window_height = windowHeight;
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("ERREUR : Init SDL > %s\nParametres passes %d , %d\n",SDL_GetError(), windowWidth, windowHeight);
        freeAndTerminate();
    }
    if (SDL_CreateWindowAndRenderer(windowWidth, windowHeight, 0, &window, &renderer)) {
        SDL_Log("ERREUR : Init window and renderer > %s\nParametres passes %d , %d\n",SDL_GetError(), windowWidth, windowHeight);
        freeAndTerminate();
    }
    SDL_SetWindowTitle(window, "Brick Breaker");
}

void freeWindow() {
    /** @brief libère la mémoire allouée à la fenêtre
     */
    if (window) SDL_DestroyWindow(window);
}

void freeRenderer() {
    /** @brief libère la mémoire allouée au renderer
     */
    if (renderer) SDL_DestroyRenderer(renderer);
}

void freeTexture(SDL_Texture *texture) {
    /** @brief libère la mémoire allouée à la texture (utilisée pour dans la fonction sprite() pour afficher une image)
     *  @param texture la texture utilisée pour afficher l'image
     */
    if (texture) SDL_DestroyTexture(texture);
}

void freeAndTerminate() {
    /** @brief libère la mémoire allouée au programme(renderer et fenêtre) puis quitte la SDL et le programme
     */
    freeRenderer();
    freeWindow();
    SDL_Quit();
    exit(EXIT_SUCCESS);
}


void actualize() {
    /** @brief actualise le renderer (i.e affiche ce qu'on a dessiné / fait dessus)
     */
    SDL_RenderPresent(renderer);
}

void changeColor(int r, int g, int b) {
    /** @brief change la couleur avec laquelle on dessine sur le renderer en celle du code RGB
     *  @param r Rouge dans le code RGB de la couleur choisi, entre 0 et 255
     *  @param g Vert dans le code RGB de la couleur choisi, entre 0 et 255
     *  @param b Bleu dans le code RGB de la couleur choisi, entre 0 et 255
     */
    if (SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE)) {
        SDL_Log("ERREUR : changement de couleur > %s\nParametres passes %d , %d, %d\n",SDL_GetError(), r, g, b);
        freeAndTerminate();
    }
}

void clear() {
    /** @brief réinitialise le fenêtre et reset la couleur
     *         (i.e supprime ce qu'on a dessiné dessus pour avoir une fenêtre noire)
     */
    changeColor(0, 0, 0);
    SDL_RenderClear(renderer);
    changeColor(255, 255, 255);
}

void drawSquare(int posX, int posY, int longueur) {
    /** @brief dessine un carré
     *  @param posX position sur l'axe horizontale du coin supérieur gauche du carré
     *  @param posY position sur l'axe verticale du coin supérieur gauche du carré
     *  @param longueur longeur du coté du carré
     */
    checkPos(posX + 20, posY + 20);
    checkPos(posX + longueur - 20, posY + longueur - 20);
    SDL_Rect rectangle;
    rectangle.x = posX;
    rectangle.y = posY;
    rectangle.w = longueur;
    rectangle.h = longueur;

    if (SDL_RenderFillRect(renderer, &rectangle)) {
        SDL_Log("ERREUR : Impossible de creer le carre > %s\nParametres passes %d , %d, %d\n",SDL_GetError(), posX, posY, longueur);
        freeAndTerminate();
    }
}

void drawRect(int posX, int posY, int longueur, int hauteur) {
    /** @brief dessine un rectangle
     *  @param posX position sur l'axe horizontale du coin supérieur gauche du rectangle
     *  @param posY position sur l'axe verticale du coin supérieur gauche du rectangle
     *  @param longueur longeur du coté du rectangle
     *  @param hauteur hauteur du coté du carré
     */
    checkPos(posX + 20, posY + 20);
    checkPos(posX + longueur - 20, posY + hauteur - 20);
    SDL_Rect rectangle;
    rectangle.x = posX;
    rectangle.y = posY;
    rectangle.w = longueur;
    rectangle.h = hauteur;

    if (SDL_RenderFillRect(renderer, &rectangle)) {
        SDL_Log("ERREUR : Impossible de creer le rectangle > %s\nParametres passes %d , %d, %d, %d\n",SDL_GetError(), posX, posY, longueur, hauteur);
        freeAndTerminate();
    }
}

void drawCircle(int centerX, int centerY, int rayon) {
    /** @brief dessine un cercle de centre (x,y) et de rayon r sur le renderer
     *         (utilise l'équation d'un cercle x^2 + y^2 <= a^2)
     *  @param centerX position sur l'axe horizontal du centre
     *  @param centerY position sur l'axe vertical du centre
     *  @param rayon le rayon du cercle
     */
    checkPos(centerX - rayon + 20, centerY - rayon + 20);
    checkPos(centerX + rayon - 20, centerY + rayon - 20);
    for (int i = centerX - rayon; i <= centerX + rayon; i++) {
        for(int j = centerY - rayon; j <= centerY +rayon; j++) {
            int x = i - centerX;
            int y = j - centerY;
            if (x * x + y * y <= rayon * rayon) {
                SDL_RenderDrawPoint(renderer, i, j);
            }
        }
    }
}

void drawPoint(int x, int  y) {
    /** @brief dessine un point à la position (x,y) i.e change la couleur du pixel
     *  @param x position sur l'axe horizontal du point
     *  @param y position sur l'axe vertical du point
     */
    SDL_RenderDrawPoint(renderer, x, y);
}

void drawLine(int x1, int y1, int x2, int y2) {
    /** @brief trace une ligne entre le point 1 : (x1,y1) et 2 : (x2,y2)
     *  @param x1 position sur l'axe horizontal du point 1
     *  @param y1 position sur l'axe vertical du point 1
     *  @param x2 position sur l'axe horizontal du point 2
     *  @param y2 position sur l'axe vertical du point 2
     */
    if (SDL_RenderDrawLine( renderer, x1, y1, x2, y2)) {
        SDL_Log("ERREUR : drawLine() > %s\nParametres passes %d , %d, %d, %d\n",SDL_GetError(), x1, y1, x2, y2);
        freeAndTerminate();
    }
}

void drawLinePoints(Point point1, Point point2) {
    /** @brief même fonction que drawLine() mais avec des structure (voir struct Point)
     *  @param point1 Point d'origine de la ligne
     *  @param point2 Point d'arrivée de la ligne
     */
    if (SDL_RenderDrawLine( renderer, point1.x, point1.y, point2.x, point2.y)) {
        SDL_Log("ERREUR : drawLinePoints() > %s\nParametres passes (%d,%d), (%d,%d)\n",SDL_GetError(), point1.x, point1.y, point2.x, point2.y);
        freeAndTerminate();
    }
}

void sprite(int posX, int posY, char *imgBMPSrc) {
    int w;
    int h;
    sprite2(posX,posY,imgBMPSrc,&w,&h);
}

void sprite2(int posX, int posY, char *imgBMPSrc, int *w,int *h) {
    /** @brief affiche un image .bmp sur le renderer
     *  @param posX position sur l'axe horizontale du coin supérieur gauche de l'image
     *  @param posY position sur l'axe verticale du coin supérieur gauche de l'image
     *  @param imgBMPSrc le chemin vers l'image que l'on veut afficher
     */
    checkPos(posX, posY);
    SDL_Texture *textureImg = NULL;
    SDL_Surface *surfaceImg = NULL;
    if (!(surfaceImg = SDL_LoadBMP(imgBMPSrc))) {
        SDL_Log("ERREUR : chargement img > %s\nParametres passes %d , %d, %s\n",SDL_GetError(), posX, posY, imgBMPSrc);
        freeAndTerminate();
    }
    textureImg = SDL_CreateTextureFromSurface(renderer, surfaceImg);
    SDL_FreeSurface(surfaceImg);
    if (textureImg == NULL) {
        SDL_Log("ERREUR : chargement texture > %s\nParametres passes %d , %d, %s\n",SDL_GetError(), posX, posY, imgBMPSrc);
        freeTexture(textureImg);
        freeAndTerminate();
    }

    SDL_Rect rectangle;
    if (SDL_QueryTexture(textureImg, NULL, NULL, &rectangle.w, &rectangle.h)) {
        SDL_Log("ERREUR : image : query texture > %s\nParametres passes %d , %d, %s\n",SDL_GetError(), posX, posY, imgBMPSrc);
        freeTexture(textureImg);
        freeAndTerminate();
    }
    rectangle.x = posX;
    rectangle.y = posY;
    if (SDL_RenderCopy(renderer, textureImg, NULL, &rectangle) != 0) {
        SDL_Log("ERREUR: image : RenderCopy > %s\nParametres passes %d , %d, %s\n",SDL_GetError(), posX, posY, imgBMPSrc);
        freeTexture(textureImg);
        freeAndTerminate();
    }
    freeTexture(textureImg);
    *w=rectangle.w;
    *h=rectangle.h;
    
}

//trouver et désactiver la partie qui affiche l'image
void sprite3(int posX, int posY, char *imgBMPSrc, int *w,int *h) {
    /* @brief affiche un image .bmp sur le renderer
     */
    checkPos(posX, posY);
    SDL_Texture *textureImg = NULL;
    SDL_Surface *surfaceImg = NULL;
    if (!(surfaceImg = SDL_LoadBMP(imgBMPSrc))) {
        SDL_Log("ERREUR : chargement img > %s\nParametres passes %d , %d, %s\n",SDL_GetError(), posX, posY, imgBMPSrc);
        freeAndTerminate();
    }
    textureImg = SDL_CreateTextureFromSurface(renderer, surfaceImg);
    SDL_FreeSurface(surfaceImg);
    if (textureImg == NULL) {
        SDL_Log("ERREUR : chargement texture > %s\nParametres passes %d , %d, %s\n",SDL_GetError(), posX, posY, imgBMPSrc);
        freeTexture(textureImg);
        freeAndTerminate();
    }

    SDL_Rect hitBox;
    if (SDL_QueryTexture(textureImg, NULL, NULL, &hitBox.w, &hitBox.h)) {
        SDL_Log("ERREUR : image : query texture > %s\nParametres passes %d , %d, %s\n",SDL_GetError(), posX, posY, imgBMPSrc);
        freeTexture(textureImg);
        freeAndTerminate();
    }
    hitBox.x = posX;
    hitBox.y = posY;
/*    if (SDL_RenderCopy(renderer, textureImg, NULL, &rectangle) != 0) {
        SDL_Log("ERREUR: image : RenderCopy > %s\nParametres passes %d , %d, %s\n",SDL_GetError(), posX, posY, imgBMPSrc);
        freeTexture(textureImg);
        freeAndTerminate();
    }*/
    freeTexture(textureImg);
    *w=hitBox.w;
    *h=hitBox.h;
    
}


void lastKeyPressed(SDL_Event *event) {
    /** @brief affiche dans le terminal le caractère associé à la dernière touche appuyée
     *         ne fonctionne que si le type de l'event est SDL_KEYDOWN
     *         la gestion d'évènement se fait avec SDL_PollEvent(&event)
     *  @param event l'evenement qui s'est produit
     */
    if (event->type == SDL_KEYDOWN) {
        printf("Last Key Pressed: %c\n", event->key.keysym.sym);
    }
}

//imprime les briques
void jellyfish(int a, int b){   
    sprite(a,b,"jellyfish.bmp");   
}

void jellyfishPrint(){
    for (int j=0;j<100;j++){
        if (level[numLevel].tableLevel[2][j]==1){
            jellyfish(level[numLevel].tableLevel[0][j],level[numLevel].tableLevel[1][j]);        
        }
    }
}

//fait rebondir contre la brique et la supprime
//créer une structure pour les tableaux pour gérer les interactions
void interaction(){
   SDL_Rect hitBoxJellyfish = hitBoxSizeJellyfish(); //va récupérer les dimensions de l'image pour les hitBox
   SDL_Rect hitBoxTurtle = hitBoxSizeTurtle();

    for (int j=0;j<100;j++){

//position précédente de la balle
      int a=x-vx;
      int b=y-vy;
//chemin entre les 2 positions de la balle
      float R = sqrt(pow((x-a),2)+(pow((y-b),2)));
//coordonnées du coin haut gauche de la brique
        int xtest;
        int ytest;
        xtest=level[numLevel].tableLevel[0][j]; 
        ytest=level[numLevel].tableLevel[1][j];
//tester toutes les positions intermédiaires
        for (int i=0;i<=(int)R;i++){
            a=a+i;
            b=b+i;
            //contact par le bas
            if ((vy<0) && ((b<=(ytest+hitBoxJellyfish.h)) && (b>=(ytest)) && ((((a+10)>=(xtest)) && ((a+10)<=(xtest+hitBoxJellyfish.w)))))){   
                if ((level[numLevel].tableLevel[2][j])==1){
                printf("Bas atteint\n");
                printf("Bas a :%d b :%d xtest : %d ytest : %d \n", a,b,xtest,ytest );
                    vy=vy*-1;
                    level[numLevel].tableLevel[2][j]=0;
                    y=(ytest+hitBoxJellyfish.h+1);
                    x=a;
                }
            }
            //contact par le haut
            else if ((vy>0) && ((b+20)>=(ytest)) && ((b+20)<=(ytest+hitBoxJellyfish.h)) && (((a+10)>=(xtest)) && ((a+10)<=(xtest+hitBoxJellyfish.w)))){
                if ((level[numLevel].tableLevel[2][j])==1){  
            printf("Haut atteint\n");
            printf("Haut a :%d b :%d xtest : %d ytest : %d \n", a,b,xtest,ytest );
                    vy=vy*-1;
                    level[numLevel].tableLevel[2][j]=0;
                    y=(ytest-21);
                    x=a;
                }
            }
            //contact par la gauche
            else if ((vx>0) && (((a+20)>=(xtest)) && ((a+10)<=(xtest+hitBoxJellyfish.w))) && (((b+10)>=(ytest)) && ((b+10)<=(ytest+hitBoxJellyfish.h)))){
                if ((level[numLevel].tableLevel[2][j])==1){  
                            printf("Gauche atteint\n");
                printf("Gauche a :%d b :%d xtest : %d ytest : %d \n", a,b,xtest,ytest );
                    vx=vx*-1;
                    level[numLevel].tableLevel[2][j]=0;
                    x=(xtest-21);
                    y=b;
                }                                  
            }
            //contact par la droite
            else if ((vx<0) && ((a>=(xtest)) && (a<=(xtest+hitBoxJellyfish.w))) && (((b+10)>=(ytest)) && ((b+10)<=(ytest+hitBoxJellyfish.h)))){
                if ((level[numLevel].tableLevel[2][j])==1){  
                            printf("Droite atteint\n");
                printf("Droite a :%d b :%d xtest : %d ytest : %d \n", a,b,xtest,ytest );
                    vx=vx*-1;
                    level[numLevel].tableLevel[2][j]=0;
                    x=(xtest+hitBoxJellyfish.w+1);
                    y=b;
                }                
            }
            else{}
        }
    }
}

void gameEnd(){
    int gameOn=0;
    for (int j=0;j<100;j++){
        if (level[numLevel].tableLevel[2][j]==1){
            gameOn=1;
        }     
    }
    switch (gameOn){
      case 1:
      gameOn=0;
      break;
      case 0:
          sprite (0,0,"win.bmp");
          actualize();
          usleep(200000000 / FPS);
          freeAndTerminate(); 
    }
}

void background(){
    sprite(0,0,"background.bmp");
}

void vie(){
    nbVie=nbVie-1;
        if (nbVie>=0){
        x=500;
        y=800;
        sprite (0,0,"goAgain.bmp");  //image à créer
        actualize();
        usleep(100000000 / FPS);
        vx=4;
        vy=-4;
        speedVar=5;
      }  
      else{
        sprite (0,0,"lost.bmp");
        actualize();
        usleep(200000000 / FPS);
        freeAndTerminate();
      }
}
void printVie(){
    for (int i=0;i<=(nbVie);i++){
        xheart=10+50*i;
        sprite(xheart,yheart,"heart.bmp");
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
  //faire évoluer la fonction speed en fonction des rebonds     
    //créer un gradient de 0 à 100 pour modifier l'angle entre 30° et 60°, utiliser la fonction speed
    
void rebondTortue(){
    if(y>(yRect-8) && y<(yRect+10) && x>(xRect-20) && x<=(xRect+80)){
      float posRebond;
      posRebond = (x-xRect) / 100;
      angle=30+posRebond*30;   //fait évoluer l'angle entre 30 et 60 suivant la position sur la barre
      vecteurSpeed();
      vy=vy*-1;
        if (vx>0){
          vx=vx*-1;
        }
        else {}
      y=yRect-10;
    }
    
    //centre, pas de modification de la direction
    else if((y>(yRect-8)) && y<(yRect+10) && x>(xRect+80) && x<(xRect+120)){
      angle=60;
      vecteurSpeed();
      vy=vy*-1;
      y=yRect-10;
    }
    //droite, renvoyer vers la droite
    else if(y>(yRect-8) && y<(yRect+10) && x>=(xRect+120) && x<(xRect+200)){
      float posRebond;
      posRebond = (x-(xRect+120)) / 80;
      angle=30+posRebond*30;   //fait évoluer l'angle entre 30 et 60 suivant la position sur la barre
      vecteurSpeed();
      vy=vy*-1;
        if (vx<0){
          vx=vx*-1;
        }
        else {}
      y=yRect-10;
    }
}

void rebondBords(){
    if (x>(979)){   //window_width-rayon de la balle-1 pour éviter le contact
      vx=vx*-1;         //renvoie dans l'autre sens
      x=979;
    }
    else if(x<1){
      vx=vx*-1;
      x=1;
    }
    else if(y<11){
      vy=vy*-1;
      y=11;
    }

    else if (y>(yRect-8) && y<(yRect+10) && x>(xRect-20) && x<=(xRect+200)) {
      rebondTortue();
    }
    else if (y>1000){
      vie();
    }
    else {}
}


//Déplacement de la raquette
void turtle(){
    int vMax=30;
    int vMin=10;
    int vTurtle=vMin;
    if (deplacementGauche==1){
      xRect=xRect-2*vTurtle;
    }
    else if (deplacementDroite==1){
      xRect=xRect+2*vTurtle;    
    }
    if(xRect<0){
      xRect=0;
    }
    else if(xRect>800){
      xRect=800;
    }
    sprite(xRect,yRect,"turtle.bmp");
}

void waterDrop(){
    if (vx<0 && vy<0){
        sprite(x,y,"waterDrophg.bmp");
    }
    else if (vx<0 && vy>0){
        sprite(x,y,"waterDropbg.bmp");
    }
    if (vx>0 && vy<0){
        sprite(x,y,"waterDrophd.bmp");
    }
    else if (vx>0 && vy>0){
        sprite(x,y,"waterDropbd.bmp");
    }
}
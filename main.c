#include <SDL2/SDL.h>
#include <unistd.h>
#include "function.h"
#include <time.h>

#define WINDOW_WIDTH 700
#define WINDOW_HEIGHT 920
#define FPS 60

//couleur aléatoire à chaque rebond
//changer la vitesse
//Créer une raquette qui se déplace de gauche à droite
//pour éviter la raquette qui devient transparente faire un supérieur ou égal
//faire une balle qui rebondi sur la raquette
//créer des briques et faire disparaître les briques au rebond (tableau)

//position du carre dessiné dans drawGame()
int x = 40;
int y = 40;
int vx=0;
int vy=0;
//couleurs
int r=247;
int g=146;
int b=1;

void couleurAleatoire(){
      r=rand()%256;
      g=rand()%256;
      b=rand()%256;
}

void init_game(){

}

void speed(){
    x=x+vx;
    y=y+vy;
}

void rebond(){  //attention, là balle qui colle à la bordure
    if (x>(689)){   //window_width-rayon de la balle-1 pour éviter le contact
      vx=vx*-1;
      couleurAleatoire();
    }
    else if(x<11){
      vx=vx*-1;
      couleurAleatoire();
    }
    else if(y<11){
      couleurAleatoire();
      vy=vy*-1;
    }
    else if(y>909){
      vy=vy*-1;
      couleurAleatoire();
    }
}

void drawGame(){
    /* Ici je dessine mon jeu
     * exemple position x, y modifiés dans KeyPressed() et utilisés pour
     * pouvoir deplacer la figure à chaque boucle de gameLoop()
     */
    clear();
    speed();
    rebond();
    changeColor(r,g,b);
    drawCircle(x,y,10);
    actualize();
    usleep(100000 / FPS); // 60 images par seconde | 1000000 = 1 seconde
}
void KeyPressed(SDL_Keycode touche){
    /** @brief event.key.keysym.sym renvoi la touche appuyé
     */
    int speedx=1;
    int speedy=1;
    
    switch (touche) {
        case SDLK_q:
            vx=-1*speedx;
            vy=0*speedy;
            break;
        case SDLK_d:
            vx=1*speedx;
            vy=0*speedy;
            break;
        case SDLK_z:
            vx=0*speedx;
            vy=-1*speedy;
            break;
        case SDLK_s:
            vx=0*speedx;
            vy=1*speedy;
            break;
        case SDLK_PLUS:
            speedx=speedx+2;
            speedy=speedy+2;
            break;
        case SDLK_MINUS:
            speedx=speedx-2;
            speedy=speedy-2;
            break;
        case SDLK_ESCAPE:
            freeAndTerminate();
            break;
        default:
            break;
    }
}
void joyButtonPressed(){
}

void gameLoop() {
    int programLaunched = 1;
    while (programLaunched == 1) {
        // Boucle pour garder le programme ouvert
        // lorsque programLaunched est different de 1
        // on sort de la boucle, donc de la fonction
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            // boucle pour la gestion d'évenement
            switch (event.type) {
                /** event.type renvoi le type d'evenement qui se passe
                 * (si on appuie sur une touche, clique de souris...)
                 * en fonction du type d'évènement on à alors
                 * différentes information accessibles
                 * voir doc pour plus d'event https://wiki.libsdl.org/SDL_EventType
                 */
                case SDL_QUIT:
                    // quand on clique sur fermer la fénêtre en haut à droite
                    programLaunched = 0;
                    break;
                case SDL_MOUSEBUTTONUP:
                    /* clique de la souris
                     * event.motion.y | event.motion.x pour les positions de la souris
                     */
                    printf("position de la souris x : %d , y : %d\n", event.motion.x, event.motion.y);
                    break;
                case SDL_KEYDOWN:
                    KeyPressed(event.key.keysym.sym);
                    break;
                case SDL_JOYBUTTONDOWN:
                    break;
                default:
                    break;
            }
        }
        /* coder ici pour que le code s'execute après chaque évenement
         * exemple dessiner un carré avec position int x, int y qu'on peut
         * deplacer lorsqu'on appuie sur une touche
         */
        drawGame();
    }
}

int main(){
    /** @description 3 fonctions dans le main qui permettent de créer l'application et la maintenir ouverte :
     *  init(...) : initialiser la SDL/ fenêtre
     *  gameLoop() : boucle de jeu dans laquelle l'application reste ouverte
     *  freeAndTerminate() : quitte le programme proprement
     */
    init(WINDOW_WIDTH, WINDOW_HEIGHT);
    init_game();
    gameLoop();
    printf("Fin du programme\n");
    freeAndTerminate();
}

/**
 * \file main.c
 * \brief Programme principal initial du niveau 0
 * \author Mathieu Constant, Denys Shcherba, Ivan Osadtsiv
 * \version 1.0
 * \date 18 mars 2020
 */

#include <stdio.h>
#include "sdl2-light.h"


/**
 * \brief Largeur de l'écran
*/


#define SCREEN_WIDTH 320

/**
 * \brief Hauteur de l'écran
*/

#define SCREEN_HEIGHT 240

/**
 * \brief Taille du sprite
*/

#define SPRITE_SIZE 32

/**
 * \brief Pas de déplacement du sprite
*/

#define MOVING_STEP 5

/**
 * \brief Représentation pour stocker les textures nécessaires à l'affichage graphique
*/

struct textures_s{
    SDL_Texture* background; /*!< Texture liée à l'image du fond de l'écran. */
    SDL_Texture* sprite;  /*!< Stockera la texture liée au personnage. */
};


/**
 * \brief Type qui correspond aux textures du jeu
*/

typedef struct textures_s resources_t;


/**
 * \brief Représentation du monde du jeu
*/

struct world_s{
    int pos_x;
    int pos_y;
    
    int gameover; /*!< Champ indiquant si l'on est à la fin du jeu */

};

/**
 * \brief Type qui correspond aux données du monde
 */

typedef struct world_s world_t;





/**
 * \brief La fonction initialise les données du monde du jeu
 * \param world les données du monde
 */


void init_data(world_t * world){
    
    //on n'est pas à la fin du jeu
    world->gameover = 0;
    world->pos_x = (SCREEN_WIDTH-SPRITE_SIZE)/2;
    world->pos_y = (SCREEN_HEIGHT-SPRITE_SIZE)/2;
}


/**
 * \brief La fonction nettoie les données du monde
 * \param world les données du monde
 */


void clean_data(world_t *world){
    /* utile uniquement si vous avez fait de l'allocation dynamique (malloc); la fonction ici doit permettre de libérer la mémoire (free) */
    
}



/**
 * \brief La fonction indique si le jeu est fini en fonction des données du monde
 * \param world les données du monde
 * \return 1 si le jeu est fini, 0 sinon
 */

int is_game_over(world_t *world){
    return world->gameover;
}



/**
 * \brief La fonction met à jour les données en tenant compte de la physique du monde
 * \param les données du monde
 */

void update_data(world_t *world){
    /* A COMPLETER */
}



/**
 * \brief La fonction gère les évènements ayant eu lieu et qui n'ont pas encore été traités
 * \param event paramètre qui contient les événements
 * \param world les données du monde
 */

void handle_events(SDL_Event *event,world_t *world){
    Uint8 *keystates;
    while( SDL_PollEvent( event ) ) {
        
        //Si l'utilisateur a cliqué sur le X de la fenêtre
        if( event->type == SDL_QUIT ) {
            //On indique la fin du jeu
            world->gameover = 1;
        }
       
        //si une touche est appuyée
        if(event->type == SDL_KEYDOWN){
            switch (event->key.keysym.sym)
            {
            //si la touche appuyée est 'D'
            case SDLK_d:
                printf("La touche D est appuyée\n");
                break;
            // si la touche appuyée est 'DOWN'
            case SDLK_DOWN:
                (world->pos_y) += MOVING_STEP;
                break;
            // si la touche appuyée est 'UP'
            case SDLK_UP:
                (world->pos_y) -= MOVING_STEP;
                break;
            // si la touche appuyée est 'RIGHT'
            case SDLK_RIGHT:
                (world->pos_x) += MOVING_STEP;
                break;
            // si la touche appuyée est 'LEFT'
            case SDLK_LEFT:
                (world->pos_x) -= MOVING_STEP;
                break;
            }
        }
    }
}


/**
 * \brief La fonction nettoie les textures
 * \param textures les textures
*/

void clean_textures(resources_t *textures){
    clean_texture(textures->background);
    clean_texture(textures->sprite);
}



/**
 * \brief La fonction initialise les texures
 * \param screen la surface correspondant à l'écran de jeu
 * \param textures les textures du jeu
*/

void  init_textures(SDL_Renderer *renderer, resources_t *textures){
    textures->background = load_image( "ressources/background.bmp",renderer);
    
    textures->sprite = load_image("ressources/sprite.bmp", renderer);

    
}


/**
 * \brief La fonction applique la texture du fond sur le renderer lié à l'écran de jeu
 * \param renderer le renderer
 * \param textures les textures du jeu
*/

void apply_background(SDL_Renderer *renderer, resources_t *textures){
    if(textures->background != NULL){
      apply_texture(textures->background, renderer, 0, 0);
    }
}





/**
 * \brief La fonction rafraichit l'écran en fonction de l'état des données du monde
 * \param renderer le renderer
 * \param world les données du monde
 * \param textures les textures du jeu
 */

void refresh_graphics(SDL_Renderer *renderer, world_t *world,resources_t *textures){
    
    //on vide le renderer
    clear_renderer(renderer);
    
    //application des textures dans le renderer
    apply_background(renderer, textures);
    apply_texture(textures->sprite, renderer, world->pos_x, world->pos_y);
    
    // on met à jour l'écran
    update_screen(renderer);
}



/**
* \brief fonction qui nettoie le jeu: nettoyage de la partie graphique (SDL), nettoyage des textures, nettoyage des données
* \param window la fenêtre du jeu
* \param renderer le renderer
* \param textures les textures
* \param world le monde
*/

void clean(SDL_Window *window, SDL_Renderer * renderer, resources_t *textures, world_t * world){
    clean_data(world);
    clean_textures(textures);
    clean_sdl(renderer,window);
}



/**
 * \brief fonction qui initialise le jeu: initialisation de la partie graphique (SDL), chargement des textures, initialisation des données
 * \param window la fenêtre du jeu
 * \param renderer le renderer
 * \param textures les textures
 * \param wordl le monde
 */

void init(SDL_Window **window, SDL_Renderer ** renderer, resources_t *textures, world_t * world){
    init_sdl(window,renderer,SCREEN_WIDTH, SCREEN_HEIGHT);
    init_data(world);
    init_textures(*renderer,textures);
}


/**
 *  \brief programme principal qui implémente la boucle du jeu
 */


int main( int argc, char* args[] )
{
    SDL_Event event;
    world_t world;
    resources_t textures;
    SDL_Renderer *renderer;
    SDL_Window *window;

    //initialisation du jeu
    init(&window,&renderer,&textures,&world);
    
    while(!is_game_over(&world)){ //tant que le jeu n'est pas fini
        
        //gestion des évènements
        handle_events(&event,&world);
        
        //mise à jour des données liée à la physique du monde
        update_data(&world);
        
        //rafraichissement de l'écran
        refresh_graphics(renderer,&world,&textures);
        
        // pause de 10 ms pour controler la vitesse de rafraichissement
        pause(10);
    }
    
    //nettoyage final
    clean(window,renderer,&textures,&world);
    
    
    return 0;
} 

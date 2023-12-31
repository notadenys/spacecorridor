/// @file           space_const.h
/// @author         SHCHERBA Denys, OSADTSIV Ivan
/// @brief          File with all the constants needed in game


#ifndef SPACE_CONST_H
#define SPACE_CONST_H

#include "sdl2-light.h"


/// @brief          Largeur de l'écran de jeu
#define SCREEN_WIDTH 300


/// @brief          Hauteur de l'écran de jeu
#define SCREEN_HEIGHT 480


/// @brief          Taille d'un vaisseau
#define SHIP_SIZE 32


/// @brief          Taille d'un météorite
#define METEORITE_SIZE 32


/// @brief          Hauteur de la ligne d'arrivée
#define FINISH_LINE_HEIGHT -960


/// @brief          Pas de déplacement horizontal du vaisseau
#define MOVING_STEP 10


/// @brief          Vitesse initiale de déplacement vertical des éléments du jeu 
#define INITIAL_SPEED 2


/// @brief          Pas de changement de vitesse
#define SPEED_DELTA 0.5

#endif

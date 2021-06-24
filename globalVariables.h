#include<SDL2/SDL.h>

#ifndef  EXTERN
#define  EXTERN  extern
#endif


EXTERN SDL_Window* window;
EXTERN SDL_Renderer* rend;
EXTERN SDL_Surface* surface;
EXTERN SDL_Texture* texcharacter;
EXTERN SDL_Texture* texStartScreen;
EXTERN SDL_Texture* texBackground;
EXTERN SDL_Texture* texPathway;

EXTERN SDL_Rect characterPos, backgroundPos, backgroundAnchor, pathwayPos, pathwayAnchor;
EXTERN char characterDirection;
EXTERN int CHARACTER_MOVEMENT_STEP_X, CHARACTER_MOVEMENT_STEP_Y;

EXTERN int SCREEN_WIDTH;
EXTERN int SCREEN_HEIGHT;
EXTERN int START_GAME_BTN_LEFT_X ;
EXTERN int START_GAME_BTN_LEFT_Y ;
EXTERN int START_GAME_BTN_RIGHT_X ;
EXTERN int START_GAME_BTN_RIGHT_Y ;

EXTERN char mapMatrix[17][68];
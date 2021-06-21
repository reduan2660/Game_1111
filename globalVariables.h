#include<SDL2/SDL.h>

#ifndef  EXTERN
#define  EXTERN  extern
#endif


EXTERN SDL_Window* window;
EXTERN SDL_Renderer* rend;
EXTERN SDL_Surface* surface;
EXTERN SDL_Texture* texCharecter;
EXTERN SDL_Texture* texStartScreen;
EXTERN SDL_Texture* texBackground;

EXTERN SDL_Rect charecterPos, backgroundPos, backgroundAnchor;
EXTERN char characterDirection;
EXTERN int CHARACTER_MOVEMENT_STEP_X, CHARACTER_MOVEMENT_STEP_Y;

EXTERN int START_GAME_BTN_LEFT_X ;
EXTERN int START_GAME_BTN_LEFT_Y ;
EXTERN int START_GAME_BTN_RIGHT_X ;
EXTERN int START_GAME_BTN_RIGHT_Y ;
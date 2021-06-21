#include<SDL2/SDL.h>

#ifndef  EXTERN
#define  EXTERN  extern
#endif

EXTERN SDL_Rect startScreenPos, mapPos, charecterPos, cluePos, tresurePos;
EXTERN char characterDirection;
EXTERN int CHARACTER_MOVEMENT_STEP_X, CHARACTER_MOVEMENT_STEP_Y;
#include<SDL2/SDL.h>

#ifndef  EXTERN
#define  EXTERN  extern

struct Bullets {
    char direction;
    int initX;
    int initY;
    SDL_Rect bulletPosition;
    bool active;
};


struct EnemyAliveState {
    bool bird[3];
    bool bomb[3];
    bool snail[6];
};


struct ExplosiveEnemy {
    bool bird[3];
    bool bomb[3];
    bool snail[6];

    //  frame informations
    int birdFrame[3] = {0,0,0};
    int bombFrame[3] = {0,0,0};
    int snailFrame[6] = {0,0,0,0,0,0};
};


#endif


EXTERN SDL_Window* window;
EXTERN SDL_Renderer* rend;
EXTERN SDL_Surface* surface;
EXTERN SDL_Texture* texcharacter;
EXTERN SDL_Texture* texcharacter_R[10];
EXTERN SDL_Texture* texcharacter_L[10];
EXTERN SDL_Texture* texShooting;
EXTERN SDL_Texture* texShooting_R[10];
EXTERN SDL_Texture* texShooting_L[10];
EXTERN SDL_Texture* texBird;
EXTERN SDL_Texture* texBird_R[6];
EXTERN SDL_Texture* texBird_L[6];
EXTERN SDL_Texture* texBomb;
EXTERN SDL_Texture* texBomb_R[6];
EXTERN SDL_Texture* texBomb_L[6];
EXTERN SDL_Texture* texSnail;
EXTERN SDL_Texture* texSnail_R[6];
EXTERN SDL_Texture* texSnail_L[6];
EXTERN SDL_Texture* texExplosion[6];
EXTERN SDL_Texture* texBullet;
EXTERN SDL_Texture* texStartScreen;
EXTERN SDL_Texture* texGameOver;
EXTERN SDL_Texture* texBackground;
EXTERN SDL_Texture* texPathway;

EXTERN SDL_Rect characterPos, backgroundPos, backgroundAnchor, pathwayPos, pathwayAnchor, birdPos[3], bombPos[3], snailPos[6], GameOverPos;
EXTERN char characterDirection;
EXTERN int CHARACTER_MOVEMENT_STEP_X, CHARACTER_MOVEMENT_STEP_Y;

EXTERN int SCREEN_WIDTH;
EXTERN int SCREEN_HEIGHT;
EXTERN int TILE_X;
EXTERN int TILE_Y;
EXTERN int START_GAME_BTN_LEFT_X ;
EXTERN int START_GAME_BTN_LEFT_Y ;
EXTERN int START_GAME_BTN_RIGHT_X ;
EXTERN int START_GAME_BTN_RIGHT_Y ;

EXTERN char mapMatrix[17][68];

EXTERN int bullet_fired_character_cur_frame;
EXTERN int BULLET_FIRED_CHARACTER_FRAME;
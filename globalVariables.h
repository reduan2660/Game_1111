#include<SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

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
EXTERN SDL_Texture* texGameWon;
EXTERN SDL_Texture* texBackground;
EXTERN SDL_Texture* texPathway;

EXTERN SDL_Rect characterPos, backgroundPos, backgroundAnchor, pathwayPos, pathwayAnchor, birdPos[10], bombPos[10], snailPos[10], GameOverPos;
EXTERN char characterDirection;
EXTERN int CHARACTER_MOVEMENT_STEP_X, CHARACTER_MOVEMENT_STEP_Y;

EXTERN int SCREEN_WIDTH;
EXTERN int SCREEN_HEIGHT;
EXTERN int TILE_X;
EXTERN int TILE_Y;

EXTERN int NEW_GAME_BTN_LEFT_X ;
EXTERN int NEW_GAME_BTN_LEFT_Y ;
EXTERN int NEW_GAME_BTN_RIGHT_X ;
EXTERN int NEW_GAME_BTN_RIGHT_Y ;

EXTERN int RESUME_GAME_BTN_LEFT_X ;
EXTERN int RESUME_GAME_BTN_LEFT_Y ;
EXTERN int RESUME_GAME_BTN_RIGHT_X ;
EXTERN int RESUME_GAME_BTN_RIGHT_Y ;


EXTERN int EXIT_GAME_BTN_LEFT_X ;
EXTERN int EXIT_GAME_BTN_LEFT_Y ;
EXTERN int EXIT_GAME_BTN_RIGHT_X ;
EXTERN int EXIT_GAME_BTN_RIGHT_Y ;


EXTERN char mapMatrix[17][68];

EXTERN int bullet_fired_character_cur_frame;
EXTERN int BULLET_FIRED_CHARACTER_FRAME;

EXTERN int ENEMY_1_snail;
EXTERN int ENEMY_2_bomb;
EXTERN int ENEMY_3_bird;



EXTERN Mix_Music *background_music;
EXTERN Mix_Chunk *sBulletFired;
EXTERN Mix_Chunk *sEnemyDied;
EXTERN Mix_Chunk *sJump;
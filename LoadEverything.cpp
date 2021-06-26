#include "LoadEverything.h"
#include "globalVariables.h"


// SDL and Default Librariescha
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <bits/stdc++.h>
#include <fstream>

bool startScreen()
{
    surface = NULL;
    surface = IMG_Load("./files/images/StartScreen.png");
    if(surface == NULL){
        std::cout << "Error Loading Image" << std::endl;
        return false;
    }
    texStartScreen = NULL;
    texStartScreen = SDL_CreateTextureFromSurface(rend, surface);
    if(!texStartScreen){
        return false;
    }
    // ? Load Game Over Screen
    surface = NULL;
    surface = IMG_Load("./files/images/Game-Over.png");
    if(surface == NULL){
        std::cout << "Error Loading Game Over" << std::endl;
        return false;
    }
    texGameOver = NULL;
    texGameOver = SDL_CreateTextureFromSurface(rend, surface);
    if(!texGameOver){
        return false;
    }

    surface = NULL;
    surface = IMG_Load("./files/images/Game_won.png");
    if(surface == NULL){
        std::cout << "Error Loading Game Win Sreen" << std::endl;
        return false;
    }

    texGameWon = NULL;
    texGameWon = SDL_CreateTextureFromSurface(rend, surface);
    if(!texGameWon){
        return false;
    }
    return true;
}

bool loadGameBackground(int PLAYER_CURRENT_LEVEL)
{   

    surface = NULL;
    if(PLAYER_CURRENT_LEVEL == 1 ) surface = IMG_Load("./files/images/Game-level-1/bg.png");
    if(PLAYER_CURRENT_LEVEL == 2 ) surface = IMG_Load("./files/images/Game-level-2/bg.png");
    if(PLAYER_CURRENT_LEVEL == 3 ) surface = IMG_Load("./files/images/Game-level-3/bg.png");
    if(surface == NULL){
        std::cout << "Error Loading Background" << std::endl;
        return false;
    }

    texBackground = NULL;
    texBackground = SDL_CreateTextureFromSurface(rend, surface);
    if(!texBackground){
        return false;
    }

    
    return true;
}

bool loadGamePathway(int PLAYER_CURRENT_LEVEL){
    surface = NULL;
    if(PLAYER_CURRENT_LEVEL == 1 ) surface = IMG_Load("./files/images/Game-level-1/pathway.png");
    if(PLAYER_CURRENT_LEVEL == 2 ) surface = IMG_Load("./files/images/Game-level-2/pathway.png");
    if(PLAYER_CURRENT_LEVEL == 3 ) surface = IMG_Load("./files/images/Game-level-3/pathway.png");
    if(surface == NULL){
        std::cout << "Error Loading Pathway" << std::endl;
        return false;
    }

    texPathway = NULL;
    texPathway = SDL_CreateTextureFromSurface(rend, surface);
    if(!texPathway){
        return false;
    }
    return true;
}

bool loadCharacter()
{   
    // ? Movement
    for(int i=0;i<9;i++){
        // Right Direction
        surface = NULL;
        char filename[] = "./files/images/Character-movement/Right/Character1.png";
        filename[49] = 49 + i;
        
        surface = IMG_Load(filename);
        if(surface == NULL){
            std::cout << "Error Loading Character" << std::endl;
            return false;
        }
        texcharacter_R[i] = NULL;
        texcharacter_R[i] = SDL_CreateTextureFromSurface(rend, surface);
        if(!texcharacter_R[i]){
            return false;
        }

        // Left Direction
        surface = NULL;
        char filename_L[] = "./files/images/Character-movement/Left/Character1flip.png";
        filename_L[48] = 49 + i;
        
        surface = IMG_Load(filename_L);
        if(surface == NULL){
            std::cout << "Error Loading Character" << std::endl;
            return false;
        }
        texcharacter_L[i] = NULL;
        texcharacter_L[i] = SDL_CreateTextureFromSurface(rend, surface);
        if(!texcharacter_L[i]){
            return false;
        }
    }
    texcharacter = texcharacter_R[0];

    // ? Shooting
    for(int i=0;i<9;i++){
        // Right Direction
        surface = NULL;
        char filename[] = "./files/images/Character-shooting/Right/Character1.png";
        filename[49] = 49 + i;
        
        surface = IMG_Load(filename);
        if(surface == NULL){
            std::cout << "Error Loading Character SHooting" << std::endl;
            return false;
        }
        texShooting_R[i] = NULL;
        texShooting_R[i] = SDL_CreateTextureFromSurface(rend, surface);
        if(!texShooting_R[i]){
            return false;
        }

        // Left Direction
        surface = NULL;
        char filename_L[] = "./files/images/Character-shooting/Left/Character1flip.png";
        filename_L[48] = 49 + i;
        
        surface = IMG_Load(filename_L);
        if(surface == NULL){
            std::cout << "Error Loading Character SHooting" << std::endl;
            return false;
        }
        texShooting_L[i] = NULL;
        texShooting_L[i] = SDL_CreateTextureFromSurface(rend, surface);
        if(!texShooting_L[i]){
            return false;
        }
    }
    
    return true;
}


bool loadMatrix(int PLAYER_CURRENT_LEVEL){

    ENEMY_1_snail = 0;
    ENEMY_2_bomb = 0;
    ENEMY_3_bird = 0;
    if(PLAYER_CURRENT_LEVEL == 1){
        std::ifstream FILE_MATRIX("./files/images/Game-level-1/matrix/matrix.txt");
        for(int row = 0; row < 17; row++){
            for(int column = 0; column < 68; column++){
                FILE_MATRIX >> mapMatrix[row][column];
                if(mapMatrix[row][column] == '7') ENEMY_2_bomb++;
                if(mapMatrix[row][column] == '5') ENEMY_1_snail++;
                if(mapMatrix[row][column] == '6') ENEMY_3_bird++;
            }    
        }
        FILE_MATRIX.close();


    }
    if(PLAYER_CURRENT_LEVEL == 2){
        std::ifstream FILE_MATRIX("./files/images/Game-level-2/Matrix.txt");
        for(int row = 0; row < 17; row++){
            for(int column = 0; column < 68; column++){
                FILE_MATRIX >> mapMatrix[row][column];
                if(mapMatrix[row][column] == '7') ENEMY_2_bomb++;
                if(mapMatrix[row][column] == '5') ENEMY_1_snail++;
                if(mapMatrix[row][column] == '6') ENEMY_3_bird++;
            }    
        }
        FILE_MATRIX.close();
    }
    if(PLAYER_CURRENT_LEVEL == 3){
        std::ifstream FILE_MATRIX("./files/images/Game-level-3/Matrix.txt");
        for(int row = 0; row < 17; row++){
            for(int column = 0; column < 68; column++){
                FILE_MATRIX >> mapMatrix[row][column];
                if(mapMatrix[row][column] == '7') ENEMY_2_bomb++;
                if(mapMatrix[row][column] == '5') ENEMY_1_snail++;
                if(mapMatrix[row][column] == '6') ENEMY_3_bird++;
            }    
        }
        FILE_MATRIX.close();
    }
    return true;    
}

bool loadEnemy(int PLAYER_CURRENT_LEVEL)
{   
    
    for(int i=0;i<6;i++){
        //  Bird Left
        surface = NULL;
        if(PLAYER_CURRENT_LEVEL == 1||PLAYER_CURRENT_LEVEL==3){
            char filename[] = "./files/images/Game-level-1/Bird/Left/enemy-bird-src-1.png";
            filename[53] = 49 + i;
            surface = IMG_Load(filename);
        }else if(PLAYER_CURRENT_LEVEL == 2){
            char filename[] = "./files/images/Game-level-2/Bird/Left/enemy-bird-src-1.png";
            filename[53] = 49 + i;
            surface = IMG_Load(filename);
        }
        
        if(surface == NULL){
            std::cout << "Error Loading Bird" << std::endl;
            return false;
        }
        texBird_R[i] = NULL;
        texBird_R[i] = SDL_CreateTextureFromSurface(rend, surface);
        if(!texBird_R[i]){
            return false;
        }

        // Bird Right
        if(PLAYER_CURRENT_LEVEL == 1||PLAYER_CURRENT_LEVEL ==3){        
            surface = NULL;
            char filename_L[] = "./files/images/Game-level-1/Bird/Right/enemy-bird-src-1flip.png";
            filename_L[54] = 49 + i;
            surface = IMG_Load(filename_L);
        }else if(PLAYER_CURRENT_LEVEL == 2){        
            surface = NULL;
            char filename_L[] = "./files/images/Game-level-2/Bird/Right/enemy-bird-src-1flip.png";
            filename_L[54] = 49 + i;
            surface = IMG_Load(filename_L);
        }
        if(surface == NULL){
            std::cout << "Error Loading Bird" << std::endl;
            return false;
        }
        texBird_L[i] = NULL;
        texBird_L[i] = SDL_CreateTextureFromSurface(rend, surface);
        if(!texBird_L[i]){
            return false;
        }
    }
    texBird = texBird_R[0];

    for(int i=0;i<6;i++){
        //  Bomb Right
        surface = NULL;
        char filename[] = "./files/images/Game-level-1/Bomb/Right/enemy-bomb-src-1flip.png";
        filename[54] = 49 + i;
        surface = IMG_Load(filename);
        if(surface == NULL){
            std::cout << "Error Loading Bomb L" << std::endl;
            return false;
        }
        texBomb_R[i] = NULL;
        texBomb_R[i] = SDL_CreateTextureFromSurface(rend, surface);
        if(!texBomb_R[i]){
            return false;
        }
        // Bomb Left
        surface = NULL;
        char filename_L[] = "./files/images/Game-level-1/Bomb/Left/enemy-bomb-src-1.png";
        filename_L[53] = 49 + i;
        surface = IMG_Load(filename_L);
        if(surface == NULL){
            std::cout << "Error Loading Bomb R" << std::endl;
            return false;
        }
        texBomb_L[i] = NULL;
        texBomb_L[i] = SDL_CreateTextureFromSurface(rend, surface);
        if(!texBomb_L[i]){
            return false;
        }
    }
    texBomb = texBomb_R[0];

    for(int i=0;i<6;i++){
        //  Snail Right
        surface = NULL;
        if(PLAYER_CURRENT_LEVEL ==1 || PLAYER_CURRENT_LEVEL == 3){
            char filename[] = "./files/images/Game-level-1/Snail/Right/enemy-src-1flip.png";
            filename[50] = 49 + i;
            surface = IMG_Load(filename);
        }
        else if(PLAYER_CURRENT_LEVEL == 2){
            char filename[] = "./files/images/Game-level-2/Snail/Right/Enemy-snail-src-1flip.png";
            filename[56] = 49 + i;
            surface = IMG_Load(filename);
        }
        if(surface == NULL){
            std::cout << "Error Loading Snail" << std::endl;
            return false;
        }
        texSnail_R[i] = NULL;
        texSnail_R[i] = SDL_CreateTextureFromSurface(rend, surface);
        if(!texSnail_R[i]){
            return false;
        }
        // Snail Left
        surface = NULL;
        if(PLAYER_CURRENT_LEVEL ==1 || PLAYER_CURRENT_LEVEL == 3){ 
            char filename_L[] = "./files/images/Game-level-1/Snail/Left/enemy-src-1.png";
            filename_L[49] = 49 + i;
            surface = IMG_Load(filename_L);
        }else if(PLAYER_CURRENT_LEVEL == 2){ 
            char filename_L[] = "./files/images/Game-level-2/Snail/Left/Enemy-snail-src-1.png";
            filename_L[55] = 49 + i;
            surface = IMG_Load(filename_L);
        }
        if(surface == NULL){
            std::cout << "Error Loading Snail" << std::endl;
            return false;
        }
        texSnail_L[i] = NULL;
        texSnail_L[i] = SDL_CreateTextureFromSurface(rend, surface);
        if(!texSnail_L[i]){
            return false;
        }
    }
    texSnail = texSnail_R[0];
    
    
    
    for(int i=0;i<6;i++){
        //  Explosion
        surface = NULL;
        char filename[] = "./files/images/Explosion/explosion-1.png";
        filename[35] = 49 + i;
        surface = IMG_Load(filename);
        if(surface == NULL){
            std::cout << "Error Loading Explosion" << std::endl;
            return false;
        }
        texExplosion[i] = NULL;
        texExplosion[i] = SDL_CreateTextureFromSurface(rend, surface);
        if(!texExplosion[i]){
            return false;
        }
    }
    
    return true;
}


bool loadBullet(){
    surface = NULL;
    surface = IMG_Load("./files/images/bullet.png");
    texBullet = SDL_CreateTextureFromSurface(rend, surface);
    if(!texBullet){
        printf("Error Loading Bullet Texture");
        return false;
    }
     return true;
}

bool loadSound(int PLAYER_CURRENT_LEVEL){
    // ?Background Music
    if(PLAYER_CURRENT_LEVEL == 1)    background_music = Mix_LoadMUS( "./files/Sounds/level-1.wav" );
    if(PLAYER_CURRENT_LEVEL == 2)    background_music = Mix_LoadMUS( "./files/Sounds/level-2.wav" );
    if(PLAYER_CURRENT_LEVEL == 3)    background_music = Mix_LoadMUS( "./files/Sounds/level-3.wav" );
    if( background_music == NULL )
    {
        printf( "Failed to load  music! SDL_mixer Error: %s\n", Mix_GetError() );
        return false;
    }

    //? Bullet Fried
    sBulletFired = Mix_LoadWAV( "./files/Sounds/Bullet-Fired.wav" );
    if( sBulletFired == NULL )
    {
        printf( "Failed to load  sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        return false;
    }

    //? Enemy Died
    sEnemyDied = Mix_LoadWAV( "./files/Sounds/Enemy-Died.wav" );
    if( sEnemyDied == NULL )
    {
        printf( "Failed to load  sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        return false;
    }

    //? Jump
    sJump = Mix_LoadWAV( "./files/Sounds/Jump.wav" );
    if( sJump == NULL )
    {
        printf( "Failed to load  sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        return false;
    }
    return true;
}


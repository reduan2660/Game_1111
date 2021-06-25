#include "LoadEverything.h"
#include "globalVariables.h"


// SDL and Default Librariescha
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <bits/stdc++.h>

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
    return true;
}

bool loadGameBackground(int PLAYER_CURRENT_LEVEL)
{   

    surface = NULL;
    if(PLAYER_CURRENT_LEVEL == 1 ) surface = IMG_Load("./files/images/Game-level-1/bg.png");
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


bool loadEnemy()
{   
    
    for(int i=0;i<6;i++){
        //  Bird Right
        surface = NULL;
        char filename[] = "./files/images/Game-level-1/Bird/Left/enemy-bird-src-1.png";
        filename[53] = 49 + i;
        
        surface = IMG_Load(filename);
        if(surface == NULL){
            std::cout << "Error Loading Bird" << std::endl;
            return false;
        }
        texBird_R[i] = NULL;
        texBird_R[i] = SDL_CreateTextureFromSurface(rend, surface);
        if(!texBird_R[i]){
            return false;
        }

        // Bird Left
        surface = NULL;
        char filename_L[] = "./files/images/Game-level-1/Bird/Right/enemy-bird-src-1flip.png";
        filename_L[54] = 49 + i;
        
        surface = IMG_Load(filename_L);
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
        char filename[] = "./files/images/Game-level-1/Snail/Right/enemy-src-1flip.png";
        filename[50] = 49 + i;
        surface = IMG_Load(filename);
        if(surface == NULL){
            std::cout << "Error Loading Snail" << std::endl;
            return false;
        }
        texSnail_R[i] = NULL;
        texSnail_R[i] = SDL_CreateTextureFromSurface(rend, surface);
        if(!texSnail_R[i]){
            return false;
        }
        // Bomb Left
        surface = NULL;
        char filename_L[] = "./files/images/Game-level-1/Snail/Left/enemy-src-1.png";
        filename_L[49] = 49 + i;
        surface = IMG_Load(filename_L);
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

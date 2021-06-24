#include "LoadEverything.h"
#include "globalVariables.h"


// SDL and Default Libraries
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
    surface = NULL;
    surface = IMG_Load("./files/images/character_temp.png");
    if(surface == NULL){
        std::cout << "Error Loading Character" << std::endl;
        return false;
    }
    texcharacter = NULL;
    texcharacter = SDL_CreateTextureFromSurface(rend, surface);
    if(!texcharacter){
        return false;
    }
    return true;
}


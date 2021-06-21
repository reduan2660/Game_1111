// SDL and Default Libraries
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <bits/stdc++.h>

// Partial Functiolities
#include "LoadEverything.cpp"
#include "CharecterMovement.cpp"

// External Global Variables
#define  EXTERN 
#include "globalVariables.h"

// Global Variables

SDL_Rect StartScreenPos;

FILE *FILE_SAVED;

const int SCREEN_WIDTH = 1300;
const int SCREEN_HEIGHT = 700;
const int FPS = 60;

// Player Saved Information

int PLAYER_CURRENT_LEVEL;


void intializerParam()
{
    StartScreenPos.x = 0;
    StartScreenPos.y = 0;
    StartScreenPos.w = 1300;
    StartScreenPos.h = 700;

    START_GAME_BTN_LEFT_X = 390;
    START_GAME_BTN_LEFT_Y = 470;
    START_GAME_BTN_RIGHT_X = 970;
    START_GAME_BTN_RIGHT_Y = 630;

    backgroundPos.x = 0;
    backgroundPos.y = 0;
    backgroundPos.w = 6800;
    backgroundPos.h = 700;

    backgroundAnchor.x = 0;
    backgroundAnchor.y = 0;
    backgroundAnchor.w = 6800;
    backgroundAnchor.h = 700;


    charecterPos.x = 200;
	charecterPos.y = 215;
	charecterPos.w = 150;
	charecterPos.h = 100;
    CHARACTER_MOVEMENT_STEP_X = 24;
    CHARACTER_MOVEMENT_STEP_Y = 24;
}

bool init(){
    // SDL Initialize
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0){
        printf("Error Loading SDL\n");
        return false;
    }
    
    // Window Creation
    window = SDL_CreateWindow("Game.exe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(window == NULL){
        std::cout << "Error Creating Window" << std::endl;
        return false;
    }

    // Renderer Creation on Window
    Uint32 render_flags = SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC;
    rend = SDL_CreateRenderer(window, -1, render_flags);
    if(!rend){
        std::cout << "Error Creating Renderer" << std::endl;
        return false;
    }


    // SDL Image Library Initialize
    int imgFlags = IMG_INIT_PNG;
    if(!(IMG_Init(imgFlags) & imgFlags)){
        std::cout << "Error Initializing SDL Image" << std::endl;
        return false;
    }

    // Open Files
    FILE_SAVED = fopen("./files/saved.txt","a+");
    if(FILE_SAVED == NULL){
        std::cout << "Error Initializing Saved File" << std::endl;
        return false;
    }
    else
    {
        char buffer[1000];
        fgets (buffer,1000,FILE_SAVED);

        // * TODO find better solution
        // Get Player Level 
        sscanf(buffer, "LEVEL=%d", &PLAYER_CURRENT_LEVEL);
    }   
    return true;
}

void close(){
    fclose (FILE_SAVED);
    SDL_FreeSurface(surface);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(window);
    window=NULL;
    IMG_Quit();
    SDL_Quit();
}


int main(int argc, char* arcg[])
{
   intializerParam();
   
   bool quit = false, jump = false, game_started = false;
   int stepX = 0, stepY = 0;
   SDL_Event e;
    if(init()){
        if(startScreen()){
            std::cout<<"HERE" <<std::endl;
            // Game Loop
            while(!quit){
                // * * ----------------------- Events ----------------------- 
                
                while( SDL_PollEvent( &e ) != 0 ){
                    if( e.type == SDL_QUIT )    quit = true;
                    
                        else if(e.type == SDL_KEYDOWN )
                        {
                            if(game_started){
                            // *! debug 
                            // std::cout << charecterPos.x << " " << charecterPos.y  << std::endl;
                            if (e.key.keysym.sym == SDLK_RIGHT || e.key.keysym.sym == SDLK_d){
                                characterDirection = 'r';
                                characterPositionHandle(characterDirection, jump, stepY);
                                stepX++;
                                stepX %= CHARACTER_MOVEMENT_STEP_X;
                            }
                            if (e.key.keysym.sym == SDLK_LEFT || e.key.keysym.sym == SDLK_a){
                                characterDirection = 'l';
                                characterPositionHandle(characterDirection, jump, stepY);
                                stepX++;
                                stepX %= CHARACTER_MOVEMENT_STEP_X;
                            }
                            if (e.key.keysym.sym == SDLK_SPACE){
                                jump = true;
                                characterPositionHandle(characterDirection, jump, stepY);
                                stepY++;
                                stepY %= CHARACTER_MOVEMENT_STEP_Y;
                            }
                        }
                    }
                }

            int mouseX, mouseY;
            int mouseButtons = SDL_GetMouseState(&mouseX, &mouseY);
            // std::cout << mouseX << " " << mouseY << std::endl;
            if(!game_started && mouseX >= START_GAME_BTN_LEFT_X && mouseY >= START_GAME_BTN_LEFT_Y && mouseX <= START_GAME_BTN_RIGHT_X && mouseY <= START_GAME_BTN_RIGHT_Y && (mouseButtons & SDL_BUTTON(SDL_BUTTON_LEFT))){
                game_started = true;
                if(!loadGameBackground(PLAYER_CURRENT_LEVEL)) return 0;
                if(!loadCharacter()) return 0;
                // loadClue1();
                // loadBullet();
            }
            
             
            //   * * ----------------------- Calculations ----------------------- 
            
            if(stepY>0 || stepX>0){
                characterPositionHandle(characterDirection,jump, stepY);  // (direction, step)
                
                if(jump){ 
                    stepY++;
                    stepY %= CHARACTER_MOVEMENT_STEP_Y;

                    if(stepY == 0) jump = false;
                }
                stepX++;
                stepX %= CHARACTER_MOVEMENT_STEP_X;
            }


            //    * * ----------------------- Rendering ----------------------- 
            
            SDL_RenderClear(rend);
            if(!game_started) 
                SDL_RenderCopy(rend, texStartScreen, NULL, &StartScreenPos);
            else{ 
                SDL_RenderCopy(rend, texBackground, &backgroundAnchor, &backgroundPos);
                SDL_RenderCopy(rend, texCharecter, NULL, &charecterPos);
            }
            SDL_RenderPresent(rend);
            SDL_Delay(1000/FPS);
            }
        }
    }
    
    close();
    return 0;
}
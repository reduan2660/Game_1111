// SDL and Default Libraries
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include <bits/stdc++.h>

// Partial Functiolities
#include "CharecterMovement.cpp"

// External Global Variables
#define  EXTERN 
#include "globalVariables.h"

// Global Variables
SDL_Window* window = NULL;
SDL_Renderer* rend = NULL;
SDL_Surface* surface = NULL;
SDL_Texture* texCharecter = NULL;

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 500;
const int FPS = 60;


void intializerParam()
{
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
    return true;
}


bool startScreen()
{
    surface = IMG_Load("./files/images/me.png");
    if(surface == NULL){
        std::cout << "Error Loading Image" << std::endl;
        return false;
    }

    texCharecter = SDL_CreateTextureFromSurface(rend, surface);
    if(!texCharecter){
        return false;
    }

    return true;
}


void close(){
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
   bool quit = false, jump = false;
   int stepX = 0, stepY = 0;
   SDL_Event e;
    if(init()){
        
        if(startScreen()){
            // Game Loop
            while(!quit){
                
               
                
                // * * ----------------------- Events ----------------------- 
                
                while( SDL_PollEvent( &e ) != 0 ){
                    if( e.type == SDL_QUIT )    quit = true;
                    else if(e.type == SDL_KEYDOWN )
                    {
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

            int mouseX, mouseY;
            int mouseButtons = SDL_GetMouseState(&mouseX, &mouseY);
            
             
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
            SDL_RenderCopy(rend, texCharecter, NULL, &charecterPos);
            SDL_RenderPresent(rend);
            SDL_Delay(1000/FPS);
            }
        }
    }
    
    close();
    return 0;
}
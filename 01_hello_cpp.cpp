// Simple DirectMedia Layer

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
// #include <SDL2/SDL_mixer.h>
#include <bits/stdc++.h>


SDL_Window* window = NULL;
SDL_Renderer* rend = NULL;
SDL_Surface* surface = NULL;
SDL_Texture* tex = NULL;
SDL_Texture* texMap = NULL;
SDL_Texture* texCharecter = NULL;
SDL_Texture*  texClue = NULL;
SDL_Texture*  texTresure = NULL;
SDL_Texture*  texBullet = NULL;



struct Bullets {
    char direction;
    int initX;
    int initY;
    SDL_Rect bulletPosition;
};

SDL_Rect startScreenPos, mapPos, charecterPos, cluePos, tresurePos;

const int SCREEN_WIDTH = 1360;
const int SCREEN_HEIGHT = 760;
const int FPS = 60;

const int BULLET_WIDTH = 20;
const int BULLET_HEIGHT = 20;
char mapMask[382][682];

void intializerParam()
{
    startScreenPos.x = 500;
    startScreenPos.y = 300;
    startScreenPos.w = 200;
    startScreenPos.h = 75;

    mapPos.x = 0;
    mapPos.y = 0;
    mapPos.h = SCREEN_HEIGHT;
    mapPos.w = SCREEN_WIDTH;

    charecterPos.x = 200;
	charecterPos.y = 615;
	charecterPos.w = 35;
	charecterPos.h = 35;

    cluePos.x = SCREEN_WIDTH/2 - 150;
    cluePos.y = SCREEN_HEIGHT/2 - 150;
    cluePos.h = 100;
    cluePos.w = 300;

    tresurePos.x = 1250;
    tresurePos.y = 441;
    tresurePos.h = 50;
    tresurePos.w = 50;
}

bool init(){
        
    // SDL Initialize
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
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

    SDL_RWops* file = SDL_RWFromFile("./images/mapMask.txt","r" );
    if( file == NULL ){
        printf( "Warning: Unable to open file! SDL Error: %s\n", SDL_GetError() );
        return false;
    }
    for( int i = 0; i < 380; ++i )
    {
        SDL_RWread(file, &mapMask[i], sizeof(char), 681);
    }
    SDL_RWclose( file );
    
    return true;
}


bool startScreen()
{
    surface = IMG_Load("./images/StartGame.png");
    if(surface == NULL){
        std::cout << "Error Loading Image" << std::endl;
        return false;
    }

    tex = SDL_CreateTextureFromSurface(rend, surface);
    if(!tex){
        // cout << "Error Texture" <<endl;
        return false;
    }

    return true;
}

bool loadCharecter(char direction){
    if(direction == 'r')    surface = IMG_Load("./images/charecter.png");
    if(direction == 'l')    surface = IMG_Load("./images/charecterLeft.png");
    texCharecter = SDL_CreateTextureFromSurface(rend, surface);
    if(!texCharecter){
 		printf("Error Loading Texture");
		return false;
 	}
    return true;
}
bool loadGameScreen(){
    surface = NULL;

    surface = IMG_Load("./images/map.png");
    texMap = SDL_CreateTextureFromSurface(rend, surface);
    if(!texMap){
        printf("Error Loading Texture");
        return false;
    }
    loadCharecter('r');
    return true;
    

}



bool loadClue1(){
    surface = NULL;

    surface = IMG_Load("./images/clue1.png");
    texClue = SDL_CreateTextureFromSurface(rend, surface);
    if(!texClue){
        printf("Error Loading Clue 1 Texture");
        return false;
    }
     return true;
}


bool loadClue2(){
    surface = NULL;

    surface = IMG_Load("./images/clue2.png");
    texClue = SDL_CreateTextureFromSurface(rend, surface);
    if(!texClue){
        printf("Error Loading Clue 1 Texture");
        return false;
    }
     return true;

}

bool loadGameOver(){
    surface = NULL;

    surface = IMG_Load("./images/gameover.png");
    texClue = SDL_CreateTextureFromSurface(rend, surface);
    if(!texClue){
        printf("Error Loading Tresure Texture");
        return false;
    }
     return true;

}

bool loadTreasure(){
    surface = NULL;

    surface = IMG_Load("./images/tresure.png");
    texTresure = SDL_CreateTextureFromSurface(rend, surface);
    if(!texTresure){
        printf("Error Loading Tresure Texture");
        return false;
    }
     return true;

}

bool loadBullet(){
    surface = NULL;

    surface = IMG_Load("./images/bullet.png");
    texBullet = SDL_CreateTextureFromSurface(rend, surface);
    if(!texBullet){
        printf("Error Loading Bullet Texture");
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
    struct Bullets bullet[100];
    int bulletFired = 0;
    char charecterDirection = 'r';
   intializerParam();

   bool quit = false, game_Started = false;
   SDL_Event e;


    if(init()){
        
        if(startScreen()){
            // Game Loop
            while(!quit){
                while( SDL_PollEvent( &e ) != 0 ){
                    if( e.type == SDL_QUIT )    quit = true;
                    else if( e.type == SDL_KEYDOWN )
                    {
                        int mapMaskPosX = ((charecterPos.x)/2);
                        int mapMaskPosY = ((charecterPos.y)/2) + 18;
                        // std::cout << charecterPos.x << " " << charecterPos.y  << std::endl;
                        if (e.key.keysym.sym == SDLK_RIGHT){
                            if(charecterDirection == 'l') loadCharecter('r');
                            charecterDirection = 'r';
                            if(game_Started) if(charecterPos.x < (SCREEN_WIDTH-charecterPos.w) ) if(mapMask[mapMaskPosY][mapMaskPosX + 3]  == '0') charecterPos.x += 6;
                            break;
                        }

                        if (e.key.keysym.sym == SDLK_LEFT){
                            if(charecterDirection == 'r') loadCharecter('l');
                            charecterDirection = 'l';
                            if(game_Started && charecterPos.x > 0 && mapMask[mapMaskPosY][mapMaskPosX - 3]  == '0')  charecterPos.x -= 6;
                            break;
                        }

                        if (e.key.keysym.sym == SDLK_UP){
                            if(game_Started) if(charecterPos.y > 0 ) if(mapMask[mapMaskPosY - 3][mapMaskPosX]  == '0')  charecterPos.y -= 6;
                            break;
                        }

                        if (e.key.keysym.sym == SDLK_DOWN){
                            if(game_Started) if(charecterPos.y < (SCREEN_HEIGHT-charecterPos.h)) if(mapMask[mapMaskPosY + 3][mapMaskPosX]  == '0') charecterPos.y += 6;
                            break;
                        }
                    }
                }

            int mouseX, mouseY;
            int mouseButtons = SDL_GetMouseState(&mouseX, &mouseY);
            if(!game_Started && mouseX >= startScreenPos.x && mouseY >= startScreenPos.y && (mouseButtons & SDL_BUTTON(SDL_BUTTON_LEFT))){
                game_Started = true;
                loadGameScreen();
                loadClue1();
                loadBullet();
            }else{
                // Game Started
                if (mouseButtons & SDL_BUTTON(SDL_BUTTON_LEFT)){
                    bulletFired++;
                    bullet[bulletFired-1].direction = charecterDirection;
                    
                    SDL_Rect bulletPos;
                    bulletPos.x = charecterPos.x+10;
                    bulletPos.y = charecterPos.y;
                    bulletPos.w = BULLET_WIDTH;
                    bulletPos.h = BULLET_HEIGHT;
                    bullet[bulletFired-1].bulletPosition = bulletPos;
                    bullet[bulletFired-1].initX = charecterPos.x;
                    bullet[bulletFired-1].initY = charecterPos.y;

                }
            }
            SDL_RenderClear(rend);
            if(!game_Started)  SDL_RenderCopy(rend, tex, NULL, &startScreenPos);
            else {
                SDL_RenderCopy(rend, texMap, NULL, &mapPos);
                SDL_RenderCopy(rend, texCharecter, NULL, &charecterPos);
                // Show Clue 1
                if(charecterPos.x < 210 && charecterPos.x > 190 && charecterPos.x < 625 && charecterPos.y > 605 ){
                    SDL_RenderCopy(rend, texClue, NULL, &cluePos);
                }
                if(charecterPos.x < 618 && charecterPos.x > 598 && charecterPos.y < 121 && charecterPos.y > 101 ){
                    loadClue2();
                    SDL_RenderCopy(rend, texClue, NULL, &cluePos);
                    loadTreasure();
                    SDL_RenderCopy(rend, texTresure, NULL, &tresurePos);
                    
                }
                if(charecterPos.x < 1260 && charecterPos.x > 1240 && charecterPos.y < 450 && charecterPos.y > 430 ){
                    
                    loadGameOver();
                    SDL_RenderCopy(rend, texClue, NULL, &cluePos);
                }

                // Bullet
                for(int bulIndex = 0; bulIndex< bulletFired; bulIndex++){
                    if(bullet[bulIndex].bulletPosition.x < SCREEN_WIDTH && bullet[bulIndex].bulletPosition.x > 0 ){
                        if(bullet[bulIndex].direction == 'l') bullet[bulIndex].bulletPosition.x -= 20;
                        if(bullet[bulIndex].direction == 'r') bullet[bulIndex].bulletPosition.x += 20;
                        SDL_Rect BulPos = bullet[bulIndex].bulletPosition;
                        SDL_RenderCopy(rend, texBullet, NULL, &BulPos);
                    }
                }
            }
            SDL_RenderPresent(rend);
            SDL_Delay(1000/FPS);
            }
        }
    }
    
    close();
    return 0;
}
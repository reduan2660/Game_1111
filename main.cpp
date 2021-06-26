// SDL and Default Libraries
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include <bits/stdc++.h>

// Partial Functiolities
#include "LoadEverything.cpp"
#include "CharecterMovement.cpp"

// External Global Variables
#define  EXTERN 
#include "globalVariables.h"


// Global Variables

SDL_Rect StartScreenPos;
const int BULLET_WIDTH = 60;
const int BULLET_HEIGHT = 30;

FILE *FILE_SAVED;
const int FPS = 60;
// Player Saved Information
int PLAYER_CURRENT_LEVEL;

const int ENEMY_MOVEMENT_PIXEL = 2;
struct EnemyAliveState EnemyState;
struct ExplosiveEnemy ExplosionState;

void intializerParam()
{
    SCREEN_WIDTH = 1360;
    SCREEN_HEIGHT = 760;

    TILE_X = 100;
    TILE_Y = SCREEN_HEIGHT/17;

    StartScreenPos.x = 0;
    StartScreenPos.y = 0;
    StartScreenPos.w = 1360;
    StartScreenPos.h = 760;

    NEW_GAME_BTN_LEFT_X = 440;
    NEW_GAME_BTN_LEFT_Y = 460;
    NEW_GAME_BTN_RIGHT_X = 980;
    NEW_GAME_BTN_RIGHT_Y = 550;

    RESUME_GAME_BTN_LEFT_X = 440;
    RESUME_GAME_BTN_LEFT_Y = 380;
    RESUME_GAME_BTN_RIGHT_X = 980;
    RESUME_GAME_BTN_RIGHT_Y = 450;

    EXIT_GAME_BTN_LEFT_X = 440;
    EXIT_GAME_BTN_LEFT_Y = 560;
    EXIT_GAME_BTN_RIGHT_X = 980;
    EXIT_GAME_BTN_RIGHT_Y = 620;
    
    GameOverPos.x = 0;
    GameOverPos.y = 0;
    GameOverPos.w = 1360;
    GameOverPos.h = 760;

    backgroundPos.x = 0;
    backgroundPos.y = 0;
    backgroundPos.w = 6800;
    backgroundPos.h = 760;

    backgroundAnchor.x = 0;
    backgroundAnchor.y = 0;
    backgroundAnchor.w = 6800;
    backgroundAnchor.h = 760;
    
    pathwayPos.x = 0;
    pathwayPos.y = 0;
    pathwayPos.w = 6800;
    pathwayPos.h = 760;

    pathwayAnchor.x = 0;
    pathwayAnchor.y = 0;
    pathwayAnchor.w = 6800;
    pathwayAnchor.h = 760;

	characterPos.w = 150*2;
	characterPos.h = 116.5*2;
    characterPos.x = 20;
	characterPos.y = 0 ;

    CHARACTER_MOVEMENT_STEP_X = 9;
    CHARACTER_MOVEMENT_STEP_Y = 24;

    bullet_fired_character_cur_frame = 0;
    BULLET_FIRED_CHARACTER_FRAME = 9;
    characterDirection = 'r';
    
    for(int i =0;i<ENEMY_1_snail;i++){
        EnemyState.snail[i] = true;
    }
    for(int i =0;i<ENEMY_2_bomb;i++){
        EnemyState.bomb[i] = true;
    }
    for(int i =0;i<ENEMY_3_bird;i++){
        EnemyState.bird[i] = true;
    }
}

bool findEnemyLocation(int CURRENT_FRAME ,int ENEMY_POSITION_STEP){
    int indexBird = 0, indexBomb = 0, indexSnail = 0;
    for(int i = 0;i<17;i++){
        for(int j = 0; j<68;j++){
            if(mapMatrix[i][j] == '6'){
                birdPos[indexBird].x =( j*TILE_X )- (6800 -  pathwayPos.w);
                birdPos[indexBird].y =( i*TILE_Y)- birdPos[indexBird].h;
                birdPos[indexBird].w = 800/3;
                birdPos[indexBird].h = 600/3;
                indexBird++;
            }
            else if(mapMatrix[i][j] == '7'){
                bombPos[indexBomb].w = 800/3;
                bombPos[indexBomb].h = 600/3;
                bombPos[indexBomb].x = ( j*TILE_X )- (6800 -  pathwayPos.w);
                bombPos[indexBomb].y = i*TILE_Y - bombPos[indexBomb].h;
                indexBomb++;
            }
            else if(mapMatrix[i][j] == '5'){
                snailPos[indexSnail].w = 800/4;
                snailPos[indexSnail].h = 600/4;
                snailPos[indexSnail].x = ( j*TILE_X )- (6800 -  pathwayPos.w);
                snailPos[indexSnail].y = i*TILE_Y - snailPos[indexSnail].h;
                // std::cout << i << " " << j << " " <<snailPos[indexSnail].x << " " << snailPos[indexSnail].y << std::endl;
                indexSnail++;
            }
        }
    }
    switch (ENEMY_POSITION_STEP)
        {
        case 0:
            for(int i=0; i<ENEMY_3_bird; i++){
                birdPos[i].x += ENEMY_MOVEMENT_PIXEL*CURRENT_FRAME;
            }
            for(int i=0; i<ENEMY_2_bomb; i++){
                bombPos[i].x += ENEMY_MOVEMENT_PIXEL*CURRENT_FRAME;
            }
            for(int i=0; i<ENEMY_1_snail; i++){
                snailPos[i].x += ENEMY_MOVEMENT_PIXEL*CURRENT_FRAME;
            }
        break;
        case 3:
            for(int i=0; i<ENEMY_3_bird; i++){
                birdPos[i].x = birdPos[i].x + ENEMY_MOVEMENT_PIXEL*(CURRENT_FRAME) - 60*ENEMY_MOVEMENT_PIXEL;
            }
            for(int i=0; i<ENEMY_2_bomb; i++){
                bombPos[i].x = bombPos[i].x + ENEMY_MOVEMENT_PIXEL*(CURRENT_FRAME) - 60*ENEMY_MOVEMENT_PIXEL;
            }
            for(int i=0; i<ENEMY_1_snail; i++){
                snailPos[i].x = snailPos[i].x + ENEMY_MOVEMENT_PIXEL*(CURRENT_FRAME) - 60*ENEMY_MOVEMENT_PIXEL;
            }
            break;
        case 1:
            for(int i=0; i<ENEMY_2_bomb; i++){
                bombPos[i].x = bombPos[i].x - ENEMY_MOVEMENT_PIXEL*(CURRENT_FRAME) + 60*ENEMY_MOVEMENT_PIXEL;
            }
            for(int i=0; i<ENEMY_3_bird; i++){
                birdPos[i].x = birdPos[i].x - ENEMY_MOVEMENT_PIXEL*(CURRENT_FRAME) + 60*ENEMY_MOVEMENT_PIXEL;
            }
            for(int i=0; i<ENEMY_1_snail; i++){
                snailPos[i].x = snailPos[i].x - ENEMY_MOVEMENT_PIXEL*(CURRENT_FRAME) + 60*ENEMY_MOVEMENT_PIXEL;
            }

            break;
        case 2:
            for(int i=0; i<ENEMY_2_bomb; i++){
                bombPos[i].x -=  ENEMY_MOVEMENT_PIXEL*(CURRENT_FRAME/2);
            }
            for(int i=0; i<ENEMY_3_bird; i++){
                birdPos[i].x -=  ENEMY_MOVEMENT_PIXEL*CURRENT_FRAME;
            }
            for(int i=0; i<ENEMY_1_snail; i++){
                snailPos[i].x -=  ENEMY_MOVEMENT_PIXEL*CURRENT_FRAME;
            }
        break;

    default:
        break;
    }
    return true;
}

bool init_level(){
    loadMatrix(PLAYER_CURRENT_LEVEL);
    if(!loadSound(PLAYER_CURRENT_LEVEL)) return false;
    if(!loadGameBackground(PLAYER_CURRENT_LEVEL)) return 0;
    if(!loadGamePathway(PLAYER_CURRENT_LEVEL)) return 0;
    if(!loadCharacter()) return 0;
    if(!loadEnemy(PLAYER_CURRENT_LEVEL)) return 0;
    if(!loadBullet()) return 0;
    return true;
}

bool init(){
    // ? SDL Initialize
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0){
        printf("Error Loading SDL\n");
        return false;
    }
    
    // ? Window Creation
    window = SDL_CreateWindow("Game.exe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(window == NULL){
        std::cout << "Error Creating Window" << std::endl;
        return false;
    }

    // ? Renderer Creation on Window
    Uint32 render_flags = SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC;
    rend = SDL_CreateRenderer(window, -1, render_flags);
    if(!rend){
        std::cout << "Error Creating Renderer" << std::endl;
        return false;
    }

    // ? SDL Image Library Initialize
    int imgFlags = IMG_INIT_PNG;
    if(!(IMG_Init(imgFlags) & imgFlags)){
        std::cout << "Error Initializing SDL Image" << std::endl;
        return false;
    }
    // ? Initialize SDL_mixer
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error:\n");
        return false;
    }


    // Open Files

    // Saved File
    FILE_SAVED = fopen("./files/saved.txt","a+");
    if(FILE_SAVED == NULL){
        std::cout << "Error Initializing Saved File" << std::endl;
        return false;
    }
    else
    {
        char buffer[1000];
        // ? Read From File
        fgets (buffer,1000,FILE_SAVED);
        // ? Get Player Level
        sscanf(buffer, "LEVEL=%d", &PLAYER_CURRENT_LEVEL);
    }   
    
    if(!init_level()) return false;
    return true;
}

void saveLevel(){
    FILE_SAVED = fopen("./files/saved.txt","w+");
    fprintf(FILE_SAVED, "LEVEL=%d\n", PLAYER_CURRENT_LEVEL);
}

void close(){
    //Free the sound effects
    Mix_FreeChunk( sBulletFired );
    sBulletFired = NULL;
    Mix_FreeChunk( sEnemyDied );
    sBulletFired = NULL;
    Mix_FreeChunk( sJump );
    sJump = NULL;
    // //Free the music
    Mix_FreeMusic( background_music );
    background_music = NULL;
    fclose(FILE_SAVED);
    SDL_FreeSurface(surface);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(window);
    window=NULL;
    IMG_Quit();
    SDL_Quit();
}


int main(int argc, char* arcg[])
{
   
   struct Bullets bullet[1000];
   intializerParam();
   bool quit = false, jump = false, game_started = false, game_over=false, game_won = false;
   int stepX = 0, stepY = 0, ENEMY_STEP = 0, ENEMY_FRAME = 6, CURRENT_FRAME=0, ENEMY_POSITION_STEP =0, bulletFired = 0;
   SDL_Event e;
    if(init()){
        if(startScreen()){
            // findEnemyLocation();
            // Game Loop
            if(Mix_PlayMusic(background_music, -1)==-1) {
                printf("Mix_PlayMusic: %s\n", Mix_GetError());
            // well, there's no music, but most games don't break without music...
            }
            while(!quit){
                CURRENT_FRAME++;
                CURRENT_FRAME %= FPS;
                // * * ----------------------- Events ----------------------- 
                int matrixIndex_X = ((characterPos.y + characterPos.h) )/(760/17);
                int matrixIndex_Y = (characterPos.x + (characterPos.w)/2 + (6800 - pathwayPos.w))/100;
                // std::cout << matrixIndex_X << " " << matrixIndex_Y <<" " << mapMatrix[matrixIndex_X][matrixIndex_Y] <<std::endl;
                while( SDL_PollEvent( &e ) != 0 ){
                    if( e.type == SDL_QUIT )    quit = true;
                        else if(e.type == SDL_KEYDOWN )
                        {
                            if(game_started){
                                // std::cout << characterPos.x << " " << characterPos.y  << std::endl;
                                if (e.key.keysym.sym == SDLK_RIGHT || e.key.keysym.sym == SDLK_d){
                                    characterDirection = 'r';
                                    characterPositionHandle(characterDirection, jump, stepY, stepX);
                                    if(!jump) stepY = 0;
                                    stepX++;
                                    stepX %= CHARACTER_MOVEMENT_STEP_X;
                                }
                                if (e.key.keysym.sym == SDLK_LEFT || e.key.keysym.sym == SDLK_a){
                                    characterDirection = 'l';
                                    characterPositionHandle(characterDirection, jump, stepY, stepX);
                                    if(!jump) stepY = 0;
                                    stepX++;
                                    stepX %= CHARACTER_MOVEMENT_STEP_X;
                                }
                                if (e.key.keysym.sym == SDLK_UP || e.key.keysym.sym == SDLK_w){
                                    if(mapMatrix[matrixIndex_X][matrixIndex_Y]  == 'u' || mapMatrix[matrixIndex_X][matrixIndex_Y]  == '4'){
                                        characterDirection = 'u';
                                        characterPositionHandle(characterDirection, jump, stepY, stepX);
                                        
                                        stepY++;
                                        stepY %= CHARACTER_MOVEMENT_STEP_Y;
                                    }
                                }
                                if (e.key.keysym.sym == SDLK_DOWN || e.key.keysym.sym == SDLK_s){
                                    if(mapMatrix[matrixIndex_X][matrixIndex_Y]  == 'd' || mapMatrix[matrixIndex_X][matrixIndex_Y]  == '4'){
                                        characterDirection = 'd';
                                        characterPositionHandle(characterDirection, jump, stepY, stepX);
                                        
                                        stepY++;
                                        stepY %= CHARACTER_MOVEMENT_STEP_Y;
                                    }
                                }
                                if (e.key.keysym.sym == SDLK_SPACE){
                                    Mix_PlayChannel( -1, sJump, 0 );
                                    jump = true;
                                    characterPositionHandle(characterDirection, jump, stepY, stepX);
                                    stepY++;
                                    stepY %= CHARACTER_MOVEMENT_STEP_Y;
                                }
                            }
                            else{
                                if (e.key.keysym.sym == SDLK_SPACE){
                                    game_started = true;
                                    intializerParam();
                                    
                                }
                            }
                        }
                    }

                int mouseX, mouseY;
                int mouseButtons = SDL_GetMouseState(&mouseX, &mouseY);
                // std::cout << stepX << " " << stepY << std::endl;
                // ? Game Start Screen Functionality
                if(game_won){
                    // ? New Game
                    if(mouseX >= NEW_GAME_BTN_LEFT_X && mouseY >= NEW_GAME_BTN_LEFT_Y && mouseX <= NEW_GAME_BTN_RIGHT_X && mouseY <= NEW_GAME_BTN_RIGHT_Y && (mouseButtons & SDL_BUTTON(SDL_BUTTON_LEFT))){
                        game_started = true;
                        game_over = false;
                        PLAYER_CURRENT_LEVEL = 1;
                        saveLevel();
                        init_level();
                        intializerParam();
                    }
                    // ? Quit
                    if(mouseX >= EXIT_GAME_BTN_LEFT_X && mouseY >= EXIT_GAME_BTN_LEFT_Y && mouseX <= EXIT_GAME_BTN_RIGHT_X && mouseY <= EXIT_GAME_BTN_RIGHT_Y && (mouseButtons & SDL_BUTTON(SDL_BUTTON_LEFT))){
                        quit = true;
                    }
                }
                else if(game_over){
                    // ? Resume
                    if(mouseX >= RESUME_GAME_BTN_LEFT_X && mouseY >= RESUME_GAME_BTN_LEFT_Y && mouseX <= RESUME_GAME_BTN_RIGHT_X && mouseY <= RESUME_GAME_BTN_RIGHT_Y && (mouseButtons & SDL_BUTTON(SDL_BUTTON_LEFT))){
                        game_started = true;
                        game_over = false;
                        intializerParam();
                    }
                    // ? New Game
                    if(mouseX >= NEW_GAME_BTN_LEFT_X && mouseY >= NEW_GAME_BTN_LEFT_Y && mouseX <= NEW_GAME_BTN_RIGHT_X && mouseY <= NEW_GAME_BTN_RIGHT_Y && (mouseButtons & SDL_BUTTON(SDL_BUTTON_LEFT))){
                        game_started = true;
                        game_over = false;
                        PLAYER_CURRENT_LEVEL = 1;
                        saveLevel();
                        init_level();
                        intializerParam();
                    }
                    // ? Quit
                    if(mouseX >= EXIT_GAME_BTN_LEFT_X && mouseY >= EXIT_GAME_BTN_LEFT_Y && mouseX <= EXIT_GAME_BTN_RIGHT_X && mouseY <= EXIT_GAME_BTN_RIGHT_Y && (mouseButtons & SDL_BUTTON(SDL_BUTTON_LEFT))){
                        quit = true;
                    }
                }
                else if(!game_started  && (mouseButtons & SDL_BUTTON(SDL_BUTTON_LEFT))){
                    
                     // ? Resume
                    if(mouseX >= RESUME_GAME_BTN_LEFT_X && mouseY >= RESUME_GAME_BTN_LEFT_Y && mouseX <= RESUME_GAME_BTN_RIGHT_X && mouseY <= RESUME_GAME_BTN_RIGHT_Y && (mouseButtons & SDL_BUTTON(SDL_BUTTON_LEFT))){
                        game_started = true;
                        intializerParam();
                    }
                    // ? New Game
                    if(mouseX >= NEW_GAME_BTN_LEFT_X && mouseY >= NEW_GAME_BTN_LEFT_Y && mouseX <= NEW_GAME_BTN_RIGHT_X && mouseY <= NEW_GAME_BTN_RIGHT_Y && (mouseButtons & SDL_BUTTON(SDL_BUTTON_LEFT))){
                        game_started = true;
                        PLAYER_CURRENT_LEVEL = 1;
                        saveLevel();
                        init_level();
                        intializerParam();
                    }
                    // ? Quit
                    if(mouseX >= EXIT_GAME_BTN_LEFT_X && mouseY >= EXIT_GAME_BTN_LEFT_Y && mouseX <= EXIT_GAME_BTN_RIGHT_X && mouseY <= EXIT_GAME_BTN_RIGHT_Y && (mouseButtons & SDL_BUTTON(SDL_BUTTON_LEFT))){
                        quit = true;
                    }

                    
                    
                }
                // ? Game Stareted
                else if(game_started && (CURRENT_FRAME%4 == 0) && (mouseButtons & SDL_BUTTON(SDL_BUTTON_LEFT))){
                        // ? Bullet Fired -----------------------
                        Mix_PlayChannel( -1, sBulletFired, 0 );
                        SDL_Rect bulletPos;
                        bullet_fired_character_cur_frame++;
                        bullet_fired_character_cur_frame %= BULLET_FIRED_CHARACTER_FRAME;
                        bulletPos.w = BULLET_WIDTH;
                        bulletPos.h = BULLET_HEIGHT;
                        if(characterDirection == 'r' || characterDirection == 'u' || characterDirection == 'd'){
                            bulletPos.x = characterPos.x+10+characterPos.w;
                            bulletPos.y = characterPos.y+80;
                            bullet[bulletFired].direction = 'r';
                        }
                        else if(characterDirection == 'l'){
                            bulletPos.x = characterPos.x-10;
                            bulletPos.y = characterPos.y+40;
                            bullet[bulletFired].direction = characterDirection;
                        }
                        
                        bullet[bulletFired].bulletPosition = bulletPos;
                        bullet[bulletFired].initX = bulletPos.x;
                        bullet[bulletFired].initY = bulletPos.y;
                        bullet[bulletFired].active = true;

                        bulletFired++;
                }
                
                //   * * ----------------------- Calculations ----------------------- 
                // if(CURRENT_FRAME%30 == 0)std::cout << PLAYER_CURRENT_LEVEL << std::endl;
                // ? Level Succesful
                if(mapMatrix[matrixIndex_X][matrixIndex_Y] == '8'){
                    PLAYER_CURRENT_LEVEL++;
                    if(PLAYER_CURRENT_LEVEL == 4){
                        game_won = true;
                        PLAYER_CURRENT_LEVEL = 1;
                    }
                    else{
                        saveLevel();
                        intializerParam();
                        init_level();
                    }
                    continue;
                }
                // ? Character Movement
                // ? Jump or Game Over        
                if(stepY > 0){
                    if(stepY> CHARACTER_MOVEMENT_STEP_Y/2  &&jump && mapMatrix[matrixIndex_X][matrixIndex_Y] == '1'){
                        stepY = 0;
                        jump = false;
                    }
                    else{
                        characterPositionHandle(characterDirection,jump, stepY, stepX);  // (direction, step)
                        if(jump || characterDirection == 'u' || characterDirection == 'd'){ 
                            stepY++;
                            stepY %= CHARACTER_MOVEMENT_STEP_Y;
                            if(stepY == 0) jump = false;
                        }
                    }
                }
                // ? Gravity
                else if(mapMatrix[matrixIndex_X][matrixIndex_Y] == '0'){
                    gravity();
                }
                // ? Game Over
                else if( (mapMatrix[matrixIndex_X][matrixIndex_Y] == '9')){
                    // ? Game Over
                    // std::cout<<"Fell Into Lava" << std::endl;
                    game_over = true;
                    game_started = false;
                }

                // ? Moving Left and Right
                if(stepX > 0){
                    characterPositionHandle(characterDirection, jump, stepY, stepX);  // (direction, step)
                    stepX++;
                    stepX %= CHARACTER_MOVEMENT_STEP_X;
                }
                
                // ? Enemy Movement
                findEnemyLocation(CURRENT_FRAME,ENEMY_POSITION_STEP);
                if(CURRENT_FRAME == 59){
                    ENEMY_POSITION_STEP++;
                    ENEMY_POSITION_STEP %= 4;
                }
                if(CURRENT_FRAME % 6 ==0){
                    // ? Enemy Right
                    if(ENEMY_POSITION_STEP == 0 || ENEMY_POSITION_STEP == 3){
                        texBird = texBird_L[ENEMY_STEP];
                        ENEMY_STEP+=1;
                        ENEMY_STEP %= ENEMY_FRAME;

                        texBomb = texBomb_R[ENEMY_STEP];
                        ENEMY_STEP+=1;
                        ENEMY_STEP %= ENEMY_FRAME;

                        texSnail = texSnail_R[ENEMY_STEP];
                        ENEMY_STEP+=1;
                        ENEMY_STEP %= ENEMY_FRAME; 
                    }
                    // ? Enemy Left
                    else if(ENEMY_POSITION_STEP == 1 || ENEMY_POSITION_STEP == 2){
                        texBird = texBird_R[ENEMY_STEP];
                        ENEMY_STEP+=1;
                        ENEMY_STEP %= ENEMY_FRAME;

                        texBomb = texBomb_L[ENEMY_STEP];
                        ENEMY_STEP+=1;
                        ENEMY_STEP %= ENEMY_FRAME;

                        texSnail = texSnail_L[ENEMY_STEP];
                        ENEMY_STEP+=1;
                        ENEMY_STEP %= ENEMY_FRAME; 
                    }
                }

                // ? Bullet Collision && Propagation
                    for(int bulIndex = 0; bulIndex<= bulletFired; bulIndex++){
                        if(bullet[bulIndex].bulletPosition.x < SCREEN_WIDTH && bullet[bulIndex].bulletPosition.x > 0 ){
                            if(bullet[bulIndex].direction == 'l') bullet[bulIndex].bulletPosition.x -= 20;
                            if(bullet[bulIndex].direction == 'r') bullet[bulIndex].bulletPosition.x += 20;
                        }
                        else{
                            bullet[bulIndex].active = false;
                        }
                    }

                // ? Character Died with Enemy Contact
                // ? Check charater contacted Bomb
                for(int i=0;i<ENEMY_2_bomb;i++){
                    // std::cout << i << " " << characterPos.x + characterPos.w  << " > " << bombPos[i].x << " && " << EnemyState.bomb[i]<< std::endl;
                    if(game_started && characterPos.x + characterPos.w >= bombPos[i].x && EnemyState.bomb[i]){
                        // std::cout << "Character Died by Bommb" << std::endl;
                        game_over = true;
                        game_started = false;
                    }
                }
                
                // ? Check character contacted Snail
                for(int i=0;i<ENEMY_1_snail;i++){
                    if(game_started && characterPos.x + characterPos.w >= snailPos[i].x && EnemyState.snail[i]){
                        // std::cout << "Character Died by Snail" << std::endl;
                        game_over = true;
                        game_started = false;
                    }
                }

                // ? Check Bullet hit Enemy 
                for(int bulletIndex=0; bulletIndex<bulletFired;bulletIndex++){
                    if(bullet[bulletIndex].active == true){
                        // ? Check Bullet hit Bird
                        for(int i=0;i<ENEMY_3_bird;i++){
                            // ? Enemy Died
                            if(bullet[bulletIndex].bulletPosition.x + bullet[bulletIndex].bulletPosition.w >= birdPos[i].x && bullet[bulletIndex].bulletPosition.y > birdPos[i].y && bullet[bulletIndex].bulletPosition.y < birdPos[i].y + birdPos[i].h){
                                // std::cout << "Bird " << i << " Died by Bullet" << std::endl;
                                // texBird = texExplosion[0];
                                EnemyState.bird[i] = false;
                                Mix_Volume(4,MIX_MAX_VOLUME/2);
                                Mix_PlayChannel( 4, sEnemyDied, 0 );
                            }
                        }
                        // ? Check Bullet hit Bomb
                        for(int i=0;i<ENEMY_2_bomb;i++){
                            if(bullet[bulletIndex].bulletPosition.x + bullet[bulletIndex].bulletPosition.w >= bombPos[i].x && bullet[bulletIndex].bulletPosition.y > bombPos[i].y && bullet[bulletIndex].bulletPosition.y < bombPos[i].y + bombPos[i].h){
                                // std::cout << "Bomb " << i << " Died by Bullet" << std::endl;
                                // texBomb = texExplosion[0];
                                EnemyState.bomb[i] = false;
                                Mix_Volume(4,MIX_MAX_VOLUME/2);
                                Mix_PlayChannel( 4, sEnemyDied, 0 );
                            }
                        }
                        // ? Check Bullet hit Snail
                        for(int i=0;i<ENEMY_1_snail;i++){
                            if(bullet[bulletIndex].bulletPosition.x + bullet[bulletIndex].bulletPosition.w >= snailPos[i].x && bullet[bulletIndex].bulletPosition.y > snailPos[i].y ){
                                // std::cout << "Snail " << i<<   " Died by Bullet" << std::endl;
                                // texSnail = texExplosion[0];
                                EnemyState.snail[i] = false;
                                Mix_Volume(4,MIX_MAX_VOLUME/2);
                                Mix_PlayChannel( 4, sEnemyDied, 0 );
                                
                            }
                        }
                                
                    }
                }
                
                // ? Check Explosion
                // ! Not Working
                // if(CURRENT_FRAME %6 == 0){
                //     for(int i=0;i<6;i++){
                //         if(ExplosionState.snail[i]){
                //             ExplosionState.snailFrame[i]++;
                //             if (ExplosionState.snailFrame[i] == 6){
                //                 EnemyState.snail[i] = false;
                //             }
                //             texSnail = texExplosion[i];
                //         }
                //     }
                // }


                // ? Bullet Fired Character Animation
                if(bullet_fired_character_cur_frame > 0){
                    if (characterDirection == 'r')  texcharacter = texShooting_R[stepX];
                    if (characterDirection == 'l')  texcharacter = texShooting_L[stepX];
                    stepX++;
                    bullet_fired_character_cur_frame++;
                    bullet_fired_character_cur_frame %= BULLET_FIRED_CHARACTER_FRAME;
                }
                
                // ? Enemey Died Animation
                
                
                //    * * ----------------------- Rendering ----------------------- 

                SDL_RenderClear(rend);
                if(game_won){
                    SDL_RenderCopy(rend, texGameWon, NULL, &GameOverPos);
                }
                else if(game_over){
                    SDL_RenderCopy(rend, texGameOver, NULL, &GameOverPos);
                }
                else if(!game_started) 
                    SDL_RenderCopy(rend, texStartScreen, NULL, &StartScreenPos);
                else{
                    
                    SDL_RenderCopy(rend, texBackground, &backgroundAnchor, &backgroundPos);
                    SDL_RenderCopy(rend, texPathway, &pathwayAnchor, &pathwayPos);
                    
                    // Enemy
                    for(int i=0;i<ENEMY_2_bomb;i++){
                        if(EnemyState.bomb[i]) SDL_RenderCopy(rend, texBomb, NULL, &bombPos[i]);
                    }
                    for(int i=0;i<ENEMY_3_bird;i++){
                        if(EnemyState.bird[i]) SDL_RenderCopy(rend, texBird, NULL, &birdPos[i]);
                    }
                    for(int i=0;i<ENEMY_1_snail;i++){
                        if(EnemyState.snail[i]) SDL_RenderCopy(rend, texSnail, NULL, &snailPos[i]);
                    }
                    
                    // Bullet
                    for(int bulIndex = 0; bulIndex<= bulletFired; bulIndex++){
                        if(bullet[bulIndex].bulletPosition.x < SCREEN_WIDTH && bullet[bulIndex].bulletPosition.x > 0 ){
                            SDL_RenderCopy(rend, texBullet, NULL, &bullet[bulIndex].bulletPosition);
                        }
                    }
                    SDL_RenderCopy(rend, texcharacter, NULL, &characterPos);
                }
                SDL_RenderPresent(rend);
                SDL_Delay(1000/FPS);
            }
        }
    }
    
    close();
    return 0;
}
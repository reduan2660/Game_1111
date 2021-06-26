

#include "globalVariables.h"
#include "CharecterMovement.h"
#include <bits/stdc++.h>

const int PIXELS_TO_MOVE_EACH_FRAME = 1;
const int JUMP_COEFFICIENT = 4;
const int LADDER_COEFFICIENT = 1;

const int BG_MOVE_COEFFICIENT = 2;
const int PATHWAY_MOVE_COEFFICIENT = 3;
const int JUMP_MOVE_COEFFICIENT = 5;
// const int ENEMY_MOVEMENT_PIXEL = 2;


bool characterPositionHandle(char direction, bool jump, int stepY, int stepX){
    


    if(!jump){
        switch (direction)
        {
        
        case 'r':
            
            
                texcharacter = texcharacter_R[stepX];
                if(characterPos.x < SCREEN_WIDTH/2 - characterPos.w){
                    characterPos.x += PIXELS_TO_MOVE_EACH_FRAME * PATHWAY_MOVE_COEFFICIENT;
                }
                else if(pathwayAnchor.x + PIXELS_TO_MOVE_EACH_FRAME * PATHWAY_MOVE_COEFFICIENT < (5500)){
                    backgroundAnchor.x += PIXELS_TO_MOVE_EACH_FRAME * BG_MOVE_COEFFICIENT; // move the texture
                    backgroundPos.w -= PIXELS_TO_MOVE_EACH_FRAME * BG_MOVE_COEFFICIENT; // reduce width otherwise tearing occurs

                    pathwayAnchor.x += PIXELS_TO_MOVE_EACH_FRAME * PATHWAY_MOVE_COEFFICIENT;
                    // pathwayPos.x += PIXELS_TO_MOVE_EACH_FRAME * PATHWAY_MOVE_COEFFICIENT;
                    pathwayPos.w -= PIXELS_TO_MOVE_EACH_FRAME * PATHWAY_MOVE_COEFFICIENT;
                }
                else if(characterPos.x + PIXELS_TO_MOVE_EACH_FRAME * PATHWAY_MOVE_COEFFICIENT < SCREEN_WIDTH-characterPos.w){
                    characterPos.x += PIXELS_TO_MOVE_EACH_FRAME * PATHWAY_MOVE_COEFFICIENT;
                }
            
            break;

            
        case 'l':
            texcharacter = texcharacter_L[stepX];
            if(pathwayAnchor.x - PIXELS_TO_MOVE_EACH_FRAME * PATHWAY_MOVE_COEFFICIENT > 0){
                backgroundAnchor.x -= PIXELS_TO_MOVE_EACH_FRAME * BG_MOVE_COEFFICIENT;
                backgroundPos.w += PIXELS_TO_MOVE_EACH_FRAME * BG_MOVE_COEFFICIENT;
                pathwayAnchor.x -= PIXELS_TO_MOVE_EACH_FRAME * PATHWAY_MOVE_COEFFICIENT;
                pathwayPos.w += PIXELS_TO_MOVE_EACH_FRAME * PATHWAY_MOVE_COEFFICIENT;
            }
            else if(characterPos.x>0){
                characterPos.x -= PIXELS_TO_MOVE_EACH_FRAME * PATHWAY_MOVE_COEFFICIENT;
            }
            
            break;
        case 'u':
            if(stepY < CHARACTER_MOVEMENT_STEP_Y) 
                characterPos.y -= CHARACTER_MOVEMENT_STEP_Y/(stepY+1) * LADDER_COEFFICIENT;
            break;
        case 'd':
            if(stepY < CHARACTER_MOVEMENT_STEP_Y) 
                characterPos.y += CHARACTER_MOVEMENT_STEP_Y/(stepY+1) * LADDER_COEFFICIENT;
            break;
        default:
            break;
        }
    }
    else{
        if(stepY < CHARACTER_MOVEMENT_STEP_Y/2)characterPos.y -= CHARACTER_MOVEMENT_STEP_Y/(stepY+1) * JUMP_COEFFICIENT;
        if(stepY >= CHARACTER_MOVEMENT_STEP_Y/2)characterPos.y += CHARACTER_MOVEMENT_STEP_Y/(CHARACTER_MOVEMENT_STEP_Y-stepY) * JUMP_COEFFICIENT;
        
        switch (direction)
        {
        case 'r':
            
            if(characterPos.x < SCREEN_WIDTH/2 - characterPos.w){
                characterPos.x += PIXELS_TO_MOVE_EACH_FRAME * PATHWAY_MOVE_COEFFICIENT;
                
            }
            else if(pathwayAnchor.x + PIXELS_TO_MOVE_EACH_FRAME * PATHWAY_MOVE_COEFFICIENT + JUMP_MOVE_COEFFICIENT < (5500)){
                backgroundAnchor.x += PIXELS_TO_MOVE_EACH_FRAME * BG_MOVE_COEFFICIENT + JUMP_MOVE_COEFFICIENT; // move the texture
                backgroundPos.w -= PIXELS_TO_MOVE_EACH_FRAME * BG_MOVE_COEFFICIENT + JUMP_MOVE_COEFFICIENT; // reduce width otherwise tearing occurs

                pathwayAnchor.x += PIXELS_TO_MOVE_EACH_FRAME * PATHWAY_MOVE_COEFFICIENT + JUMP_MOVE_COEFFICIENT;
                pathwayPos.w -= PIXELS_TO_MOVE_EACH_FRAME * PATHWAY_MOVE_COEFFICIENT + JUMP_MOVE_COEFFICIENT;
            }
            else if(characterPos.x + PIXELS_TO_MOVE_EACH_FRAME * PATHWAY_MOVE_COEFFICIENT < SCREEN_WIDTH-characterPos.w){
                characterPos.x += PIXELS_TO_MOVE_EACH_FRAME * PATHWAY_MOVE_COEFFICIENT;
            }
            break;
        case 'l':
            
            if(pathwayAnchor.x - PIXELS_TO_MOVE_EACH_FRAME * PATHWAY_MOVE_COEFFICIENT > 0){
                backgroundAnchor.x -= PIXELS_TO_MOVE_EACH_FRAME * BG_MOVE_COEFFICIENT;
                backgroundPos.w += PIXELS_TO_MOVE_EACH_FRAME * BG_MOVE_COEFFICIENT;
                pathwayAnchor.x -= PIXELS_TO_MOVE_EACH_FRAME * PATHWAY_MOVE_COEFFICIENT;
                pathwayPos.w += PIXELS_TO_MOVE_EACH_FRAME * PATHWAY_MOVE_COEFFICIENT;
            }
            else if(characterPos.x>0){
                characterPos.x -= PIXELS_TO_MOVE_EACH_FRAME * PATHWAY_MOVE_COEFFICIENT;
            }
            
            break;
        default:
            break;
        }
    }
    
    return true;
}

bool gravity(){
    characterPos.y += 20;
}
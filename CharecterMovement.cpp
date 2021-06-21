#include "globalVariables.h"
#include "CharecterMovement.h"
#include <bits/stdc++.h>

const int PIXELS_TO_MOVE_EACH_FRAME = 1;
const int JUMP_COEFFICIENT = 5;

bool characterPositionHandle(char directionX, bool jump, int stepY){
    
    // if(direction == 'r'){
    //     characterDirection = 'r';
    //     // charecterPos.x += CHARACTER_MOVEMENT_STEP/(step+1);
    //     charecterPos.x += 2;
    // }
    // else if(direction == 'l'){
    //     characterDirection = 'l';
    //     // charecterPos.x -= CHARACTER_MOVEMENT_STEP/(step+1);
    //     charecterPos.x -= 2;
    // }
    // else if(direction == 'j'){
    //     characterDirection = 'j';
    //     if(step < CHARACTER_MOVEMENT_STEP_Y/2)charecterPos.y -= CHARACTER_MOVEMENT_STEP_Y/(step+1);
    //     if(step >= CHARACTER_MOVEMENT_STEP_Y/2)charecterPos.y += CHARACTER_MOVEMENT_STEP_Y/(CHARACTER_MOVEMENT_STEP_Y-step);
    // }

    if(!jump){
        switch (directionX)
        {
        case 'r':
            charecterPos.x += PIXELS_TO_MOVE_EACH_FRAME;
            break;
        case 'l':
            charecterPos.x -= PIXELS_TO_MOVE_EACH_FRAME;
            break;
        default:
            break;
        }
    }
    else{
        if(stepY < CHARACTER_MOVEMENT_STEP_Y/2)charecterPos.y -= CHARACTER_MOVEMENT_STEP_Y/(stepY+1);
        if(stepY >= CHARACTER_MOVEMENT_STEP_Y/2)charecterPos.y += CHARACTER_MOVEMENT_STEP_Y/(CHARACTER_MOVEMENT_STEP_Y-stepY);
        
        switch (directionX)
        {
        case 'r':
            charecterPos.x += PIXELS_TO_MOVE_EACH_FRAME*JUMP_COEFFICIENT;
            break;
        case 'l':
            charecterPos.x -= PIXELS_TO_MOVE_EACH_FRAME*JUMP_COEFFICIENT;
            break;
        default:
            break;
        }
    }
    
    return true;
}
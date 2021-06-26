#pragma once

#ifndef LOAD_EVERYTHING_H
#define LOAD_EVERYTHING_H	

bool startScreen();
bool loadGameBackground(int PLAYER_CURRENT_LEVEL);
bool loadCharacter();
bool loadEnemy(int PLAYER_CURRENT_LEVEL);
bool loadBullet();
bool loadSound(int PLAYER_CURRENT_LEVEL);

#endif // LOAD_EVERYTHING_H
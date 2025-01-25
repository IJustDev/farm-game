#ifndef PLAYER_H
#define PLAYER_H

#include "inventory.h"

#define VELOCITY 8

#define PLAYER_SPRITE 90

typedef struct {
    char* name;
    int x, y;
    int moves_x, moves_y;
} Player;

Player* create_player(const char* name);
void free_player(Player* player);

#endif

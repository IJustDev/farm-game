#ifndef PLAYER_H
#define PLAYER_H

#include "inventory.h"

#define VELOCITY 16

#define PLAYER_SPRITE 90

typedef struct {
    char* name;
    int x, y;
} Player;

Player* create_player(const char* name);
void free_player(Player* player);

#endif

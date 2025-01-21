#include "player.h"
#include <stdlib.h>
#include <string.h>

Player* create_player(const char* name) {
    Player* player = malloc(sizeof(Player));
    if (player) {
        player->name = strdup(name);
        player->x = 0;
        player->y = 0;
    }
    return player;
}

void free_player(Player* player) {
    if (player) {
        free(player->name);
        free(player);
    }
}

#include "player.h"
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>

Player* create_player(const char* name) {
    Player* player = malloc(sizeof(Player));
    if (player) {
        player->name = strdup(name);
        player->x = 0;
        player->y = 0;
        player->moves_x = 0;
        player->moves_y = 0;
    }
    return player;
}

void player_update(Player* player) {
    int new_x = player->x + player->moves_x * VELOCITY;
    if (new_x > 0 && new_x <= 800 - 64)
        player->x = new_x;

    int new_y = player->y + player->moves_y * VELOCITY;
    if (new_y > 0 && new_y <= 600 - 64)
        player->y = new_y;
}

void free_player(Player* player) {
    if (player) {
        free(player->name);
        free(player);
    }
}

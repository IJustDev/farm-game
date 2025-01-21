#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>
#include "player.h"
#include "inventory.h"

void handle_input(SDL_Event* event, int* running, Player* player, Inventory* inventory);

#endif


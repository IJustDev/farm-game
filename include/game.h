#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "player.h"
#include "inventory.h"
#include "sprite.h"

void draw_player(SDL_Renderer* renderer, Player* player);
void draw_inventory(SDL_Renderer* renderer, SpriteSheet* sprite_sheet, TTF_Font* font, Inventory* inventory);
void draw_map(SDL_Renderer* renderer, SpriteSheet* spritesheet);

#endif


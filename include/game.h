#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "player.h"
#include "inventory.h"
#include "sprite.h"

extern Player* player;
extern Inventory* inventory;

void initialize_game();

void draw_player(SDL_Renderer* renderer, SpriteSheet* sprite_sheet, Player* player);
void draw_inventory(SDL_Renderer* renderer, SpriteSheet* sprite_sheet, TTF_Font* font);
void draw_map(SDL_Renderer* renderer, SpriteSheet* spritesheet);

void check_collision();

#endif


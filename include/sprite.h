#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>

#define SPRITE_SIZE 32

#define GRASS_TL 0
#define GRASS_TR 1
#define GRASS_BL 15
#define GRASS_BR 16

#define SPRITESHEET_PATH "assets/sprites/tools.png"

typedef struct {
	SDL_Texture* texture;
} SpriteSheet;

SpriteSheet* load_spritesheet(SDL_Renderer* renderer);

void render_sprite(SDL_Renderer* renderer, SpriteSheet* spritesheet, int sprite_index, int x, int y);

void free_spritesheet(SpriteSheet* spritesheet);
#endif

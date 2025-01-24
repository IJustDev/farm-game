#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>

#define SPRITE_SIZE 32

#define SPRITESHEET_PATH "assets/sprites/tools.png"

typedef struct {
	SDL_Texture* texture;
} SpriteSheet;

SpriteSheet* load_spritesheet(SDL_Renderer* renderer);

void render_scaled_sprite(SDL_Renderer* renderer, SpriteSheet* spritesheet, int sprite_index, int x, int y, int scale);
void render_sprite(SDL_Renderer* renderer, SpriteSheet* spritesheet, int sprite_index, int x, int y);

void free_spritesheet(SpriteSheet* spritesheet);
#endif

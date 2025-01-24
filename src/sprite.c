#include "sprite.h"
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <stdio.h>

SpriteSheet* load_spritesheet(SDL_Renderer* renderer) {
	SDL_Surface* loaded_surface = IMG_Load(SPRITESHEET_PATH);
	if(!loaded_surface) {
		printf("Error loading sprite sheet. %s", IMG_GetError());
		return NULL;
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
	SDL_FreeSurface(loaded_surface);
	if(!loaded_surface) {
		printf("Error loading texture. %s", SDL_GetError());
		return NULL;
	}
    	SpriteSheet* spritesheet = (SpriteSheet*)malloc(sizeof(SpriteSheet));
	spritesheet->texture = texture;
	return spritesheet;
}

void render_scaled_sprite(SDL_Renderer* renderer, SpriteSheet* spritesheet, int sprite_index, int x, int y, int scale) {
	if (!spritesheet || !renderer) return;
	int sheet_width, sheet_height;
	SDL_QueryTexture(spritesheet->texture, NULL, NULL, &sheet_width, &sheet_height);
	
	int columns = sheet_width / SPRITE_SIZE;
	
	int src_x = (sprite_index % columns) * SPRITE_SIZE;
	int src_y = (sprite_index / columns) * SPRITE_SIZE;
	SDL_Rect src_rect = {src_x, src_y, SPRITE_SIZE, SPRITE_SIZE};
	SDL_Rect dest_rect = {x, y, SPRITE_SIZE * scale, SPRITE_SIZE * scale};
	
	SDL_RenderCopy(renderer, spritesheet->texture, &src_rect, &dest_rect);
}

void render_sprite(SDL_Renderer* renderer, SpriteSheet* spritesheet, int sprite_index, int x, int y) {
	render_scaled_sprite(renderer, spritesheet, sprite_index, x, y, 1);
}

void free_spritesheet(SpriteSheet* sheet) {
    if (sheet) {
	SDL_DestroyTexture(sheet->texture);
	free(sheet);
    }
}


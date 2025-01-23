#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "player.h"
#include "inventory.h"
#include "game.h"
#include "input.h"
#include "sprite.h"

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0 || TTF_Init() == -1) {
        printf("SDL konnte nicht initialisiert werden: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Cleaned Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    TTF_Font* font = TTF_OpenFont("assets/font.ttf", 24);

    if (!window || !renderer || !font) {
        printf("Fehler beim Initialisieren von Ressourcen.\n");
        SDL_Quit();
        return 1;
    }

    SpriteSheet* sheet = load_spritesheet(renderer);

    Player* player = create_player("Player One");
    Inventory* inventory = create_inventory();

    SDL_Event e;
    int running = 1;

    while (running) {
        while (SDL_PollEvent(&e)) {
            handle_input(&e, &running, player, inventory);
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

	draw_map(renderer, sheet);
        draw_player(renderer, player);
        draw_inventory(renderer, font, inventory);

        SDL_RenderPresent(renderer);
    }

    free_player(player);
    free_inventory(inventory);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();

    return 0;
}


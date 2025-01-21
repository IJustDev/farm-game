#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "player.h"
#include "inventory.h"

void draw_player(SDL_Renderer* renderer, Player* player) {
    SDL_Rect rect = { player->x, player->y, 32, 32 };  // x, y, Breite, Höhe
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Rot
    SDL_RenderFillRect(renderer, &rect); // Rechteck füllen
}

void draw_item(SDL_Renderer* renderer, int index, ItemStack* itemStack, TTF_Font* font) {
    SDL_Rect rect = {200 + index * 45, 500, 45, 48};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &rect);

    // Text nur rendern, wenn ein Item vorhanden ist
    if (itemStack->item != NULL) {
        SDL_Color textColor = {255, 255, 255, 255};
        char item[8];
        snprintf(item, 8, "%d", itemStack->amount);
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, item, textColor);

        if (!textSurface) {
            printf("Fehler beim Erstellen der Text-Oberfläche: %s\n", TTF_GetError());
            return;
        }

        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_Rect textRect = {200 + index * 45 + 16, 510, textSurface->w, textSurface->h};

        SDL_FreeSurface(textSurface);
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
        SDL_DestroyTexture(textTexture);
    }
}

void draw_inventory(SDL_Renderer* renderer, TTF_Font* font, Inventory* inventory) {
    SDL_Rect rect = {200, 500, 405, 48};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &rect);
    for (int i = 0; i < INVENTORY_COLS; i++) {
        draw_item(renderer, i, &inventory->items[i], font);
    }
}


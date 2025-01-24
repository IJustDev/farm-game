#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "player.h"
#include "inventory.h"
#include "sprite.h"

Player* player;
Inventory* inventory;

void draw_player(SDL_Renderer* renderer, SpriteSheet* sprite_sheet, Player* player) {
    render_scaled_sprite(renderer, sprite_sheet, PLAYER_SPRITE, player->x, player->y, 2);
}

void draw_count(SDL_Renderer* renderer, SpriteSheet* sprite_sheet, int index, ItemStack* itemStack, TTF_Font* font) {
    SDL_Color textColor = {255, 255, 255, 255};
    char item[sizeof(int)];
    snprintf(item, sizeof(int), "%d", itemStack->amount);
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, item, textColor);

    if (!textSurface) {
        printf("Fehler beim Erstellen der Text-Oberfläche: %s\n", TTF_GetError());
        return;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_Rect textRect = {208 + index * 45 + 16, 520, textSurface->w, textSurface->h};

    SDL_FreeSurface(textSurface);
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_DestroyTexture(textTexture);
}

void draw_item(SDL_Renderer* renderer, SpriteSheet* sprite_sheet, int index, ItemStack* itemStack, TTF_Font* font) {
    SDL_Rect rect = {200 + index * 45, 500, 45, 48};
    if (index == selected) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    } else
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &rect);

    // Text nur rendern, wenn ein Item vorhanden ist
    if (itemStack->item != NULL) {
        render_sprite(renderer, sprite_sheet, itemStack->item->definition.sprite_index, 206 + index * 45, 506);
        if (itemStack->item->definition.is_tool == 0) {
            draw_count(renderer, sprite_sheet, index, itemStack, font);
        }
    }
}

void draw_inventory(SDL_Renderer* renderer, SpriteSheet* sprite_sheet, TTF_Font* font) {
    SDL_Rect rect = {200, 500, 405, 48};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &rect);
    for (int i = 0; i < INVENTORY_COLS; i++) {
        draw_item(renderer, sprite_sheet, i, &inventory->items[i], font);
    }
}

typedef struct {
    int x;
    int y;
    Item* item;
} DroppedItemStack;

DroppedItemStack dropped_items[32];

void drop_item(int index, int x, int y, int item) {
    dropped_items[index].x = x;
    dropped_items[index].y = y;
    dropped_items[index].item = create_item(item);
}

void initialize_game() {
    initialize_items();
    player = create_player("Player One");
    inventory = create_inventory();
    drop_item(0, 96, 96, ITEM_HP);
    drop_item(1, 96, 96, ITEM_HP);
    drop_item(2, 96, 96, ITEM_HP);
    drop_item(3, 96, 96, ITEM_HP);
    drop_item(2, 192, 96, ITEM_WATER);
    drop_item(4, 128, 256, ITEM_AXE);
    drop_item(5, 384, 128, ITEM_SHOVEL);
    drop_item(6, 416, 128, ITEM_SHOVEL);
}

void check_collision() {
    for (int i = 0; i != 32; i++) {
        if (dropped_items[i].item == NULL) continue;
        DroppedItemStack dropped = dropped_items[i];
        if (player->x + 32 >= dropped.x && player->x <= dropped.x + 32 && player->y + 32 >= dropped.y && player->y <= dropped.y + 32) {
            collect_item(inventory, dropped_items[i].item);
            dropped_items[i].item = NULL;
        }
    }
}

void draw_map(SDL_Renderer* renderer, SpriteSheet* sprite_sheet) {
    for (int i = 0; i != 32; i++) {
        if (dropped_items[i].item == NULL) continue;
        DroppedItemStack dropped = dropped_items[i];
        render_sprite(renderer, sprite_sheet, dropped.item->definition.sprite_index, dropped.x, dropped.y);
    }
}


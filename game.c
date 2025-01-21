#include <stdio.h>
#include <stdlib.h>
#include <libc.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define INVENTORY_COLS 9
#define INVENTORY_ROWS 4
#define VELOCITY 16
#define SCALE 1

typedef struct {
	char* name;
	int character;
	int x;
	int y;
} Player;

typedef struct {
	int id;
} Item;

const int ITEM_SHOVEL = 0;
const int ITEM_AXE = 1;
const int ITEM_DIRT = 2;
const int ITEM_WOOD = 3;

typedef struct {
	Item* item;
	int amount;
} ItemStack;

typedef struct {
	ItemStack items[INVENTORY_ROWS * INVENTORY_COLS];
} Inventory;

const int MATERIAL_DIRT = 0;
const int MATERIAL_STONE = 1;

typedef struct {
	int id;
	int material;
	int hardness;
} Block;

const int BLOCK_COBBLESTONE = 0;
const int BLOCK_DIRT = 1;
const int BLOCK_IRONORE = 2;

Block* new_cobblestone() {
	Block* b = malloc(sizeof(Block));
	b->material = MATERIAL_STONE;
	b->hardness = 1;
	return b;
}

Block* new_dirt() {
	Block* b = malloc(sizeof(Block));
	b->material = MATERIAL_DIRT;
	b->hardness = 1;
	return b;
}

Block* new_iron_ore() {
	Block* b = malloc(sizeof(Block));
	b->material = MATERIAL_STONE;
	b->hardness = 2;
	return b;
}

Player* player;
Inventory* inventory;

void initialize_player() {
	player = malloc(sizeof(Player));
	player->name = "Player One";
	player->x = 0;
	player->y = 0;
	inventory = malloc(sizeof(Inventory));
}

Item* create_item(int id) {
	Item* item = malloc(sizeof(Item));
	item->id = id;
	return item;
}

int are_equal_items(Item* one, Item* two) {
	return (one->id == two->id);
}

int find_index_of_item_stack(Item* item) {
	for (int i = 0; i <INVENTORY_ROWS; i++) {
		for (int j = 0; j < INVENTORY_COLS; j++) {
			int index = INVENTORY_COLS * i + j;
			ItemStack itemStack = inventory->items[index];
			if (itemStack.item == NULL) continue;
			if (are_equal_items(itemStack.item, item)) {
				return index;
			}
		}
	}
  return -1;
}

int next_free_slot() {
	for (int i = 0; i <INVENTORY_ROWS; i++) {
		for (int j = 0; j < INVENTORY_COLS; j++) {
			int index = INVENTORY_COLS * i + j;
			ItemStack itemStack = inventory->items[index];
			if (itemStack.item == NULL) return index;
		}
	}
  return -1;
}

int collect_item(Item* item) {
	int index = find_index_of_item_stack(item);
  if (index == -1) {
		ItemStack* itemStack = malloc(sizeof(ItemStack));
		itemStack->item = item;
		itemStack->amount = 1;
		int next_slot = next_free_slot();
		if (next_slot == -1) {
			return -1;
		}
		inventory->items[next_slot] = *itemStack;
  } else {
		inventory->items[index].amount++;
	}
	return 0;
}

Item* drop_item(int index) {
	return NULL;
}

void print_inventory() {
	for (int i = 0; i <INVENTORY_ROWS; i++) {
		for (int j = 0; j < INVENTORY_COLS; j++) {
			int index = INVENTORY_COLS * i + j;
			if (inventory->items[index].item != NULL)
			printf("%i:%i->%i\n", index, inventory->items[index].item->id, inventory->items[index].amount);
		}
	}
}

void draw_player(SDL_Renderer* renderer) {
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
				snprintf(item, 8, "%d", itemStack->item->id);
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, item, textColor);
        
        if (!textSurface) {
            printf("Fehler beim Erstellen der Text-Oberfläche: %s\n", TTF_GetError());
            return;
        }

        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_Rect textRect = {200 + index * 45 + 16, 510, textSurface->w, textSurface->h}; // Text unter das Item setzen

        SDL_FreeSurface(textSurface); // Text-Oberfläche nach Erstellung der Textur freigeben

        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
        SDL_DestroyTexture(textTexture); // Textur freigeben
    }
}

void draw_inventory(SDL_Renderer* renderer, TTF_Font* font) {
	SDL_Rect rect = {200, 500, 405, 48};
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &rect);
	for (int i = 0; i < INVENTORY_COLS; i++) {
		draw_item(renderer, i, &inventory->items[i], font);
	}
}

void test() {
	Item* item = create_item(ITEM_SHOVEL);
	Item* item2 = create_item(ITEM_SHOVEL);
	Item* item3 = create_item(ITEM_AXE);
	collect_item(item);
	collect_item(item2);
	collect_item(item3);
}
int main() {
		initialize_player();
		test();
    // SDL initialisieren
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL konnte nicht initialisiert werden: %s\n", SDL_GetError());
        return 1;
    }
		if (TTF_Init() == -1) {
        printf("SDL_ttf konnte nicht initialisiert werden: %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }

    // Fenster erstellen
    SDL_Window* window = SDL_CreateWindow("Farm Game",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          800, 600,
                                          SDL_WINDOW_SHOWN);

    if (!window) {
        printf("Fenster konnte nicht erstellt werden: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }


    // Renderer erstellen
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer konnte nicht erstellt werden: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    // Textfarbe festlegen (z.B. weiß)
    SDL_Color textColor = {255, 255, 255, 255};

    TTF_Font* font = TTF_OpenFont("./font.ttf", 24);
		if (!font) {
        printf("Schriftart konnte nicht geladen werden: %s\n", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Hauptloop
    SDL_Event event;
    int running = 1;

    while (running) {
        // Events verarbeiten
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = 0; // Beendet die Schleife bei Fenster schließen
                    break;

                case SDL_KEYDOWN: // Taste gedrückt
										if (event.key.keysym.sym == SDLK_s) {
											player->y+=VELOCITY;
											printf("%i %i", player->x, player->y);
										}
										if (event.key.keysym.sym == SDLK_a) {
											player->x-=VELOCITY;
											printf("%i %i", player->x, player->y);
										}
										if (event.key.keysym.sym == SDLK_d) {
											player->x+=VELOCITY;
											printf("%i %i", player->x, player->y);
										}
										if (event.key.keysym.sym == SDLK_w) {
											player->y-=VELOCITY;
											printf("%i %i", player->x, player->y);
										}
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        running = 0; // ESC beendet das Spiel
                    }
                    break;

                case SDL_KEYUP: // Taste losgelassen
                    printf("Taste losgelassen: %s\n", SDL_GetKeyName(event.key.keysym.sym));
                    break;

                default:
                    break;
            }
        }

        // Fensterinhalt aktualisieren
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Schwarz
        SDL_RenderClear(renderer);

				// Render
				draw_player(renderer);
				draw_inventory(renderer, font);
        // Renderer anzeigen
        SDL_RenderPresent(renderer);
    }

    // Ressourcen freigeben
		TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}


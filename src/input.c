#include <SDL2/SDL.h>
#include "player.h"
#include "inventory.h"

// Verarbeitet Tastatureingaben
void handle_input(SDL_Event* event, int* running, Player* player, Inventory* inventory) {
    switch (event->type) {
        case SDL_QUIT: // Fenster schließen
            *running = 0;
            break;

        case SDL_KEYDOWN: // Taste gedrückt
            switch (event->key.keysym.sym) {
                case SDLK_w: // Hoch
                    player->y -= VELOCITY;
                    break;
                case SDLK_a: // Links
                    player->x -= VELOCITY;
                    break;
                case SDLK_s: // Runter
                    player->y += VELOCITY;
                    break;
                case SDLK_d: // Rechts
                    player->x += VELOCITY;
                    break;
                case SDLK_f: // Gegenstand aufnehmen
                    collect_item(inventory, create_item(ITEM_HP)); // Beispiel: Axe sammeln
                    break;
                case SDLK_e: // Gegenstand aufnehmen
                    collect_item(inventory, create_item(ITEM_AXE)); // Beispiel: Axe sammeln
                    break;
                case SDLK_q: // Gegenstand aufnehmen
                    collect_item(inventory, create_item(ITEM_SHOVEL)); // Beispiel: Shovel sammeln
                    break;
                case SDLK_ESCAPE: // Spiel beenden
                    *running = 0;
                    break;
                default:
                    break;
            }
            break;

        case SDL_KEYUP: // Taste losgelassen (falls benötigt)
            printf("Taste losgelassen: %s\n", SDL_GetKeyName(event->key.keysym.sym));
            break;

        default:
            break;
    }
}


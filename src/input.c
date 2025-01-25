#include <SDL2/SDL.h>
#include "player.h"
#include "inventory.h"
#include "game.h"

// Verarbeitet Tastatureingaben
void handle_input(SDL_Event* event, int* running, Player* player, Inventory* inventory) {
    switch (event->type) {
        case SDL_QUIT: // Fenster schließen
            *running = 0;
            break;

	case SDL_KEYUP:
		switch(event->key.keysym.sym) {
			case SDLK_w:
			case SDLK_s:
				player->moves_y = 0;
				break;
			case SDLK_a:
			case SDLK_d:
				player->moves_x = 0;
				break;
		}
		break;
        case SDL_KEYDOWN: // Taste gedrückt
            switch (event->key.keysym.sym) {
                case SDLK_1:
                    select(0);
                    break;
                case SDLK_2:
                    select(1);
                    break;
                case SDLK_3:
                    select(2);
                    break;
                case SDLK_4:
                    select(3);
                    break;
                case SDLK_5:
                    select(4);
                    break;
                case SDLK_6:
                    select(5);
                    break;
                case SDLK_7:
                    select(6);
                    break;
                case SDLK_8:
                    select(7);
                    break;
                case SDLK_9:
                    select(8);
                    break;
                case SDLK_w: // Hoch
                    player->moves_y = -1;
                    break;
                case SDLK_a: // Links
			player->moves_x = -1;
                    break;
                case SDLK_s: // Runter
			player->moves_y = 1;
                    break;
                case SDLK_d: // Rechts
			player->moves_x = 1;
                    break;
                case SDLK_ESCAPE: // Spiel beenden
                    *running = 0;
                    break;
                default:
                    break;
            }
            break;

        default:
            break;
    }
}


#include "inventory.h"
#include <stdlib.h>
#include <stdio.h>

Inventory* create_inventory() {
    Inventory* inventory = malloc(sizeof(Inventory));
    if (inventory) {
        for (int i = 0; i < INVENTORY_ROWS * INVENTORY_COLS; i++) {
            inventory->items[i].item = NULL;
            inventory->items[i].amount = 0;
        }
    }
    return inventory;
}

void free_inventory(Inventory* inventory) {
    if (inventory) {
        for (int i = 0; i < INVENTORY_ROWS * INVENTORY_COLS; i++) {
            free(inventory->items[i].item);
        }
        free(inventory);
    }
}

int collect_item(Inventory* inventory, Item* item) {
    for (int i = 0; i < INVENTORY_ROWS * INVENTORY_COLS; i++) {
        if (inventory->items[i].item && inventory->items[i].item->id == item->id) {
            inventory->items[i].amount++;
            return 0;
        }
    }

    for (int i = 0; i < INVENTORY_ROWS * INVENTORY_COLS; i++) {
        if (!inventory->items[i].item) {
            inventory->items[i].item = item;
            inventory->items[i].amount = 1;
            return 0;
        }
    }
    return -1;
}

void print_inventory(const Inventory* inventory) {
    for (int i = 0; i < INVENTORY_ROWS * INVENTORY_COLS; i++) {
        if (inventory->items[i].item) {
            printf("Slot %d: Item ID %d, Amount %d\n", i, inventory->items[i].item->id, inventory->items[i].amount);
        }
    }
}

Item* create_item(int id) {
    Item* item = malloc(sizeof(Item));
    if (item == NULL) {
        return NULL;
    }
    item->id = id;
    return item;
}


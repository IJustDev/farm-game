#include "inventory.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

ItemDefinition item_definitions[32];

void register_item(int id, const char* name, int sprite_index) {
    item_definitions[id].id = id;
    item_definitions[id].sprite_index = sprite_index;
    item_definitions[id].is_tool = 0;
    strcpy(item_definitions[id].name, name);
}

void register_tool(int id, const char* name, int sprite_index, int material, int max_uses) {
    register_item(id, name, sprite_index);
    item_definitions[id].is_tool = 1;
    item_definitions[id].material = material;
    item_definitions[id].max_uses = max_uses;
}

void initialize_items() {
    register_tool(ITEM_SHOVEL, "Shovel", 0, MATERIAL_DIRT, 200);
    register_tool(ITEM_AXE, "Axe", 1, MATERIAL_WOOD, 200);
    register_item(ITEM_HP, "HP", 11);
}

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

int collect_item(Inventory* inventory, Item* collectable) {
    for (int i = 0; i < INVENTORY_ROWS * INVENTORY_COLS; i++) {
        Item* item = inventory->items[i].item;
        if (collectable->definition.is_tool == 1) break;
        if (item != NULL && item->definition.id == collectable->definition.id && inventory->items[i].amount < MAX_STACK_SIZE) {
            inventory->items[i].amount++;
            return 0;
        }
    }

    for (int i = 0; i < INVENTORY_ROWS * INVENTORY_COLS; i++) {
        if (!inventory->items[i].item) {
            inventory->items[i].item = collectable;
            inventory->items[i].amount = 1;
            return 0;
        }
    }
    return -1;
}

void print_inventory(const Inventory* inventory) {
    for (int i = 0; i < INVENTORY_ROWS * INVENTORY_COLS; i++) {
        if (inventory->items[i].item) {
            printf("Slot %d: Item ID %d, Amount %d\n", i, inventory->items[i].item->definition.id, inventory->items[i].amount);
        }
    }
}

Item* create_item(int definition) {
    Item* item = malloc(sizeof(Item));
    if (item == NULL) {
        return NULL;
    }
    item->definition = item_definitions[definition];
    return item;
}


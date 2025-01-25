#ifndef INVENTORY_H
#define INVENTORY_H

#define INVENTORY_COLS 9
#define INVENTORY_ROWS 4

#define MAX_STACK_SIZE 64

#include "items.h"

extern int selected;
void select(int index);

typedef struct {
    ItemDefinition definition;
    int uses;
} Item;

typedef struct {
    Item* item;
    int amount;
} ItemStack;

typedef struct {
    ItemStack items[INVENTORY_ROWS * INVENTORY_COLS];
} Inventory;

Inventory* create_inventory();
void free_inventory(Inventory* inventory);
int collect_item(Inventory* inventory, Item* item);
void print_inventory(const Inventory* inventory);
Item* create_item(int item_id);

#endif

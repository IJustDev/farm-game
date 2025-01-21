#ifndef INVENTORY_H
#define INVENTORY_H

#define INVENTORY_COLS 9
#define INVENTORY_ROWS 4

#define ITEM_SHOVEL 0
#define ITEM_AXE 1

typedef struct {
    int id;
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
Item* create_item(int id);

#endif

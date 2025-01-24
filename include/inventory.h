#ifndef INVENTORY_H
#define INVENTORY_H

#define INVENTORY_COLS 9
#define INVENTORY_ROWS 4

#define MAX_STACK_SIZE 64

#define ITEM_SHOVEL 0
#define ITEM_AXE 1
#define ITEM_SWORD 2
#define ITEM_HP 3

#define MATERIAL_WOOD 0
#define MATERIAL_STONE 1
#define MATERIAL_DIRT 2

typedef struct {
    int id;
    char name[32];
    int sprite_index;
    int is_tool;
    int material;
    int max_uses;
} ItemDefinition;

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

void initialize_items();
Inventory* create_inventory();
void free_inventory(Inventory* inventory);
int collect_item(Inventory* inventory, Item* item);
void print_inventory(const Inventory* inventory);
Item* create_item(int item_id);

#endif

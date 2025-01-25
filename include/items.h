#ifndef ITEMS_H
#define ITEMS_H

typedef struct {
    int id;
    char name[32];
    int sprite_index;
    int is_tool;
    int material;
    int max_uses;
} ItemDefinition;

#define MATERIAL_WOOD 0
#define MATERIAL_STONE 1
#define MATERIAL_DIRT 2

#define ITEM_SHOVEL 0
#define ITEM_AXE 1
#define ITEM_SWORD 2
#define ITEM_HP 3
#define ITEM_WATER 4

void initialize_items();
ItemDefinition get_item_definition(int index);
#endif

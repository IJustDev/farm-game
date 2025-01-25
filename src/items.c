#include <string.h>
#include "items.h"

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
    register_item(ITEM_WATER, "Water", 12);
}

ItemDefinition get_item_definition(int index) {
return item_definitions[index];
}

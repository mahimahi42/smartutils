#include "main_menu.h"

// Callback for user selecting menu icon
void menu_select_callback(int index, void* ctx)
{
    first_menu_items[index].subtitle = "You've hit select here!";
    layer_mark_dirty(simple_menu_layer_get_layer(menu_layer));
}

// Initialize the menu and its items 
void init_menu()
{
    int num_a_items = 0;

    first_menu_items[num_a_items++] = (SimpleMenuItem) {
        .title = "First Item",
        .callback = menu_select_callback,
    };

    first_menu_items[num_a_items++] = (SimpleMenuItem) {
        .title = "Second Item",
        .subtitle = "Here's a subtitle!",
        .callback = menu_select_callback,
    };

    first_menu_items[num_a_items++] = (SimpleMenuItem) {
        .title = "Third Item",
        .callback = menu_select_callback,
    };
    //
    // Bind the menu items to their sections
    menu_sections[0] = (SimpleMenuSection) {
        .title = "SmartUtils",
        .num_items = NUM_FIRST_MENU_ITEMS,
        .items = first_menu_items,
    };
}
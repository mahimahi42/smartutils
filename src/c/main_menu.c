#include "headers.h"

// Initialize the menu and its items 
void init_menu()
{
    int num_a_items = 0;

    menu_items[num_a_items++] = (SimpleMenuItem) {
        .title = "Timer",
        .callback = menu_select_callback,
    };

    menu_items[num_a_items++] = (SimpleMenuItem) {
        .title = "Weather",
        .callback = weather_select_callback,
    };

    menu_items[num_a_items++] = (SimpleMenuItem) {
        .title = "Calendar",
        .callback = menu_select_callback,
    };

    menu_items[num_a_items++] = (SimpleMenuItem) {
        .title = "Music",
        .callback = menu_select_callback,
    };

    menu_items[num_a_items++] = (SimpleMenuItem) {
        .title = "Location",
        .callback = menu_select_callback,
    };

    menu_items[num_a_items++] = (SimpleMenuItem) {
        .title = "Tip Calculator",
        .callback = menu_select_callback,
    };

    // Bind the menu items to their sections
    menu_sections[0] = (SimpleMenuSection) {
        .title = "SmartUtils for Pebble",
        .num_items = NUM_FIRST_MENU_ITEMS,
        .items = menu_items,
    };
}

// Callback for user selecting menu icon
void menu_select_callback(int index, void* ctx)
{
    menu_items[index].subtitle = "You've hit select here!";
    layer_mark_dirty(simple_menu_layer_get_layer(menu_layer));
}

// Callback for user selecting Weather applet
void weather_select_callback(int index, void* ctx)
{
    window_stack_push(weather_window, ANIMATED);
}
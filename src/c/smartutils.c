#include "headers.h"

int main(void)
{
    init();
    app_event_loop();
    deinit();
}

// Init the menu on window load
void window_load(Window* window)
{
    // Initialize the menu items
    init_menu();

    // Get the bounds of the window
    Layer* window_layer = window_get_root_layer(window);
    GRect bounds = layer_get_frame(window_layer);

    menu_layer = simple_menu_layer_create(bounds, window, menu_sections, NUM_MENU_SECTIONS, NULL);
    layer_add_child(window_layer, simple_menu_layer_get_layer(menu_layer));
}

void window_unload(Window* window)
{
    simple_menu_layer_destroy(menu_layer);
}

void init()
{
    window = window_create();
    window_set_fullscreen(window, true);
    window_set_window_handlers(window, (WindowHandlers) {
        .load = window_load,
        .unload = window_unload,
    });
    window_stack_push(window, ANIMATED);
}

void deinit()
{
    window_destroy(window);
}

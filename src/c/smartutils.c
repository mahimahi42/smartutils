#include <pebble.h>

#define NUM_MENU_SECTIONS 1
#define NUM_FIRST_MENU_ITEMS 6

// The main window for the app
static Window *window;
// The main menu layer
static SimpleMenuLayer* menu_layer;
// Menu sections
static SimpleMenuSection menu_sections[NUM_MENU_SECTIONS];
// Items included in the sections
static SimpleMenuItem first_menu_items[NUM_FIRST_MENU_ITEMS];

static bool flag = false;
static int hit_count = 0;

// Callback for user selecting menu icon
static void menu_select_callback(int index, void* ctx)
{
    first_menu_items[index].subtitle = "You've hit select here!";
    layer_mark_dirty(simple_menu_layer_get_layer(menu_layer));
}

// Init the menu on window load
static void window_load(Window* window)
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

int main(void)
{
    window = window_create();

    window_set_fullscreen(window, true);

    window_set_window_handlers(window, (WindowHandlers) {
        .load = window_load,
        .unload = window_unload,
    });

    window_stack_push(window, true);
    app_event_loop();
    window_destroy(window);
}

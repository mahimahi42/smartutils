#ifndef SMARTUTIL_H
#define SMARTUTIL_H
#include <pebble.h>

#define NUM_MENU_SECTIONS 1
#define NUM_FIRST_MENU_ITEMS 6

// The main window for the app
static Window *window;

// Lifecycle functions
void init();
void deinit();

#endif

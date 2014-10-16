#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "smartutils.h"

// The main menu layer
SimpleMenuLayer* menu_layer;
// Menu sections
SimpleMenuSection menu_sections[NUM_MENU_SECTIONS];
// Items included in the sections
SimpleMenuItem menu_items[NUM_FIRST_MENU_ITEMS];

void init_menu();
void menu_select_callback(int, void*);
void weather_select_callback(int, void*);

#endif
#ifndef LOCATION_H
#define LOCATION_H

// Window for location applet
Window* location_window;

// TextLayers for location info
TextLayer* location_title_text_layer;
TextLayer* location_info_text_layer;

// Lifecycle functions
void location_window_init();
void location_window_deinit();
void location_window_load();
void location_window_appear();
void location_window_disappear();
void location_window_unload();

#endif
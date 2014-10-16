#ifndef WEATHER_H
#define WEATHER_H

#define KEY_WEATHER_TEMP 0
#define KEY_WEATHER_TEMP_LOW 1
#define KEY_WEATHER_TEMP_HIGH 2
#define KEY_WEATHER_COND 3

// Window for weather applet
Window* weather_window;

// TextLayers for weather info
TextLayer* weather_title_text_layer;
TextLayer* weather_info_text_layer;

// Buffers for AppMessages
static char temp_buffer[16];
static char temp_low_buffer[16];
static char temp_high_buffer[16];
static char cond_buffer[64];
static char info_buffer[256];

// Lifecycle functions
void weather_window_init();
void weather_window_deinit();
void weather_window_load(Window*);
void weather_window_appear(Window*);
void weather_window_disappear(Window*);
void weather_window_unload(Window*);
void weather_click_to_close(void*);
void weather_back_click_handler(ClickRecognizerRef, void*);
void weather_down_click_handler(ClickRecognizerRef, void*);

// AppMessage API (for weather info)
void weather_inbox_received_callback(DictionaryIterator*, void*);
void weather_inbox_dropped_callback(AppMessageResult, void*);
void weather_outbox_failed_callback(DictionaryIterator*, 
                                    AppMessageResult, void*);
void weather_outbox_sent_callback(DictionaryIterator*, void*);

#endif
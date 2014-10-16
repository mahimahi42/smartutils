#ifndef WEATHER_H
#define WEATHER_H

#define KEY_WEATHER_TEMP 0

// Window for weather applet
Window* weather_window;
TextLayer* weather_temp_text_layer;

// Buffers for AppMessages
static char temp_buffer[32];

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
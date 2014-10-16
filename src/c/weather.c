#include "headers.h"

void weather_window_init()
{
    weather_window = window_create();
    window_set_fullscreen(weather_window, true);
    window_set_window_handlers(weather_window, (WindowHandlers) {
        .load = weather_window_load,
        .appear = weather_window_appear,
        .disappear = weather_window_disappear,
        .unload = weather_window_unload,
    });

    app_message_register_inbox_received(weather_inbox_received_callback);
    app_message_register_inbox_dropped(weather_inbox_dropped_callback);
    app_message_register_outbox_failed(weather_outbox_failed_callback);
    app_message_register_outbox_sent(weather_outbox_sent_callback);
    app_message_open(app_message_inbox_size_maximum(), 
                     app_message_outbox_size_maximum());

    window_set_click_config_provider(weather_window, weather_click_to_close);

    // Begin dictionary
    DictionaryIterator *iter;
    app_message_outbox_begin(&iter);

    // Add a key-value pair
    dict_write_uint8(iter, 0, 0);

    // Send the message!
    app_message_outbox_send();
}

void weather_window_deinit()
{
    window_destroy(weather_window);
}

void weather_window_load(Window* window) {
    weather_temp_text_layer = text_layer_create(GRect(0, 0, 144, 168));
    text_layer_set_background_color(weather_temp_text_layer, GColorClear);
    text_layer_set_text_color(weather_temp_text_layer, GColorBlack);
    text_layer_set_text_alignment(weather_temp_text_layer, GTextAlignmentCenter);
    layer_add_child(window_get_root_layer(weather_window), 
                    text_layer_get_layer(weather_temp_text_layer));
    //text_layer_set_text(weather_temp_text_layer, 
    //                    "Testing...");
}

void weather_window_appear(Window* window) {

}

void weather_window_disappear(Window* window) {

}

void weather_window_unload(Window* window) {
    text_layer_destroy(weather_temp_text_layer);
}

void weather_click_to_close(void* context) {
    window_single_click_subscribe(BUTTON_ID_BACK, weather_back_click_handler);
}

void weather_back_click_handler(ClickRecognizerRef recognizer, 
                                void* context) {
    window_stack_pop(ANIMATED);
}

void weather_inbox_received_callback(DictionaryIterator* iterator, 
                                     void* context) {
    // Read first item
    Tuple* t = dict_find(iterator, KEY_WEATHER_TEMP);
    snprintf(temp_buffer, sizeof(temp_buffer), "%dC", (int)t->value->int32);
    text_layer_set_text(weather_temp_text_layer, temp_buffer);
    layer_mark_dirty(text_layer_get_layer(weather_temp_text_layer));
}

void weather_inbox_dropped_callback(AppMessageResult reason, void* context) {
    APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped!");
}

void weather_outbox_failed_callback(DictionaryIterator* iterator, 
                                    AppMessageResult reason, void* context) {
    APP_LOG(APP_LOG_LEVEL_ERROR, "Outbox send failed!");
}

void weather_outbox_sent_callback(DictionaryIterator* iterator, void* context) {
    APP_LOG(APP_LOG_LEVEL_INFO, "Outbox send success!");
}
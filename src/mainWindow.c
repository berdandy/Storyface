#include <pebble.h>
#include "mainWindow.h"

static Window *s_mainWindow;
static TextLayer *s_timeLayer;

void mainWindowLoad(Window *window) {
  // Create time TextLayer
  s_timeLayer = text_layer_create(GRect(0, 55, 144, 50));
  text_layer_set_background_color(s_timeLayer, GColorClear);
  text_layer_set_text_color(s_timeLayer, GColorBlack);
  text_layer_set_text(s_timeLayer, "00:00");

  // Improve the layout to be more like a watchface
  text_layer_set_font(s_timeLayer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
  text_layer_set_text_alignment(s_timeLayer, GTextAlignmentCenter);

  // Add it as a child layer to the Window's root layer
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_timeLayer));
}

void mainWindowUnload(Window *window) {
    // Destroy TextLayer
    text_layer_destroy(s_timeLayer);
}

void initMainWindow() {
  // Create main Window element and assign to pointer
  s_mainWindow = window_create();

  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(s_mainWindow, (WindowHandlers) {
    .load = mainWindowLoad,
    .unload = mainWindowUnload
  });

  // Show the Window on the watch, with animated=true
  window_stack_push(s_mainWindow, true);
}

void deinitMainWindow() {
	// Destroy Window
    window_destroy(s_mainWindow);
}

void updateTime() {
	// Get a tm structure
  time_t temp = time(NULL); 
  struct tm *tick_time = localtime(&temp);

  // Create a long-lived buffer
  static char buffer[] = "00:00";

  // Write the current hours and minutes into the buffer
  if(clock_is_24h_style() == true) {
    // Use 24 hour format
    strftime(buffer, sizeof("00:00"), "%H:%M", tick_time);
  } else {
    // Use 12 hour format
    strftime(buffer, sizeof("00:00"), "%I:%M", tick_time);
  }

  // Display this time on the TextLayer
  text_layer_set_text(s_timeLayer, buffer);
}
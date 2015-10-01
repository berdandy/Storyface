#include <pebble.h>
#include "mainWindow.h"

static Window *s_mainWindow;
static TextLayer *s_timeLayer;
static TextLayer *s_storyTitleLayer;
static TextLayer *s_storyTextLayer;

void mainWindowLoad(Window *window) {
	// Create time TextLayer
	s_timeLayer = text_layer_create(GRect(0, 125, 144, 50));
	text_layer_set_background_color(s_timeLayer, GColorClear);
	text_layer_set_text_color(s_timeLayer, GColorBlack);
	text_layer_set_text(s_timeLayer, "00:00");
	text_layer_set_font(s_timeLayer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
	text_layer_set_text_alignment(s_timeLayer, GTextAlignmentRight);
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_timeLayer));
	
	s_storyTitleLayer = text_layer_create(GRect(0, 0, 144, 24));
	text_layer_set_background_color(s_storyTitleLayer, GColorClear);
	text_layer_set_text_color(s_storyTitleLayer, GColorBlack);
	text_layer_set_text(s_storyTitleLayer, "Story Title");	
	text_layer_set_font(s_storyTitleLayer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
	text_layer_set_text_alignment(s_storyTitleLayer, GTextAlignmentCenter);
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_storyTitleLayer));

	// Create story TextLayer
	s_storyTextLayer = text_layer_create(GRect(12, 24, 120, 120));
	text_layer_set_background_color(s_storyTextLayer, GColorClear);
	text_layer_set_text_color(s_storyTextLayer, GColorBlack);
	text_layer_set_text(s_storyTextLayer, "Story Text 1\nThis is the first note\ntest test test\n4\n5\n6");	
	text_layer_set_font(s_storyTextLayer, fonts_get_system_font(FONT_KEY_GOTHIC_18));
	text_layer_set_text_alignment(s_storyTextLayer, GTextAlignmentLeft);
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_storyTextLayer));
}

void mainWindowUnload(Window *window) {
    text_layer_destroy(s_timeLayer);
	text_layer_destroy(s_storyTitleLayer);	
	text_layer_destroy(s_storyTextLayer);
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
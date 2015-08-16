#include <pebble.h>
#include "mainWindow.h"
	
static void tickHandler(struct tm *tick_time, TimeUnits units_changed) {
	updateTime();
}

static void init() {
	initMainWindow();
	updateTime();
	
	tick_timer_service_subscribe(MINUTE_UNIT, tickHandler);
}

static void deinit() {
	deinitMainWindow();
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
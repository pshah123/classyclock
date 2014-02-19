#include <pebble.h>

static char* format_time(struct tm *tick_time) {
  static char time_text[] = "00:00";
  static char *time_format;
  if (clock_is_24h_style()) {
    time_format = "%R";
  } else {
    time_format = "%I:%M";
  }
  strftime(time_text, sizeof(time_text), time_format, tick_time);
  if (!clock_is_24h_style() && (time_text[0] == '0')) {
    // Remove the leading zero when 12-hour clock is used
    memmove(time_text, &time_text[1], sizeof(time_text) - 1);
  }
  return time_text;
}

static char* format_next_class_time(int next_class_minutes_left, char* next_class_verb) {
  static char next_class_time[32];
  if (next_class_minutes_left > 60) {
    snprintf(next_class_time, 32, "%s in %dh%dm", next_class_verb, next_class_minutes_left / 60, next_class_minutes_left % 60);
  } else {
    snprintf(next_class_time, 32, "%s in %d min.", next_class_verb, next_class_minutes_left);
  }
  return next_class_time;
}
/*
 * data.h
 *
 * Created: 14.04.2022 19:31:22
 *  Author: Micha³ Jackowski
 */ 

#ifndef SNAKE_DATA_H_
#define SNAKE_DATA_H_

#include <avr/pgmspace.h>

// Snake main menu
extern const char snake_menu_play[]	PROGMEM;
extern const char snake_menu_settings[]	PROGMEM;
extern const char snake_menu_exit[]	PROGMEM;

// Snake settings menu
extern const char snake_settings_sound[]	PROGMEM;
extern const char snake_settings_borders[]	PROGMEM;
extern const char snake_settings_map_limit_x[]	PROGMEM;
extern const char snake_settings_map_limit_y[]	PROGMEM;
extern const char snake_settings_return[]	PROGMEM;

#endif /* SNAKE_DATA_H_ */
/*
 * data.c
 *
 * Created: 14.04.2022 19:49:47
 *  Author: Micha³ Jackowski
 */ 

#ifndef __cplusplus
#include <avr/io.h>
#endif // !__cplusplus
#include <stdlib.h>

#include "SnakeData.h"

// Menu const strings
const char snake_menu_play[]	PROGMEM = "Uruchom";
const char snake_menu_settings[]	PROGMEM = "Ustawienia";
const char snake_menu_exit[]	PROGMEM = "Wyjdz";

// Snake settings menu
const char snake_settings_sound[]	PROGMEM = "Dzwiek: ";
const char snake_settings_borders[]	PROGMEM = "Sciany: ";
const char snake_settings_map_limit_x[]	PROGMEM = "Granica X: ";
const char snake_settings_map_limit_y[]	PROGMEM = "Granica Y: ";
const char snake_settings_return[]	PROGMEM = "Wroc";
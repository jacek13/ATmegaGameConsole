/*
 * systemData.h
 *
 * Created: 29.11.2022 20:38:06
 *  Author: Michal
 */ 

#ifndef SYSTEMDATA_H_
#define SYSTEMDATA_H_

#include <avr/pgmspace.h>

// Menu const strings
extern const char menu_main_menu[]		PROGMEM; 
extern const char menu_apps[]			PROGMEM; 
extern const char menu_settings[]		PROGMEM; 
extern const char menu_info[]			PROGMEM; 
extern const char menu_game_tetris[]	PROGMEM; 
extern const char menu_game_snake[]		PROGMEM; 
extern const char menu_return[]			PROGMEM; 
extern const char menu_turn_sound[]		PROGMEM; 
extern const char menu_turn_data[]		PROGMEM; 
extern const char menu_turn_info[]		PROGMEM; 
extern const char menu_brightness[]		PROGMEM; 
extern const char menu_compile_time[]	PROGMEM; 
extern const char menu_author_name[]	PROGMEM; 
extern const char menu_hardware[]		PROGMEM; 
extern const char menu_instruction[]	PROGMEM; 
extern const char menu_processor[]		PROGMEM; 
extern const char menu_display[]		PROGMEM; 
extern const char menu_controller[]		PROGMEM; 
extern const char menu_rtc[]			PROGMEM; 
extern const char menu_link_info[]		PROGMEM; 
extern const char menu_github_link[]	PROGMEM;

// Menu Element type acronyms
extern const char menu_element_info[]		PROGMEM;
extern const char menu_element_submenu[]	PROGMEM;
extern const char menu_element_app[]		PROGMEM;
extern const char menu_element_return[]		PROGMEM;
extern const char menu_element_select[]		PROGMEM;
extern const char menu_element_value[]		PROGMEM;
extern const char menu_element_unknown[]	PROGMEM;

// Settings description
extern const char menu_true[]			PROGMEM;
extern const char menu_false[]			PROGMEM;

#endif /* SYSTEMDATA_H_ */
/*
 * systemData.c
 *
 * Created: 29.11.2022 21:58:00
 *  Author: Michal
 */ 

#include "systemData.h"

// Menu const strings
const char menu_main_menu[]		PROGMEM = "Menu glowne";
const char menu_apps[]			PROGMEM = "Gry i aplikacje";
const char menu_settings[]		PROGMEM = "Ustawienia";
const char menu_info[]			PROGMEM = "Info";
const char menu_return[]		PROGMEM = "Wroc";
const char menu_turn_sound[]	PROGMEM = "Wl/wyl dzwiek";
const char menu_turn_data[]		PROGMEM = "Wl/wyl data";
const char menu_turn_info[]		PROGMEM = "Wl/wyl opisy menu";
const char menu_brightness[]	PROGMEM = "Jasnosc";
const char menu_compile_time[]	PROGMEM = __TIMESTAMP__;
const char menu_author_name[]	PROGMEM = "Autor: Michal Jackowski";
const char menu_hardware[]		PROGMEM = "Sprzet";
const char menu_instruction[]	PROGMEM = "Instrukcja";
const char menu_processor[]		PROGMEM = "Procesor: ATmega328PU";
const char menu_display[]		PROGMEM = "Wyswietlacz: WS240x320";
const char menu_controller[]	PROGMEM = "Sterownik: ILI9341";
const char menu_rtc[]			PROGMEM = "Zegar RTC: DS1307";
const char menu_link_info[]		PROGMEM = "Repozytorium projektu:";
const char menu_github_link[]	PROGMEM = "www.github.com/jacek13";

// RGB565 settings
extern const char menu_set_rgb565[]		PROGMEM = "Kolor czcionki";
extern const char menu_set_rgb565_R[]	PROGMEM = "Kanal R";
extern const char menu_set_rgb565_G[]	PROGMEM = "Kanal G";
extern const char menu_set_rgb565_B[]	PROGMEM = "Kanal B";

// Menu Element type acronyms
const char menu_element_info[]		PROGMEM = "[INF]";
const char menu_element_submenu[]	PROGMEM = "[SUB]";
const char menu_element_app[]		PROGMEM = "[EXE]";
const char menu_element_return[]	PROGMEM = "[RET]";
const char menu_element_select[]	PROGMEM = "[SEL]";
const char menu_element_value[]		PROGMEM = "[VAL]";
const char menu_element_unknown[]	PROGMEM = "[UNK]";

const char menu_true[]	PROGMEM = "true";
const char menu_false[]	PROGMEM = "false";

// Games
const char menu_game_tetris[]	PROGMEM = "Tetris";
const char menu_game_snake[]	PROGMEM = "Snake";

// Applications
const char menu_demo_Text[]		PROGMEM = "demo Text";
const char menu_demo_RTC[]		PROGMEM = "demo RTC";
const char menu_demo_Sounds[]	PROGMEM = "demo play sounds";
const char menu_demo_dynamic_text[]		PROGMEM = "demo dynamic text";
const char menu_demo_bitmaps[]	PROGMEM = "demo bitmaps";
const char menu_demo_lines[]	PROGMEM = "demo draw lines";
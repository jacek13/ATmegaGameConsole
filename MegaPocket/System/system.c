/*
 * system.c
 *
 * Created: 29.11.2022 21:18:23
 *  Author: Michal
 */ 

#include "system.h"
#include "../Demos/demo.h"

void designMenu(struct Menu* menu)
{
	MenuStatusCode status = MENU_UNKNOWN;

	// Main Menu
	status = MenuAVRSpecificAddElementAt(menu, 0, MENU_INFORMATION, &menu_main_menu);
	status = MenuAVRSpecificAddElementAt(menu, 1, MENU_SUBMENU, &menu_apps);
	status = MenuAVRSpecificAddElementAt(menu, 2, MENU_SUBMENU, &menu_settings);
	status = MenuAVRSpecificAddElementAt(menu, 3, MENU_SUBMENU, &menu_info);

	// Submenu Games and applications
	status = MenuAddSubMenuAt(menu, 1, 6);
	status = MenuAVRSpecificAddElementAt(menu->elements[1]->subMenu, 0, MENU_RUN_APP, &menu_game_tetris);
	status = MenuAVRSpecificAddElementAt(menu->elements[1]->subMenu, 1, MENU_RUN_APP, &menu_demo_Sounds);
	status = MenuAVRSpecificAddElementAt(menu->elements[1]->subMenu, 2, MENU_RUN_APP, &menu_demo_Text);
	status = MenuAVRSpecificAddElementAt(menu->elements[1]->subMenu, 3, MENU_RUN_APP, &menu_demo_bitmaps);
	status = MenuAVRSpecificAddElementAt(menu->elements[1]->subMenu, 4, MENU_RUN_APP, &menu_demo_lines);
	status = MenuAVRSpecificAddElementAt(menu->elements[1]->subMenu, 5, MENU_EXIT, &menu_return);
	status = MenuSetElementAppPointerAt(menu->elements[1]->subMenu, 0, TetrisRun);
	status = MenuSetElementAppPointerAt(menu->elements[1]->subMenu, 1, demoPlaySounds);
	status = MenuSetElementAppPointerAt(menu->elements[1]->subMenu, 2, demoText);
	status = MenuSetElementAppPointerAt(menu->elements[1]->subMenu, 3, demoFillDisplayWithBitmaps);
	status = MenuSetElementAppPointerAt(menu->elements[1]->subMenu, 4, demoLines);

	// Submenu Settings
	status = MenuAddSubMenuAt(menu, 2, 5);
	status = MenuAVRSpecificAddElementAt(menu->elements[2]->subMenu, 0, MENU_BOOL_SELECTION, &menu_turn_sound);
	status = MenuAVRSpecificAddElementAt(menu->elements[2]->subMenu, 1, MENU_BOOL_SELECTION, &menu_turn_data);
	status = MenuAVRSpecificAddElementAt(menu->elements[2]->subMenu, 2, MENU_BOOL_SELECTION, &menu_turn_info);
	status = MenuAVRSpecificAddElementAt(menu->elements[2]->subMenu, 3, MENU_INCREASE_DECREASE_VALUE, &menu_brightness);
	status = MenuAVRSpecificAddElementAt(menu->elements[2]->subMenu, 4, MENU_EXIT, &menu_return);
	status = MenuSetElementNumericalInitialValueAt(menu->elements[2]->subMenu, 0, 0);
	status = MenuSetElementNumericalInitialValueAt(menu->elements[2]->subMenu, 1, 1);
	status = MenuSetElementNumericalInitialValueAt(menu->elements[2]->subMenu, 2, 1);
	status = MenuUpdateElementRangesAt(menu->elements[2]->subMenu, 3, 0, 100, 4);

	// Sumbmenu About project
	status = MenuAddSubMenuAt(menu, 3, 5);
	status = MenuAVRSpecificAddElementAt(menu->elements[3]->subMenu, 0, MENU_INFORMATION, &menu_compile_time);
	status = MenuAVRSpecificAddElementAt(menu->elements[3]->subMenu, 1, MENU_INFORMATION, &menu_author_name);
	status = MenuAVRSpecificAddElementAt(menu->elements[3]->subMenu, 2, MENU_SUBMENU, &menu_hardware);
	status = MenuAVRSpecificAddElementAt(menu->elements[3]->subMenu, 3, MENU_SUBMENU, &menu_instruction);
	status = MenuAVRSpecificAddElementAt(menu->elements[3]->subMenu, 4, MENU_EXIT, &menu_return);

	// SubSubmenu specification
	status = MenuAddSubMenuAt(menu->elements[3]->subMenu, 2, 5);
	status = MenuAVRSpecificAddElementAt(menu->elements[3]->subMenu->elements[2]->subMenu, 0, MENU_INFORMATION, &menu_processor);
	status = MenuAVRSpecificAddElementAt(menu->elements[3]->subMenu->elements[2]->subMenu, 1, MENU_INFORMATION, &menu_display);
	status = MenuAVRSpecificAddElementAt(menu->elements[3]->subMenu->elements[2]->subMenu, 2, MENU_INFORMATION, &menu_controller);
	status = MenuAVRSpecificAddElementAt(menu->elements[3]->subMenu->elements[2]->subMenu, 3, MENU_INFORMATION, &menu_rtc);
	status = MenuAVRSpecificAddElementAt(menu->elements[3]->subMenu->elements[2]->subMenu, 4, MENU_EXIT, &menu_return);

	// SubSubmenu specification
	status = MenuAddSubMenuAt(menu->elements[3]->subMenu, 3, 3);
	status = MenuAVRSpecificAddElementAt(menu->elements[3]->subMenu->elements[3]->subMenu, 0, MENU_INFORMATION, &menu_link_info);
	status = MenuAVRSpecificAddElementAt(menu->elements[3]->subMenu->elements[3]->subMenu, 1, MENU_INFORMATION, &menu_github_link);
	status = MenuAVRSpecificAddElementAt(menu->elements[3]->subMenu->elements[3]->subMenu, 2, MENU_EXIT, &menu_return);
}

inline const char * MapMenuTypeToInfoString(MenuElementType type)
{
	switch (type)
	{
		case MENU_INFORMATION:	return menu_element_info;
		case MENU_SUBMENU:		return menu_element_submenu;
		case MENU_RUN_APP:		return menu_element_app;
		case MENU_EXIT:			return menu_element_return;
		case MENU_BOOL_SELECTION:	return menu_element_select;
		case MENU_INCREASE_DECREASE_VALUE: return menu_element_value;
		default: return menu_element_unknown;
	}
}

inline const char * MapMenuSettingsValue(uint8_t val)
{
	return val ? menu_true : menu_false;
}

inline uint8_t MenuCheckForInteractiveButtons(MenuNavigation menuNavigation)
{
	return (MENU_NAVIGATE_LEFT <= menuNavigation) && (menuNavigation <= MENU_NAVIGATE_START);
}

static inline uint16_t calculateOCRnA(uint16_t noteFrequency, uint8_t prescaler)
{
	return (F_CPU / (noteFrequency * prescaler * 2) - 1);
}

void MenuHandleSound(uint16_t interval, NoteIndex currentNote, uint8_t resetCounter, uint8_t soundEnabled)
{
	static uint16_t numberOfInvokes = 0;
	static NoteIndex noteIndex = PAUSE;
	noteIndex = currentNote;
	if (noteIndex == PAUSE || !soundEnabled) 
	{
		OCR1A = 0; 
		return;
	}
	if (numberOfInvokes++ < interval) OCR1A = calculateOCRnA(notes[noteIndex], 8);
	else OCR1A = 0;
	if (resetCounter) numberOfInvokes = 0;
}

void systemRun()
{
	uint8_t numberOfElements = 4;
	uint8_t enableSound = 0;
	uint16_t soundLength = 4;		// number of loops
	NoteIndex currentNote = C1;

	struct Menu* menu = MenuCreate(numberOfElements);
	designMenu(menu);

	struct Menu* activeMenuHandler = menu;
	struct MenuElement* localElement = NULL;
	volatile struct Buttons systemButtons = {};
	char menuChar = ' ';
	static DateTime date;
	static char bufferForDescriptionsFromProgmem[8] = {};
	static char bufferForSettingsValuesFromProgmem[8] = {};
	static char bufferForProgmem[64] = {};
	static char buffer[64] = {};
	
	// start comunication with ds1307
	IIC_init(IIC_SPEED);
	DS1307_init(0x00);
	
	// init audio
	// Set OC1A as output pin
	DDRB = (1 << PB1);
	TCCR1A = (1 << COM1A0);
	TCCR1B = (1 << WGM12) | (1 << CS10);
	
	do
	{
		enableSound = menu->elements[2]->subMenu->elements[0]->numeric.positiveValues;
		DS1307_Get_DateTime(&date);
		InputUpdateStates(&systemButtons);
		MenuNavigation tmpDirection = MenuHandleInput(activeMenuHandler, &systemButtons);
		MenuUpdate(activeMenuHandler, tmpDirection);
		activeMenuHandler = MenuGetActiveMenu(activeMenuHandler); 
		if (MenuCheckForInteractiveButtons(tmpDirection) && (tmpDirection == MENU_NAVIGATE_RIGHT || tmpDirection == MENU_NAVIGATE_LEFT)) Display_Clear_Screen(0x0000), MenuHandleSound(soundLength, currentNote = PAUSE, 1, enableSound);//, MenuHandleSound(soundLength, currentNote = PAUSE, 1);
		if (tmpDirection != MENU_NAVIGATE_NONE)
		{
			for (uint8_t i = 0; i < activeMenuHandler->numberOfElements; i++)
			{
				localElement = activeMenuHandler->elements[i];
				strcpy_P(bufferForProgmem, localElement->text);
				if (menu->elements[2]->subMenu->elements[2]->numeric.positiveValues)
				{
					strcpy_P(bufferForDescriptionsFromProgmem, MapMenuTypeToInfoString(localElement->elementType));
					if (localElement->elementType == MENU_BOOL_SELECTION)
					{
						strcpy_P(bufferForSettingsValuesFromProgmem, MapMenuSettingsValue(localElement->numeric.positiveValues));
						sprintf(buffer, "%s %s: %s%20c", bufferForDescriptionsFromProgmem, bufferForProgmem, bufferForSettingsValuesFromProgmem, ' ');
						if ((tmpDirection == MENU_NAVIGATE_SELECT) || (tmpDirection == MENU_NAVIGATE_START)) MenuHandleSound(soundLength, currentNote = E1, 1, enableSound);
					}
					else if (localElement->elementType == MENU_INCREASE_DECREASE_VALUE)
					{
						sprintf(buffer, "%s %s: %d%20c", bufferForDescriptionsFromProgmem, bufferForProgmem, localElement->numeric.positiveNegativeValues, ' ');
						Display_Set_Brightness(menu->elements[2]->subMenu->elements[3]->numeric.positiveValues);
						if ((tmpDirection == MENU_NAVIGATE_SELECT) || (tmpDirection == MENU_NAVIGATE_START)) MenuHandleSound(soundLength, currentNote = G1, 1, enableSound);
					}
					else
						sprintf(buffer, "%s %s%20c", bufferForDescriptionsFromProgmem, bufferForProgmem, ' ');
				}
				else
				{
					if (localElement->elementType == MENU_BOOL_SELECTION)
					{
						strcpy_P(bufferForSettingsValuesFromProgmem, MapMenuSettingsValue(localElement->numeric.positiveValues));
						sprintf(buffer, "%s: %s%20c", bufferForProgmem, bufferForSettingsValuesFromProgmem, ' ');
						if ((tmpDirection == MENU_NAVIGATE_SELECT) || (tmpDirection == MENU_NAVIGATE_START)) MenuHandleSound(soundLength, currentNote = E1, 1, enableSound);
					}
					else if (localElement->elementType == MENU_INCREASE_DECREASE_VALUE)
					{
						sprintf(buffer, "%s: %d%20c", bufferForProgmem, localElement->numeric.positiveNegativeValues, ' ');
						Display_Set_Brightness(menu->elements[2]->subMenu->elements[3]->numeric.positiveValues);
						if ((tmpDirection == MENU_NAVIGATE_SELECT) || (tmpDirection == MENU_NAVIGATE_START)) MenuHandleSound(soundLength, currentNote = G1, 1, enableSound);
					}
					else
						sprintf(buffer, "%s%20c", bufferForProgmem, ' ');
				}
				Display_Draw_Text(0, (i + 1) * 16, buffer, consolas_font, 0xD800, activeMenuHandler->cursorY == i ? 0x1808 : 0x0000);
			}
		}
		if (menu->elements[2]->subMenu->elements[1]->numeric.positiveValues)
		{
			sprintf(buffer, "System time: %2x:%2x:%2x %2x.%2x.20%2x", date.Hour, date.Minute, date.Second, date.DayOfMonth, date.Month, date.Year);
			Display_Draw_Text(0, 0, buffer, consolas_font, 0xD800, 0x0000);
		}
		else // TODO make PROGMEM STRING FOR CLEARING TEXT ROW || use draw rect for it
		{
			sprintf(buffer, "%40c", ' ');
			Display_Draw_Text(0, 0, buffer, consolas_font, 0xD800, 0x0000);
		}
		MenuHandleSound(soundLength, currentNote, 0, enableSound);
	} while (1);
	MenuAVRSpecificFree(menu);
}

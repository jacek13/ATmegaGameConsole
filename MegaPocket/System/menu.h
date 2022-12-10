#ifndef MENU_H_
#define MENU_H_

#include <stdint.h>

#include "../Input/input.h"

typedef enum MenuStatusCode
{
	MENU_ERROR_WRONG_RANGES = -7,
	MENU_ERROR_WRONG_ELEMENT_TYPE = -6,
	MENU_ERROR_UNKNOWN_ELEMENT_TYPE = -5,
	MENU_ERROR_NEW_STRING_SIZE_OUT_OF_RANGE = -4,
	MENU_ERROR_TOO_FEW_ELEMENTS = -3,
	MENU_ERROR_NULLPTR = -2, 
	MENU_ERROR_INDEX_OUT_OF_RANGE = -1, 
	MENU_SUCCESS = 1,
	MENU_RETURNED_FROM_APP,
	MENU_RETURNED_FROM_SUBMENU,
	MENU_ENTERED_SUBMENU,
	MENU_VALUE_INCREASED,
	MENU_VALUE_DECREASED,
	MENU_BOOL_CHANGED,
	MENU_UNKNOWN
} MenuStatusCode;

typedef enum MenuElementType
{
	MENU_INFORMATION = 0,
	MENU_SUBMENU,
	MENU_RUN_APP,
	MENU_EXIT,
	MENU_BOOL_SELECTION,
	MENU_INCREASE_DECREASE_VALUE
} MenuElementType;

typedef enum MenuNavigation
{
	MENU_NAVIGATE_UP = 0,
	MENU_NAVIGATE_DOWN,
	MENU_NAVIGATE_LEFT, 
	MENU_NAVIGATE_RIGHT,
	MENU_NAVIGATE_SELECT,
	MENU_NAVIGATE_START,
	MENU_NAVIGATE_NONE
} MenuNavigation;

struct MenuElement
{
	const char* text;
	int8_t (*application)();
	int8_t rangeFrom;
	uint8_t rangeTo;
	MenuElementType elementType;
	union numericField
	{
		uint8_t positiveValues;
		int8_t positiveNegativeValues;
	} numeric;
	struct Menu* subMenu;
};

struct Menu
{
	uint8_t cursorX, cursorY;
	uint8_t numberOfElements, numberOfElementsForActiveMenu;
	struct Menu* parent;
	struct MenuElement** elements;
};

MenuStatusCode MenuAddElementAt(struct Menu* menu, uint8_t index, MenuElementType type, const char* text);

MenuStatusCode MenuAVRSpecificAddElementAt(struct Menu* menu, uint8_t index, MenuElementType type, const char * text);

MenuStatusCode MenuUpdateElementTextAt(struct Menu* menu, uint8_t index, const char* newText);

MenuStatusCode MenuUpdateElementTypeAt(struct Menu* menu, uint8_t index, MenuElementType newType);

MenuStatusCode MenuAddSubMenuAt(struct Menu* menu, uint8_t index, uint8_t numberOfElements);

MenuStatusCode MenuSetElementAppPointerAt(struct Menu* menu, uint8_t index, uint8_t (*app)());

MenuStatusCode MenuSetElementNumericalInitialValueAt(struct Menu* menu, uint8_t index, int8_t initialValue);

MenuStatusCode MenuUpdate(struct Menu* menu, MenuNavigation input);

MenuStatusCode MenuUpdateElementRangesAt(struct Menu* menu, uint8_t index, int8_t from, uint8_t to, int8_t initialValue);

MenuStatusCode MenuFree(struct Menu* menu);

MenuStatusCode MenuAVRSpecificFree(struct Menu* menu);

#ifdef _MSC_VER
void MenuDrawElementAt(struct MenuElement* element, uint8_t index, uint8_t cursorY, uint8_t drawInfo);
#else
void MenuDrawElementAt(struct MenuElement* element, uint8_t index, uint8_t cursorY, uint8_t drawInfo, char * buffer);
#endif

struct Menu* MenuCreate(uint8_t numberOfElements);

struct Menu* MenuCreateChild(struct Menu* parentMenu, uint8_t numberOfElements);

struct Menu* MenuGetActiveMenu(struct Menu* menuBase);

MenuNavigation MenuHandleInput(struct Menu* menu, struct Buttons * buttons);

#endif
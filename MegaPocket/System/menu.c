#include "menu.h"
//#include "../Input/input.h"

#include <stdlib.h>
#include <stdio.h>

#ifdef __cplusplus
#include <conio.h>
#endif // __cplusplus


inline uint8_t StringGetNumberOfCharacters(const char* text)
{
	uint8_t n = 0;
	while (text[n++] != '\0' && n != 0xFF);
	return n;
}

inline void StringCopyContent(const char* textSource, char* textTarget, uint8_t numberOfElementsToCopy)
{
	for (uint8_t i = 0; i < numberOfElementsToCopy; textTarget[i] = textSource[i++]);
}

MenuStatusCode MenuAddElementAt(struct Menu* menu, uint8_t index, MenuElementType type, const char * text)
{
	if (menu == NULL) return MENU_ERROR_NULLPTR;
	if (menu->numberOfElements == 0) return MENU_ERROR_TOO_FEW_ELEMENTS;
	if (index >= menu->numberOfElements) return MENU_ERROR_INDEX_OUT_OF_RANGE;

	menu->elements[index] = (struct MenuElement*)malloc(sizeof(struct MenuElement));
	menu->elements[index]->subMenu = NULL;
	menu->elements[index]->application = NULL;
	menu->elements[index]->numeric.positiveValues = 0;
	menu->elements[index]->elementType = type;
	menu->elements[index]->rangeFrom = 0;
	menu->elements[index]->rangeTo = 100;
	menu->elements[index]->text = (char*) malloc((StringGetNumberOfCharacters(text) + 1) * sizeof(char));
	StringCopyContent(text, menu->elements[index]->text, StringGetNumberOfCharacters(text) + 1);

	return MENU_SUCCESS;
}

MenuStatusCode MenuAVRSpecificAddElementAt(struct Menu* menu, uint8_t index, MenuElementType type, const char * text)
{
	if (menu == NULL) return MENU_ERROR_NULLPTR;
	if (menu->numberOfElements == 0) return MENU_ERROR_TOO_FEW_ELEMENTS;
	if (index >= menu->numberOfElements) return MENU_ERROR_INDEX_OUT_OF_RANGE;

	menu->elements[index] = (struct MenuElement*)malloc(sizeof(struct MenuElement));
	menu->elements[index]->subMenu = NULL;
	menu->elements[index]->application = NULL;
	menu->elements[index]->numeric.positiveValues = 0;
	menu->elements[index]->elementType = type;
	menu->elements[index]->rangeFrom = 0;
	menu->elements[index]->rangeTo = 100;
	menu->elements[index]->text = text;

	return MENU_SUCCESS;
}

MenuStatusCode MenuSetElementAppPointerAt(struct Menu* menu, uint8_t index, uint8_t (*app)())
{
	if (menu == NULL) return MENU_ERROR_NULLPTR;
	if (menu->numberOfElements == 0) return MENU_ERROR_TOO_FEW_ELEMENTS;
	if (index >= menu->numberOfElements) return MENU_ERROR_INDEX_OUT_OF_RANGE;

	menu->elements[index]->application = app;

	return MENU_SUCCESS;
}

MenuStatusCode MenuSetElementNumericalInitialValueAt(struct Menu* menu, uint8_t index, int8_t initialValue)
{
	if (menu == NULL) return MENU_ERROR_NULLPTR;
	if (menu->numberOfElements == 0) return MENU_ERROR_TOO_FEW_ELEMENTS;
	if (index >= menu->numberOfElements) return MENU_ERROR_INDEX_OUT_OF_RANGE;
	if ((menu->elements[index]->elementType != MENU_BOOL_SELECTION) && (menu->elements[index]->elementType != MENU_INCREASE_DECREASE_VALUE)) return MENU_ERROR_WRONG_ELEMENT_TYPE;
	
	menu->elements[index]->numeric.positiveNegativeValues = initialValue;

	return MENU_SUCCESS;
}

MenuStatusCode MenuAddSubMenuAt(struct Menu* menu, uint8_t index, uint8_t numberOfElements)
{
	if (menu == NULL) return MENU_ERROR_NULLPTR;
	if (menu->numberOfElements == 0) return MENU_ERROR_TOO_FEW_ELEMENTS;
	if (index >= menu->numberOfElements) return MENU_ERROR_INDEX_OUT_OF_RANGE;

	menu->elements[index]->elementType = MENU_SUBMENU;
	menu->elements[index]->subMenu = MenuCreateChild(menu, numberOfElements);

	return MENU_SUCCESS;
}

MenuStatusCode MenuUpdateElementTextAt(struct Menu* menu, uint8_t index, const char* newText)
{
	if (menu == NULL) return MENU_ERROR_NULLPTR;
	if (menu->numberOfElements == 0) return MENU_ERROR_TOO_FEW_ELEMENTS;
	if (index >= menu->numberOfElements) return MENU_ERROR_INDEX_OUT_OF_RANGE;
	if (StringGetNumberOfCharacters(newText) > StringGetNumberOfCharacters(menu->elements[index]->text)) return MENU_ERROR_NEW_STRING_SIZE_OUT_OF_RANGE;

	StringCopyContent(newText, menu->elements[index]->text, StringGetNumberOfCharacters(newText) + 1);

	return MENU_SUCCESS;
}

MenuStatusCode MenuUpdateElementTypeAt(struct Menu* menu, uint8_t index, MenuElementType newType)
{
	if (menu == NULL) return MENU_ERROR_NULLPTR;
	if (newType < 0 || newType > MENU_INCREASE_DECREASE_VALUE) return MENU_ERROR_UNKNOWN_ELEMENT_TYPE;
	menu->elements[index]->elementType = newType;
	return MENU_SUCCESS;
}

MenuStatusCode MenuUpdateElementRangesAt(struct Menu* menu, uint8_t index, int8_t from, uint8_t to, int8_t initialValue)
{
	if (menu == NULL) return MENU_ERROR_NULLPTR;
	if (from >= to) return MENU_ERROR_WRONG_RANGES;
	if (menu->elements[index]->elementType != MENU_INCREASE_DECREASE_VALUE) return MENU_ERROR_WRONG_ELEMENT_TYPE;
	menu->elements[index]->numeric.positiveNegativeValues = initialValue;
	menu->elements[index]->rangeFrom = from;
	menu->elements[index]->rangeTo = to;
	return MENU_SUCCESS;
}

struct Menu* MenuCreate(uint8_t numberOfElements)
{
	struct Menu* newMenu = (struct Menu*) malloc(sizeof(struct Menu));
	newMenu->parent = NULL;
	newMenu->cursorX = newMenu->cursorY = 0;
	newMenu->numberOfElementsForActiveMenu = newMenu->numberOfElements = numberOfElements;
	newMenu->elements = (struct MenuElement**) malloc(numberOfElements * sizeof(struct MenuElement*));

	return newMenu;
}

struct Menu* MenuCreateChild(struct Menu* parentMenu, uint8_t numberOfElements)
{
	struct Menu* newMenu = (struct Menu*)malloc(sizeof(struct Menu));
	newMenu->parent = parentMenu;
	newMenu->cursorX = newMenu->cursorY = 0;
	newMenu->numberOfElements = numberOfElements;
	newMenu->elements = (struct MenuElement**)malloc(numberOfElements * sizeof(struct MenuElement*));

	return newMenu;
}

MenuStatusCode MenuFree(struct Menu* menu)
{
	if (menu == NULL) return MENU_ERROR_NULLPTR;

	for (uint8_t i = 0; i < menu->numberOfElements; i++)
	{
		free(menu->elements[i]->text);
		if (menu->elements[i]->subMenu != NULL) MenuFree(menu->elements[i]->subMenu);
		free(menu->elements[i]);
	}
	free(menu->elements);
	free(menu);

	return MENU_SUCCESS;
}

MenuStatusCode MenuAVRSpecificFree(struct Menu* menu)
{
	if (menu == NULL) return MENU_ERROR_NULLPTR;

	for (uint8_t i = 0; i < menu->numberOfElements; i++)
	{
		if (menu->elements[i]->subMenu != NULL) MenuFree(menu->elements[i]->subMenu);
		free(menu->elements[i]);
	}
	free(menu->elements);
	free(menu);

	return MENU_SUCCESS;
}

MenuNavigation MenuHandleInput(struct Menu* menu, struct Buttons* buttons)
{
	if (menu == NULL) return MENU_NAVIGATE_NONE;
	
	//#ifdef _MSC_VER
	//switch (input)
	//{
	//	case 'w': return MENU_NAVIGATE_UP;		// UP
	//	case 's': return MENU_NAVIGATE_DOWN;	// DOWN
	//	case 'a': return MENU_NAVIGATE_LEFT;	// LEFT
	//	case 'd': return MENU_NAVIGATE_RIGHT;	// RIGHT
	//	case 'e': return MENU_NAVIGATE_START;	// START
	//	case 'r': return MENU_NAVIGATE_SELECT;	// SELECT
	//	default: return MENU_NAVIGATE_NONE;
	//} 
	//#else
	if (buttons->ButtonUp.currentState == BUTTON_FALLING_EDGE)		return MENU_NAVIGATE_UP;
	if (buttons->ButtonDown.currentState == BUTTON_FALLING_EDGE)	return MENU_NAVIGATE_DOWN;
	if (buttons->ButtonLeft.currentState == BUTTON_FALLING_EDGE)	return MENU_NAVIGATE_LEFT;
	if (buttons->ButtonRight.currentState == BUTTON_FALLING_EDGE)	return MENU_NAVIGATE_RIGHT;
	if (buttons->ButtonStart.currentState == BUTTON_FALLING_EDGE)	return MENU_NAVIGATE_START;
	if (buttons->ButtonSelect.currentState == BUTTON_FALLING_EDGE)	return MENU_NAVIGATE_SELECT;
	return MENU_NAVIGATE_NONE;
	//#endif
}

struct Menu* MenuGetActiveMenu(struct Menu* menuBase)
{
	struct Menu* tmpMenu = menuBase;
	if (tmpMenu->cursorX == 0xFF && tmpMenu->parent != NULL)
	{
		tmpMenu->cursorX = 0;
		return tmpMenu->parent;
	}
	else if (tmpMenu->cursorX > 0)
	{
		for (uint8_t i = 0; i < tmpMenu->cursorX; i++)
		{
			if (tmpMenu->elements[tmpMenu->cursorY]->subMenu == NULL) return tmpMenu;
			tmpMenu = tmpMenu->elements[tmpMenu->cursorY]->subMenu;
		}
	}
	return tmpMenu;
}

inline MenuStatusCode MenuHandleSelectionInputs(struct Menu* menu, MenuNavigation input)
{
	MenuStatusCode status = MENU_UNKNOWN;
	switch (menu->elements[menu->cursorY]->elementType)
	{
		case MENU_INFORMATION:
		case MENU_SUBMENU:
			if (menu->elements[menu->cursorY]->elementType == MENU_SUBMENU && menu->elements[menu->cursorY]->elementType != NULL)
			{
				menu->cursorX++, status = MENU_SUCCESS;
				break;
			}
			status = MENU_ERROR_INDEX_OUT_OF_RANGE;	// RIGHT
			break;
		case MENU_RUN_APP:
			if (menu->elements[menu->cursorY]->application == NULL)
			{
				status = MENU_ERROR_NULLPTR;
				break;
			}
			menu->elements[menu->cursorY]->application();
			break;
		case MENU_EXIT:
			if (menu->parent != NULL)
			{
				menu->parent->cursorX = 0;
				menu->cursorX--;
				status = MENU_SUCCESS;
				break;
			}
			status = MENU_ERROR_INDEX_OUT_OF_RANGE;
			break;
		case MENU_BOOL_SELECTION:
			menu->elements[menu->cursorY]->numeric.positiveValues = !menu->elements[menu->cursorY]->numeric.positiveValues;
			status = MENU_SUCCESS;
			break;
		case MENU_INCREASE_DECREASE_VALUE:
			if (input == MENU_NAVIGATE_START)
			{
				if ((menu->elements[menu->cursorY]->numeric.positiveNegativeValues + 1) <= menu->elements[menu->cursorY]->rangeTo)
				{
					menu->elements[menu->cursorY]->numeric.positiveNegativeValues++;
					status = MENU_SUCCESS;
					break;
				}
			}
			if (input == MENU_NAVIGATE_SELECT)
			{
				if ((menu->elements[menu->cursorY]->numeric.positiveNegativeValues - 1) >= menu->elements[menu->cursorY]->rangeFrom)
				{
					menu->elements[menu->cursorY]->numeric.positiveNegativeValues--;
					status = MENU_SUCCESS;
					break;
				}
			}
			status = MENU_UNKNOWN;
			break;
		default: break;
	}
	return status;
}

MenuStatusCode MenuUpdate(struct Menu* menu, MenuNavigation input)
{
	MenuStatusCode status = MENU_UNKNOWN;
	switch (input)
	{
		case MENU_NAVIGATE_UP:
			if (menu->cursorY > 0)
			{
				menu->cursorY--, status = MENU_SUCCESS;
				break;
			}
			status = MENU_ERROR_INDEX_OUT_OF_RANGE;
			break;
		case MENU_NAVIGATE_DOWN:
			if ((menu->cursorY + 1) < menu->numberOfElements)
			{
				menu->cursorY++, status = MENU_SUCCESS;
				break;
			}
			status = MENU_ERROR_INDEX_OUT_OF_RANGE;
			break;
		case MENU_NAVIGATE_LEFT:
			if (menu->parent != NULL)
			{
				menu->parent->cursorX = 0;
				menu->cursorX--;
				status = MENU_SUCCESS;
				break;
			}
			status = MENU_ERROR_INDEX_OUT_OF_RANGE;
			break;
		case MENU_NAVIGATE_RIGHT:
			if (menu->elements[menu->cursorY]->elementType == MENU_SUBMENU && menu->elements[menu->cursorY]->elementType != NULL)
			{
				menu->cursorX++, status = MENU_SUCCESS;
				break;
			}
			status = MENU_ERROR_INDEX_OUT_OF_RANGE;
			break;
		case MENU_NAVIGATE_START:
			status = MenuHandleSelectionInputs(menu, input);
			break;
		case MENU_NAVIGATE_SELECT:
			status = MenuHandleSelectionInputs(menu, input);
			break;
		default: status = MENU_UNKNOWN; break;
	}
	return status;
}

void MenuDrawElementAt(struct MenuElement* element, uint8_t index, uint8_t cursorY, uint8_t drawInfo, char * buffer)
{
	#ifdef _MSC_VER
	switch (element->elementType)
	{
		case MENU_INFORMATION:				printf(cursorY == index ? (drawInfo ? "[%d INF]\t%s <-\n" : "[%2d]\t%s <-\n") : (drawInfo ? "[%d INF]\t%s\n" : "[%2d]\t%s\n"), index, element->text); break;
		case MENU_SUBMENU:					printf(cursorY == index ? (drawInfo ? "[%d SUB]\t%s <-\n" : "[%2d]\t%s <-\n") : (drawInfo ? "[%d SUB]\t%s\n" : "[%2d]\t%s\n"), index, element->text); break;
		case MENU_RUN_APP:					printf(cursorY == index ? (drawInfo ? "[%d EXE]\t%s <-\n" : "[%2d]\t%s <-\n") : (drawInfo ? "[%d EXE]\t%s\n" : "[%2d]\t%s\n"), index, element->text); break;
		case MENU_EXIT:						printf(cursorY == index ? (drawInfo ? "[%d RET]\t%s <-\n" : "[%2d]\t%s <-\n") : (drawInfo ? "[%d RET]\t%s\n" : "[%2d]\t%s\n"), index, element->text); break;
		case MENU_BOOL_SELECTION:			printf(cursorY == index ? (drawInfo ? "[%d SEL]\t%s: %s <-\n" : "[%2d]\t%s: %s <-\n") : (drawInfo ? "[%d SEL]\t%s: %s\n" : "[%2d]\t%s: %s\n"), index, element->text, (element->numeric.positiveValues ? "true" : "false")); break;
		case MENU_INCREASE_DECREASE_VALUE:	printf(cursorY == index ? (drawInfo ? "[%d VAL]\t%s: %3d <-\n" : "[%2d]\t%s: %3d <-\n") : (drawInfo ? "[%d VAL]\t%s: %3d\n" : "[%2d]\t%s: %3d\n"), index, element->text, element->numeric.positiveNegativeValues); break;
		default:							printf(cursorY == index ? (drawInfo ? "[%d UNK]\t%s <-\n" : "[%2d]\t%s <-\n") : (drawInfo ? "[%d UNK]\t%s\n" : "[%2d]\t%s\n"), index, element->text); break;
	}
	#else
	switch (element->elementType)
	{
		case MENU_INFORMATION:				sprintf(buffer, cursorY == index ? (drawInfo ? "[%d INF]\t%s <-\n" : "[%2d]\t%s <-\n") : (drawInfo ? "[%d INF]\t%s\n" : "[%2d]\t%s\n"), index, element->text); break;
		case MENU_SUBMENU:					sprintf(buffer, cursorY == index ? (drawInfo ? "[%d SUB]\t%s <-\n" : "[%2d]\t%s <-\n") : (drawInfo ? "[%d SUB]\t%s\n" : "[%2d]\t%s\n"), index, element->text); break;
		case MENU_RUN_APP:					sprintf(buffer, cursorY == index ? (drawInfo ? "[%d EXE]\t%s <-\n" : "[%2d]\t%s <-\n") : (drawInfo ? "[%d EXE]\t%s\n" : "[%2d]\t%s\n"), index, element->text); break;
		case MENU_EXIT:						sprintf(buffer, cursorY == index ? (drawInfo ? "[%d RET]\t%s <-\n" : "[%2d]\t%s <-\n") : (drawInfo ? "[%d RET]\t%s\n" : "[%2d]\t%s\n"), index, element->text); break;
		case MENU_BOOL_SELECTION:			sprintf(buffer, cursorY == index ? (drawInfo ? "[%d SEL]\t%s: %s <-\n" : "[%2d]\t%s: %s <-\n") : (drawInfo ? "[%d SEL]\t%s: %s\n" : "[%2d]\t%s: %s\n"), index, element->text, (element->numeric.positiveValues ? "true" : "false")); break;
		case MENU_INCREASE_DECREASE_VALUE:	sprintf(buffer, cursorY == index ? (drawInfo ? "[%d VAL]\t%s: %3d <-\n" : "[%2d]\t%s: %3d <-\n") : (drawInfo ? "[%d VAL]\t%s: %3d\n" : "[%2d]\t%s: %3d\n"), index, element->text, element->numeric.positiveNegativeValues); break;
		default:							sprintf(buffer, cursorY == index ? (drawInfo ? "[%d UNK]\t%s <-\n" : "[%2d]\t%s <-\n") : (drawInfo ? "[%d UNK]\t%s\n" : "[%2d]\t%s\n"), index, element->text); break;
	}
	#endif
}
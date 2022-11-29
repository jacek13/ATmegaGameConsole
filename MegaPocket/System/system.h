/*
 * system.h
 *
 * Created: 29.11.2022 21:18:09
 *  Author: Michal
 */ 


#ifndef SYSTEM_H_
#define SYSTEM_H_

#include "menu.h"
#include "systemData.h"
#include "../Input/input.h"
#include "../Games/Tetris/Tetris.h"
#include "../DS1307/rtc.h"
#include "../communication/iic.h"
#include "../Data/notes.h"

void designMenu(struct Menu* menu);

void systemRun();

#endif /* SYSTEM_H_ */

#include "MainMenu.h"
#include "SettingsMenu.h"
#include "CountFunction.h"
#include "PositionTable.h"
#include "RotateFunction.h"

CountFunction countFunction;
PositionTable posTable;
RotateFunction rotateFunction;


LCDMenuItem mainMenuItems[] =
{
	{"Settings        ", SettingsMenu::Instance()},
	{"Splines by count", &countFunction},
	{"Position Table  ", &posTable},
	{"Rotate Table    ", &rotateFunction},
};

LCDMenuDescriptor mainMenuDescriptor =
{
	5,
	false,
	mainMenuItems
};
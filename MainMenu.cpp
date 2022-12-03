
#include "MainMenu.h"
#include "SettingsMenu.h"
#include "CountFunction.h"

CountFunction countFunction;


LCDMenuItem mainMenuItems[] =
{
	{"Settings        ", SettingsMenu::Instance()},
	{"Splines by count", &countFunction},
	{"Menu Item 3     ", NULL},
	{"Menu Item 4     ", NULL},
	{"Menu Item 5     ", NULL},
};

LCDMenuDescriptor mainMenuDescriptor =
{
	5,
	false,
	mainMenuItems
};
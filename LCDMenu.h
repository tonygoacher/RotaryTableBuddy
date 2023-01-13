#pragma once
#include <LiquidCrystal_I2C.h>
#include "IMenuNavigator.h"	
#include "Switch.h"


class LCDMenuEntryPoint
{
public:
	virtual void menuEntry() = 0;
};

struct LCDMenuItem
{
	const char	m_menuItemPrompt[17];
    LCDMenuEntryPoint*  m_menuEntryPoint;
};

struct LCDMenuDescriptor
{
	const int m_numItems;
	const bool allowExit;
    LCDMenuItem*  m_menuItems;
};

class LCDMenu
{
public:
	void Init(LiquidCrystal_I2C* lcd, IMenuNavigator* navigator);
	void DoMenu(LCDMenuDescriptor* menuDescriptor);

private:
	IMenuNavigator* m_menuNavigator;
	LiquidCrystal_I2C* m_lcd;

};
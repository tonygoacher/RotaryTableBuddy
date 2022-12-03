#include "Arduino.h"
#include "LCDMenu.h"




void LCDMenu::Init(LiquidCrystal_I2C* lcd, IMenuNavigator* navigator)
{
	m_lcd = lcd;
	m_menuNavigator = navigator;

}



void LCDMenu::DoMenu(LCDMenuDescriptor* menuDescriptor)
{
	int currentPos = 0;
	IMenuNavigator::Navigation navigation;
	if (menuDescriptor->m_numItems)
	{
		m_menuNavigator->init(menuDescriptor);
		m_lcd->clear();
		do
		{
			m_lcd->setCursor(0, 0);
			m_lcd->print(menuDescriptor->m_menuItems[currentPos].m_menuItemPrompt);
			
			do
			{
				navigation = m_menuNavigator->getNavigation();
				delay(100);

			} while (navigation == IMenuNavigator::NONE);


			if (navigation == IMenuNavigator::MENU_CHANGE)
			{
				currentPos = m_menuNavigator->getCurrentMenuPos();
			}

			if (navigation == IMenuNavigator::SELECTED)
			{
				menuDescriptor->m_menuItems[currentPos].m_menuEntryPoint->menuEntry();
				// Restore display after last menu
				m_lcd->clear();
				m_lcd->setCursor(0, 0);
				m_lcd->print(menuDescriptor->m_menuItems[currentPos].m_menuItemPrompt);
				m_menuNavigator->init(menuDescriptor, currentPos);
			}

		}
		while(navigation != IMenuNavigator::EXIT || menuDescriptor->allowExit == false);
	}
}

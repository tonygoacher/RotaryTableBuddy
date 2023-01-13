#include "Arduino.h"
#include "LCDMenu.h"




void LCDMenu::Init(LiquidCrystal_I2C* lcd, IMenuNavigator* navigator)
{
	m_lcd = lcd;
	m_menuNavigator = navigator;

}



void LCDMenu::DoMenu(LCDMenuDescriptor* menuDescriptor)
{
	char buffer[256];
	int currentPos = 0;
	IMenuNavigator::Navigation navigation;
	sprintf(buffer, "Number: %d", menuDescriptor->m_numItems);
	Serial.print(buffer);
	if (menuDescriptor->m_numItems)
	{
		m_menuNavigator->init(menuDescriptor);
		m_lcd->clear();
		do
		{
			m_lcd->setCursor(0, 0);
			sprintf(buffer,"Menur %s\n", menuDescriptor->m_menuItems[currentPos].m_menuItemPrompt);
			Serial.println(buffer);
			m_lcd->print(menuDescriptor->m_menuItems[currentPos].m_menuItemPrompt);
			
			do
			{
				navigation = m_menuNavigator->getNavigation();


			} while (navigation == IMenuNavigator::NONE);


			if (navigation == IMenuNavigator::MENU_CHANGE)
			{
				currentPos = m_menuNavigator->getCurrentMenuPos();
				Serial.println(currentPos);
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

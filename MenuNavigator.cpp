#include <AiAvrRotaryEncoder.h>
#include "Switch.h"
#include "MenuNavigator.h"
#include "LCDMenu.h"

void MenuNavigator::initNavigator(AiAvrRotaryEncoder* rotaryEncoder, Switch* selectSwitch, Switch* exitSwitch)
{
	m_exitSwitch = exitSwitch;
	m_selectSwitch = selectSwitch;
	m_rotaryEncoder = rotaryEncoder;
}

void MenuNavigator::init(LCDMenuDescriptor* menu, int startPos /* =0 */)
{
	m_currentMenuSelection = startPos;
	m_rotaryEncoder->disableAcceleration();
	m_rotaryEncoder->setBoundaries(0, menu->m_numItems-1, true);
	m_rotaryEncoder->setEncoderValue(startPos);
}

int MenuNavigator::getCurrentMenuPos()
{
	return m_rotaryEncoder->readEncoder();
}




IMenuNavigator::Navigation MenuNavigator::getNavigation()
{
	do
	{
		if (m_rotaryEncoder->encoderChanged())
		{
		
			m_currentMenuSelection = (int)m_rotaryEncoder->readEncoder();
		
			return IMenuNavigator::MENU_CHANGE;
		}

		if (m_selectSwitch->Pressed())
		{
			return IMenuNavigator::SELECTED;
		}

		if (m_exitSwitch->Pressed())
		{
			return IMenuNavigator::EXIT;
		}
	} while (1);
}


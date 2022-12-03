#include "ApplicationSystem.h"
#include "Configuration.h"
#include "PositionTable.h"

PositionTable::PositionTable()
: m_nextSwitch(NEXT_SWITCH),
m_backwardsSwitch(BACKWARDS_SWITCH)
{
}

void PositionTable::menuEntry()
{
	m_lcd = ApplicationSystem::Instance().m_lcdDisplay;
	Stepper& stepper = ApplicationSystem::Instance().m_stepper;
	stepper.SetAcceleration(Configuration::instance()->getConfiguration()->acceleration);
	stepper.SetMaxSpeed(Configuration::instance()->getConfiguration()->speed);
	stepper.Enable(true);
	stepper.SetCurrentPos(0);

	m_lcd->clear();
	m_lcd->setCursor(0, 0);
	m_lcd->println("Position Mode   ");
	m_lcd->setCursor(0, 1);
	m_lcd->println("Use Fwd/Bak btns");
	bool movingForwards = false;
	bool movingBackwards = false;
	do
	{
		if (movingForwards == false && m_nextSwitch.Pressed() && movingBackwards == false)
		{
			movingForwards = true;
			stepper.SetCurrentPos(0);
			stepper.GotoRelative(200000);
		}

		if (movingForwards == true && m_nextSwitch.IsDown() == false)
		{
			long posNow = stepper.GetPos();
			posNow += 1;
			stepper.GotoRelative(posNow);
			movingForwards = false;
		}

		if (movingBackwards == false && m_backwardsSwitch.Pressed() && movingForwards == false)
		{
			movingBackwards = true;
			stepper.SetCurrentPos(0);
			stepper.GotoRelative(-200000);
		}

		if (movingBackwards == true && m_backwardsSwitch.IsDown() == false)
		{
			long posNow = stepper.GetPos();
			posNow -= 1;
			stepper.GotoRelative(posNow);
			movingBackwards = false;
		}



		stepper.Run();
	}
	while (ApplicationSystem::Instance().m_exitSwitch.Pressed() == false);
}
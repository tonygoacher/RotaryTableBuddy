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
	RTStepper& stepper = ApplicationSystem::Instance().m_stepper;
	stepper.SetAcceleration(Configuration::instance()->getConfiguration()->acceleration);
	stepper.SetMaxSpeed(Configuration::instance()->getConfiguration()->speed);
	stepper.Enable(true);
	stepper.SetCurrentPos(0);

	m_lcd->clear();
	m_lcd->setCursor(0, 0);
	m_lcd->println("Position Mode   ");
	m_lcd->setCursor(0, 1);
	m_lcd->println("Use dial        ");
	bool movingForwards = false;
	bool movingBackwards = false;

	AiAvrRotaryEncoder* encoder = ApplicationSystem::Instance().m_rotaryEncoder;
	encoder->setAcceleration(1000);
	encoder->setBoundaries(-100000, 100000, true);
	encoder->setEncoderValue(0);
	stepper.SetCurrentPos(0);
	do
	{
		long encodeValue = encoder->encoderChanged();
		if (encodeValue)
		{
			stepper.MoveTo(encoder->readEncoder());
		}

		stepper.Run();
	}
	while (ApplicationSystem::Instance().m_exitSwitch.Pressed() == false);
}
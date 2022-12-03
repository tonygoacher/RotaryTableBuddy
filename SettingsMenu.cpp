

#include "SettingsMenu.h"
#include "ApplicationSystem.h"
#include "Configuration.h"



void setRangeValue(const char* const fmt, int min, int max, int currentValue, int stepSize, int* destination)
{

	int startingValue = currentValue;
	bool selectPressed = false;
	bool exitPressed = false;

	AiAvrRotaryEncoder* encoder = ApplicationSystem::Instance().m_rotaryEncoder;
	ApplicationSystem::Instance().m_lcdDisplay->clear();
	encoder->setBoundaries(0, 601, true);

	encoder->setEncoderValue((long)currentValue / stepSize);
	encoder->setAcceleration(100);

	LiquidCrystal_I2C* lcd = ApplicationSystem::Instance().m_lcdDisplay;
	lcd->home();
	lcd->clear();
	lcd->printf(fmt, currentValue);
	do
	{
		if (currentValue != encoder->readEncoder() * stepSize)
		{
			lcd->home();
			currentValue = encoder->readEncoder() * stepSize;
			lcd->printf(fmt, currentValue);
		}
		exitPressed = ApplicationSystem::Instance().m_exitSwitch.Pressed();
		selectPressed = ApplicationSystem::Instance().m_selectSwitch.Pressed();


	} while (exitPressed == false && selectPressed == false);

	if (startingValue != currentValue && selectPressed)
	{
		*destination = currentValue;
		Configuration::instance()->writeConfiguration();
	}
}


SettingsMenu* SettingsMenu::m_instance = NULL;

SettingsMenu::SettingsMenu()
{

}



class SetMaxSpeed : public LCDMenuEntryPoint
{
public:

	// Inherited via LCDMenuEntryPoint
	virtual void menuEntry() override
	{
		setRangeValue("Max Speed %05d", 0, 601,
			Configuration::instance()->getConfiguration()->speed, 100,
			&Configuration::instance()->getConfiguration()->speed);
		
	}
};


class SetMaxAccel : public LCDMenuEntryPoint
{
public:

	// Inherited via LCDMenuEntryPoint
	virtual void menuEntry() override
	{
		setRangeValue("Max Accel %05d", 0, 601,
			Configuration::instance()->getConfiguration()->acceleration, 100,
			&Configuration::instance()->getConfiguration()->acceleration);

	}
};


class SetStepsPerRevolution : public LCDMenuEntryPoint
{
public:

	// Inherited via LCDMenuEntryPoint
	virtual void menuEntry() override
	{
		Serial.printf("Steps per rev %d", Configuration::instance()->getConfiguration()->stepsPerRev);
		setRangeValue("Steps/Rev %05d", 0, 601,
			Configuration::instance()->getConfiguration()->stepsPerRev, 200,
			&Configuration::instance()->getConfiguration()->stepsPerRev);

	}
};



class TestStepper : public LCDMenuEntryPoint
{
	virtual void menuEntry() override
	{
		ApplicationSystem::Instance().m_stepper.Enable(true);
		ApplicationSystem::Instance().m_stepper.Stop();
		ApplicationSystem::Instance().m_stepper.SetCurrentPos(0);
		ApplicationSystem::Instance().m_stepper.SetAcceleration(Configuration::instance()->getConfiguration()->acceleration);
		ApplicationSystem::Instance().m_stepper.SetMaxSpeed(Configuration::instance()->getConfiguration()->speed);
		// Do 10 revolutions
		long distance = 10 * Configuration::instance()->getConfiguration()->stepsPerRev;
		Serial.printf("Distance %d\n", distance);
		ApplicationSystem::Instance().m_stepper.GotoRelative(distance);
		while (ApplicationSystem::Instance().m_exitSwitch.Pressed() == false &&
			ApplicationSystem::Instance().m_selectSwitch.Pressed() == false &&
			ApplicationSystem::Instance().m_stepper.Running())
		{
			ApplicationSystem::Instance().m_stepper.Run();
		}
	}
};



SettingsMenu* SettingsMenu::Instance()
{
	if (m_instance == NULL)
	{
		m_instance = new SettingsMenu();
	}
	return m_instance;
}

void SettingsMenu::menuEntry()
{
	SetMaxAccel	setMaxAccell;
	SetMaxSpeed setMaxSpeed;
	SetStepsPerRevolution setStepsPerRev;
	TestStepper  testStepper;

	LCDMenuItem settingsMenuItems[] =
	{
		{"Max Speed       ", &setMaxSpeed},
		{"Max Accell      ", &setMaxAccell},
		{"Steps/Rev       ", &setStepsPerRev},
		{"Test Stepper    ",&testStepper },
	};

	LCDMenuDescriptor settingsMenu[] = { 4, true, settingsMenuItems };
	ApplicationSystem::Instance().menu.DoMenu(settingsMenu);
}

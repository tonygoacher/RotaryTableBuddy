
#include "CountFunction.h"
#include "ApplicationSystem.h"
#include "Configuration.h"
#include "Switch.h"





bool CountFunction::setSplineCount()
{
	bool result = false;
	bool exitPressed = false;
	bool selectPressed = false;
	m_splineCount = 2;
	m_lcd = ApplicationSystem::Instance().m_lcdDisplay;
	m_lcd->clear();
	AiAvrRotaryEncoder* encoder = ApplicationSystem::Instance().m_rotaryEncoder;
	encoder->setBoundaries(2, 360, true);
	encoder->setAcceleration(10);
	encoder->setEncoderValue(m_splineCount);

	m_lcd->setCursor(0, 0);
	m_lcd->printf("Spline Count %*3d", 3,m_splineCount);
	do
	{
		if (encoder->encoderChanged())
		{
			m_splineCount = encoder->readEncoder();
			m_lcd->setCursor(0, 0);
			m_lcd->printf("Spline Count %*d", 3,m_splineCount);
		}
		selectPressed = ApplicationSystem::Instance().m_selectSwitch.Pressed();
		exitPressed = ApplicationSystem::Instance().m_exitSwitch.Pressed();
	} while (exitPressed == false && selectPressed == false);
	return selectPressed == true;
}


bool CountFunction::AreYouSure()
{
	m_lcd->setCursor(0, 1);
	m_lcd->println("Exit? Select=No ");
	bool exitPressed = false;
	do
	{
		exitPressed = ApplicationSystem::Instance().m_exitSwitch.Pressed();
	} while (exitPressed == false && ApplicationSystem::Instance().m_selectSwitch.Pressed() == false);
	return exitPressed;
}

void CountFunction::Waiting()
{

	do
	{
		m_lcd->clear();
		m_lcd->setCursor(0, 0);
		m_lcd->print("Ready");
		m_lcd->setCursor(0, 1);
		m_lcd->printf("Spline %d of %d", m_currentSpline, m_splineCount);

		bool nextSwitchPressed = false;
		bool exitSwitchPressed = false;
		bool backwardsSwitchPressed = false;
		do
		{
			nextSwitchPressed = m_nextSwitch.IsDown();
			exitSwitchPressed = ApplicationSystem::Instance().m_exitSwitch.Pressed();
			backwardsSwitchPressed = m_backwardsSwitch.IsDown();
		} while (nextSwitchPressed == false && exitSwitchPressed == false && backwardsSwitchPressed == false);

		if (exitSwitchPressed)
		{
			if (AreYouSure())
			{
				m_state = Exit;
				break;
			}
		}

		if (nextSwitchPressed)
		{
			if (m_currentSpline != m_splineCount)
			{
				m_state = Moving;
				m_currentSpline++;
				InitStepper();
				ApplicationSystem::Instance().m_stepper.GotoRelative(m_stepsPerSpline);
				break;
			}
		}

		if (backwardsSwitchPressed)
		{
			if (m_currentSpline > 1)
			{
				m_state = Moving;
				InitStepper();
				m_currentSpline--;
				ApplicationSystem::Instance().m_stepper.GotoRelative(-m_stepsPerSpline);
				break;
			}
			
		}
	} while (1);
}


CountFunction::CountFunction()
: m_nextSwitch(NEXT_SWITCH),
  m_backwardsSwitch(BACKWARDS_SWITCH)
{

}

void CountFunction::MoveToSpline()
{
	m_lcd->clear();
	m_lcd->setCursor(0, 0);
	m_lcd->println("Moving to spline:");
	m_lcd->setCursor(0, 1);
	m_lcd->printf("%d of %d", m_currentSpline , m_splineCount);

	do
	{
		ApplicationSystem::Instance().m_stepper.Run();
	} while (ApplicationSystem::Instance().m_stepper.Running());
	
	m_state = Ready;
}

void CountFunction::InitStepper()
{
	ApplicationSystem::Instance().m_stepper.SetAcceleration(Configuration::instance()->getConfiguration()->acceleration);
	ApplicationSystem::Instance().m_stepper.SetMaxSpeed(Configuration::instance()->getConfiguration()->speed);
	ApplicationSystem::Instance().m_stepper.Enable(true);

}

void CountFunction::menuEntry()
{
	if (setSplineCount())
	{
		long stepsPerTableRevolution = m_TableReductionRatio * Configuration::instance()->getConfiguration()->stepsPerRev;
		m_stepsPerSpline = stepsPerTableRevolution / m_splineCount;
		Serial.printf("Steps per spline %ld\n", m_stepsPerSpline);
		m_lcd->clear();
		m_lcd->setCursor(0, 0);
		m_state = Ready;
		m_currentSpline = 1;
		do
		{
			switch (m_state)
			{
				case Ready:
				{
					Waiting();
				}
				break;

				case Moving:
				{
					MoveToSpline();
				}
				break;

				case Exit:
				{
					m_lcd->clear();
					return;
				}
			}
		} while (1);
	}
}


#include "ApplicationSystem.h"
#include "RotateFunction.h"
#include "Configuration.h"
#include "Stepper.h"
#include "RPi_Pico_TimerInterrupt.h"


RotateFunction::RotateFunction()
{

	m_speed = 100;
}


RPI_PICO_Timer ITimer0(0);

bool TimerHandler0(struct repeating_timer* t)
{
	static bool toggle = false;

	digitalWrite(PORT_STEP, toggle ? HIGH : LOW);
	toggle = !toggle;
	return true;
}


void RotateFunction::menuEntry()
{
	Stepper stepper = ApplicationSystem::Instance().m_stepper;
	LiquidCrystal_I2C* lcd = ApplicationSystem::Instance().m_lcdDisplay;
	stepper.Enable(true);

	
	Switch exit = ApplicationSystem::Instance().m_exitSwitch;
	Switch fwd(NEXT_SWITCH);


	AiAvrRotaryEncoder* encoder = ApplicationSystem::Instance().m_rotaryEncoder;
	encoder->setAcceleration(10);
	encoder->setBoundaries(10, 1000, false);
	encoder->setEncoderValue(m_speed);


	lcd->clear();
	lcd->setCursor(0, 0);
	lcd->println("Rotate.Press Fwd");
	
	bool exitPressed = false;
	bool fwdPressed = false;
	do
	{
		lcd->setCursor(0, 1);
		lcd->printf("Speed: %05d", m_speed);
		do
		{
			exitPressed = exit.Pressed();
			fwdPressed = fwd.Pressed();
			if (encoder->encoderChanged())
			{
				m_speed = encoder->readEncoder();
				break;
			}
		} while (exitPressed == false && fwdPressed == false);
	} while (exitPressed == false && fwdPressed == false);

	if (exitPressed)
	{
		return;
	}
	lcd->setCursor(0, 0);
	lcd->println("Rotating....    ");
	ITimer0.attachInterruptInterval(m_speed, TimerHandler0);
	do
	{
	
		if (encoder->encoderChanged())
		{
			m_speed = encoder->readEncoder();
			ITimer0.setInterval(m_speed, TimerHandler0);
			lcd->setCursor(0, 1);
			lcd->printf("Speed: %05d", m_speed);
		}
			
	} while (exit.Pressed() == false);
	ITimer0.stopTimer();

}
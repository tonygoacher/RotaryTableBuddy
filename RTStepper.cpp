#include "RTStepper.h"

RTStepper::RTStepper(uint8_t stepPin, uint8_t dirPin, uint8_t enablePin)
{

	m_Stepper = new AccelStepper(AccelStepper::DRIVER, stepPin, dirPin);
	m_Stepper->setAcceleration(900.0f);
	m_Stepper->setMaxSpeed(1.0f);
	m_enablePin = enablePin;
	pinMode(m_enablePin, OUTPUT);
	digitalWrite(m_enablePin, LOW);
	m_stepPin = stepPin;
	m_dirPin = dirPin;

}

RTStepper::RTStepper(uint8_t stepPin, uint8_t dirPin, float speed, float acceleration)
{
	m_Stepper = new AccelStepper(AccelStepper::DRIVER, stepPin, dirPin);
	m_Stepper->setAcceleration(acceleration);
	m_Stepper->setMaxSpeed(speed);
	//m_Stepper->setSpeed(speed);
}

void RTStepper::GotoRelative(long position)
{
	m_Stepper->move(position);
}

void RTStepper::MoveTo(long position)
{
	m_Stepper->moveTo(position);
}

void RTStepper::Enable(bool enable)
{
	digitalWrite(m_enablePin, enable ? LOW : HIGH);
}

void RTStepper::Run()
{
	m_Stepper->run();
}

bool RTStepper::Running()
{
	return m_Stepper->isRunning();
}

void RTStepper::PulsePin()
{
	digitalWrite(m_stepPin, HIGH);
	delayMicroseconds(4);
	digitalWrite(m_stepPin, LOW);

}

void RTStepper::SetDirectionPin(bool forwards)
{
	digitalWrite(m_dirPin, forwards ? HIGH : LOW);
}


void RTStepper::Step()
{
	m_Stepper->runSpeed();
}


void RTStepper::Stop()
{
	m_Stepper->stop();
}


long RTStepper::GetPos()
{
	return m_Stepper->currentPosition();
}

void RTStepper::SetCurrentPos(long newPos)
{
	m_Stepper->setCurrentPosition(newPos);
}

float RTStepper::GetCurrentSpeed()
{
	return m_Stepper->speed();
}

void RTStepper::SetCurrentSpeed(float newSpeed)
{
	m_Stepper->setSpeed(newSpeed);
}



void RTStepper::SetAcceleration(float acceleration)
{
	m_Stepper->setAcceleration(acceleration);
}

void RTStepper::SetMaxSpeed(float maxSpeed)
{
	m_Stepper->setMaxSpeed(maxSpeed);
}
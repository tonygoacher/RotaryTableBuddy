#include "Stepper.h"

Stepper::Stepper(uint8_t stepPin, uint8_t dirPin, uint8_t enablePin)
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

Stepper::Stepper(uint8_t stepPin, uint8_t dirPin, float speed, float acceleration)
{
	m_Stepper = new AccelStepper(AccelStepper::DRIVER, stepPin, dirPin);
	m_Stepper->setAcceleration(acceleration);
	m_Stepper->setMaxSpeed(speed);
	//m_Stepper->setSpeed(speed);
}

void Stepper::GotoRelative(long position)
{
	m_Stepper->move(position);
}

void Stepper::MoveTo(long position)
{
	m_Stepper->moveTo(position);
}

void Stepper::Enable(bool enable)
{
	digitalWrite(m_enablePin, enable ? LOW : HIGH);
}

void Stepper::Run()
{
	m_Stepper->run();
}

bool Stepper::Running()
{
	return m_Stepper->isRunning();
}

void Stepper::PulsePin()
{
	digitalWrite(m_stepPin, HIGH);
	delayMicroseconds(4);
	digitalWrite(m_stepPin, LOW);

}

void Stepper::SetDirectionPin(bool forwards)
{
	digitalWrite(m_dirPin, forwards ? HIGH : LOW);
}


void Stepper::Step()
{
	m_Stepper->runSpeed();
}


void Stepper::Stop()
{
	m_Stepper->stop();
}


long Stepper::GetPos()
{
	return m_Stepper->currentPosition();
}

void Stepper::SetCurrentPos(long newPos)
{
	m_Stepper->setCurrentPosition(newPos);
}

float Stepper::GetCurrentSpeed()
{
	return m_Stepper->speed();
}

void Stepper::SetCurrentSpeed(float newSpeed)
{
	m_Stepper->setSpeed(newSpeed);
}



void Stepper::SetAcceleration(float acceleration)
{
	m_Stepper->setAcceleration(acceleration);
}

void Stepper::SetMaxSpeed(float maxSpeed)
{
	m_Stepper->setMaxSpeed(maxSpeed);
}
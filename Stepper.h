#pragma once

#include <AccelStepper.h>


class Stepper
{
public:
	Stepper(uint8_t stepPin, uint8_t dirPin, uint8_t enablePin);
	Stepper(uint8_t stepPin, uint8_t dirPin, float speed, float acceleration);
	void GotoRelative(long position);
	void MoveTo(long position);
	void Enable(bool enable);
	void Run();
	void Step();
	void Stop();
	long GetPos();
	void SetCurrentPos(long newPos);
	float GetCurrentSpeed();
	void SetCurrentSpeed(float newSpeed);
	void SetAcceleration(float acceleration);
	void SetMaxSpeed(float maxSpeed);
	bool Running();
	void PulsePin();
	void SetDirectionPin(bool forwards);
private:
	AccelStepper* m_Stepper;
	uint8_t m_enablePin;
	uint8_t m_stepPin;
	uint8_t m_dirPin;

};


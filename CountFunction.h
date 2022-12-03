#pragma once

#include "LCDMenu.h"
#include "Switch.h"



class CountFunction : public LCDMenuEntryPoint
{
public:
	CountFunction();
	void menuEntry() override;
private:
	void Waiting();
	bool AreYouSure();
	bool setSplineCount();
	void MoveToSpline();
	void InitStepper();

	Switch m_nextSwitch;
	Switch m_backwardsSwitch;

	int m_splineCount;
	int m_currentSpline;
	LiquidCrystal_I2C* m_lcd;
	static const int m_TableReductionRatio = 90;
	long m_stepsPerSpline;


	enum States
	{
		Ready,
		Moving,
		Paused,
		Exit,

	};

	States m_state;

};
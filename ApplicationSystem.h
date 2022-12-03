#pragma once

#include <LiquidCrystal_I2C.h>
#include <AiAvrRotaryEncoder.h>

#include "Switch.h"
#include "LCDMenu.h"
#include "MenuNavigator.h"
#include "Stepper.h"


#define MenuSelectSwitch	2

#define		LCD_WIDTH	16
#define		LCD_HEIGHT	2
#define		LCD_ADDRESS		0x27

#define		PORT_STEP		19
#define		PORT_ENABLE		17
#define		PORT_DIRECTION	16

#define NEXT_SWITCH	12
#define BACKWARDS_SWITCH	13

class ApplicationSystem
{
public:

	void Init();
	Switch m_selectSwitch;
	Switch m_exitSwitch;
	

	LiquidCrystal_I2C* m_lcdDisplay;
	AiAvrRotaryEncoder* m_rotaryEncoder;
	LCDMenu menu;
	MenuNavigator menuNavigator;
	static ApplicationSystem& Instance();
	Stepper m_stepper;
private:
	void initStepperPorts();
	static void  readEncoderISR();
	ApplicationSystem();	// Prevent external instantiation
};




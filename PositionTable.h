
#pragma once

#include "LCDMenu.h"

class PositionTable : public LCDMenuEntryPoint
{
public: 
	PositionTable();

	void menuEntry() override;
private:
	LiquidCrystal_I2C* m_lcd;
	Switch m_nextSwitch;
	Switch m_backwardsSwitch;

};

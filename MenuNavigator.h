#pragma once

#include "IMenuNavigator.h"


class Switch;
class AiAvrRotaryEncoder;

class MenuNavigator : public IMenuNavigator
{
public: 
	
	void initNavigator(AiAvrRotaryEncoder* rotaryEncoder, Switch* selectSwitch, Switch* exitSwitch);
	

	// Inherited via IMenuNavigator
	void init(LCDMenuDescriptor* menu, int startPos = 0) override;
	int getCurrentMenuPos() override;


	IMenuNavigator::Navigation getNavigation() override;

private:
	AiAvrRotaryEncoder* m_rotaryEncoder;
	Switch* m_selectSwitch;
	Switch* m_exitSwitch;
	int m_currentMenuSelection;




};

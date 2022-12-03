#pragma once

#include "LCDMenu.h"


class SettingsMenu : public LCDMenuEntryPoint
{
public:
	static SettingsMenu* Instance();
	// Inherited via LCDMenuEntryPoint
	void menuEntry() override;
private:
	static SettingsMenu* m_instance;
	SettingsMenu();
};

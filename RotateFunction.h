#pragma once

#include "LCDMenu.h"


class RotateFunction : public LCDMenuEntryPoint
{
public:
	RotateFunction();
	void menuEntry() override;
private:
	long	m_speed;
	bool	m_forwards;
};
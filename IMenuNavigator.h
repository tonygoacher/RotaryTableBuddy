#pragma once

class LCDMenuDescriptor;

class IMenuNavigator
{
public:
	enum Navigation
	{
		NONE,
		MENU_CHANGE,
		SELECTED,
		EXIT,
	};
	virtual void init(LCDMenuDescriptor*, int startPos = 0) = 0;
	virtual IMenuNavigator::Navigation getNavigation() = 0;
	virtual int getCurrentMenuPos() = 0;
};

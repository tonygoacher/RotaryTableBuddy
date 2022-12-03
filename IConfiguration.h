#pragma once


struct ConfigurationV1
{
	int	version;
	int acceleration;
	int speed;
	int stepsPerRev;
	uint16_t csum;
};

class IConfiguration
{
public:

	virtual void init() = 0;
	
	virtual ConfigurationV1* getConfiguration() = 0;
};

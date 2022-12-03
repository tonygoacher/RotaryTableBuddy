#pragma once

#include "IConfiguration.h"

#define CONFIGURATION_STORE_SIZE	512
#define CURRENT_VERSION	1	

class Configuration : public  IConfiguration
{
public:
	static Configuration* instance();
	void init() override;
	ConfigurationV1* getConfiguration() override;
	void writeConfiguration();
private:
	Configuration() {};
	uint16_t getChecksum();
	bool isDataValid();
	void setChecksum();
	void getStoredData();
	ConfigurationV1 m_theConfiguration;
};

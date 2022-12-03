
#include <EEPROM.h>
#include <Arduino.h>
#include "Configuration.h"



Configuration* Configuration::instance()
{
	static Configuration configuration;
	return &configuration;
}


uint16_t Configuration::getChecksum()
{
	uint16_t csum = 0;
	uint8_t* data = (uint8_t*)&m_theConfiguration;
	for (int i = 0; i < offsetof(ConfigurationV1, csum); i++)
	{
		csum += *data++;
	}

	return csum;
}

bool Configuration::isDataValid()
{
	uint16_t csum = getChecksum();
	Serial.printf("Calc csum %dx", csum);
	Serial.printf("Data csum %dx", csum);
	return csum == m_theConfiguration.csum;
}

void Configuration::setChecksum()
{
	uint16_t	csum = 0;
	csum = getChecksum();
	m_theConfiguration.csum = csum;
}


void Configuration::init()
{
	EEPROM.begin(CONFIGURATION_STORE_SIZE);
	getStoredData();
	if (isDataValid() == false)
	{
		memset(&m_theConfiguration, 0, sizeof(m_theConfiguration));
		m_theConfiguration.acceleration = 1234;
		m_theConfiguration.speed = 5678;
		m_theConfiguration.version = CURRENT_VERSION;
		writeConfiguration();
	}
}

void Configuration::getStoredData()
{

	if (sizeof(ConfigurationV1) <= CONFIGURATION_STORE_SIZE)
	{

		EEPROM.get(0, m_theConfiguration);
	}
}

ConfigurationV1* Configuration::getConfiguration()
{
	return &m_theConfiguration;
}

void Configuration::writeConfiguration()
{
	setChecksum();
	EEPROM.put(0, m_theConfiguration);
	EEPROM.commit();
}
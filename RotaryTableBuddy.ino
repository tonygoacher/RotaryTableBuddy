
#include <EEPROM.h>
#include <Wire.h>
#include "ApplicationSystem.h"
#include <AiAvrRotaryEncoder.h>
#include "LCDMenu.h"
#include "MainMenu.h"
#include "Switch.h"
#include "MenuNavigator.h"
#include "MainMenu.h"
#include "Configuration.h"



LCDMenu lcdMenu;
Switch selectSwitch;
Switch exitSwitch;





// The setup() function runs once each time the micro-controller starts
void setup()
{
    Serial.begin(115200);
 
 
    ApplicationSystem::Instance().Init();  // All  the ports and stuff are set in here

  
    Configuration::instance()->init();


}

// Add the main program code into the continuous loop() function
void loop()
{

    ApplicationSystem::Instance().menu.DoMenu(&mainMenuDescriptor);
 
    delay(50);
}

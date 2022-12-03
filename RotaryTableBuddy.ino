
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



#define ROTARY_ENCODER_A_PIN 7
#define ROTARY_ENCODER_B_PIN 8
#define ROTARY_ENCODER_BUTTON_PIN 25
#define ROTARY_ENCODER_VCC_PIN 2

//depending on your encoder - try 1,2 or 4 to get expected behaviour
//#define ROTARY_ENCODER_STEPS 1
//#define ROTARY_ENCODER_STEPS 2
#define ROTARY_ENCODER_STEPS 4





// The setup() function runs once each time the micro-controller starts
void setup()
{
    Serial.begin(115200);
    delay(10);
    Serial.println("Start");
    ApplicationSystem::Instance().Init();  // All  the ports and stuff are set in here
    ApplicationSystem::Instance().m_lcdDisplay->printstr("HelloBBB");
    Configuration::instance()->init();
   
   
}

// Add the main program code into the continuous loop() function
void loop()
{

    ApplicationSystem::Instance().menu.DoMenu(&mainMenuDescriptor);


    delay(50);
}

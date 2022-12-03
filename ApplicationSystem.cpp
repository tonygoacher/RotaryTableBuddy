#include <Wire.h>
#include "ApplicationSystem.h"



#define ROTARY_ENCODER_A_PIN 7
#define ROTARY_ENCODER_B_PIN 8
#define ROTARY_ENCODER_BUTTON_PIN -1
#define ROTARY_ENCODER_VCC_PIN -1

//depending on your encoder - try 1,2 or 4 to get expected behaviour
//#define ROTARY_ENCODER_STEPS 1
//#define ROTARY_ENCODER_STEPS 2
#define ROTARY_ENCODER_STEPS 4



#define SELECT_SWITCH_PORT  6
#define EXIT_SWITCH_PORT    14



ApplicationSystem& ApplicationSystem::Instance()
{
    static ApplicationSystem instance;
    return instance;
}

void ApplicationSystem::initStepperPorts()
{

    pinMode(PORT_STEP, OUTPUT);
    pinMode(PORT_ENABLE, OUTPUT);
    pinMode(PORT_DIRECTION, OUTPUT);

    digitalWrite(PORT_STEP, LOW);
    digitalWrite(PORT_ENABLE, HIGH);
    digitalWrite(PORT_DIRECTION, LOW);
}

ApplicationSystem::ApplicationSystem()
: m_stepper(PORT_STEP, PORT_DIRECTION, PORT_ENABLE)
{
    digitalWrite(PORT_ENABLE, HIGH);
}



void encoderCallback()
{
    
     ApplicationSystem::Instance().m_rotaryEncoder->readEncoder_ISR();
}




void ApplicationSystem::Init()
{

    Wire.setSDA(0);
    Wire.setSCL(1);
    Wire.setClock(40000);
    Wire.begin();

	m_lcdDisplay = new LiquidCrystal_I2C(LCD_ADDRESS, LCD_WIDTH, LCD_HEIGHT);
    m_lcdDisplay->init();
    m_lcdDisplay->clear();
    m_lcdDisplay->backlight();

    m_rotaryEncoder = new AiAvrRotaryEncoder(ROTARY_ENCODER_A_PIN, ROTARY_ENCODER_B_PIN, -1, -1, ROTARY_ENCODER_STEPS);

    m_rotaryEncoder->begin();
    m_rotaryEncoder->setEncoderValue(0);
    m_rotaryEncoder->setup(encoderCallback);
    m_rotaryEncoder->setBoundaries(-1000, 1000, false); //minValue, maxValue, circleValues true|false (when max go to min and vice versa)
    m_rotaryEncoder->setAcceleration(100);                    //acceleration is now enabled by default - disable if you dont need it## exitSwitch.Init(14);

    m_selectSwitch.Init(SELECT_SWITCH_PORT);
    m_exitSwitch.Init(EXIT_SWITCH_PORT);

    initStepperPorts();
    menuNavigator.initNavigator(m_rotaryEncoder, &m_selectSwitch, &m_exitSwitch);

    menu.Init(m_lcdDisplay, &menuNavigator);





}
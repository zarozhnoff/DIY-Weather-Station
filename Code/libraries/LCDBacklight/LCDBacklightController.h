#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <arduino.h>

#define TURN_ON_LIGHT_THRESHOLD 200


enum LCDBacklightMode { ON, OFF, AUTO };

class LCDBacklightController
{
private:
	LiquidCrystal_I2C* _lcd;
	uint8_t _switcher_pin, _photoResistor_pin;
	LCDBacklightMode _currentMode;
	bool _isBacklightTurnOn;

public:
	LCDBacklightController(LiquidCrystal_I2C* lcd, uint8_t switcher_pin, uint8_t photoResistor_pin)
{
  _lcd = lcd;
_switcher_pin = switcher_pin;
_photoResistor_pin = photoResistor_pin;
}


void CheckBacklightMode()
{
	LCDBacklightMode newMode = GetLCDMode();
  if (newMode == AUTO)
  {
    UpdateBacklightInAutoMode();
  }
  else if (newMode != _currentMode)
  {
    if (newMode == ON)
    {
      TurnOnBacklight();
    }
    else
    {
      TurnOffBacklight();
    }
  }
  _currentMode = newMode;
}

LCDBacklightMode GetLCDMode()
{
  if (analogRead(_switcher_pin) > 900)
  {
    return ON;
  }
  if (analogRead(_switcher_pin) > 400)
  {
    return AUTO;
  }

  return OFF;
}


private:
void TurnOnBacklight()
{
  _lcd->backlight();
  _isBacklightTurnOn = true;
}

void TurnOffBacklight()
{
  _lcd->noBacklight();
  _isBacklightTurnOn = false;
}

void UpdateBacklightInAutoMode()
{
  if ((analogRead(_photoResistor_pin) < TURN_ON_LIGHT_THRESHOLD) && _isBacklightTurnOn)
  {
    TurnOffBacklight();
  }
  else if (!_isBacklightTurnOn)
  {
    TurnOnBacklight();
  }
}
};
#include "DigitalState.h"

DigitalState::DigitalState(int pin, int pGND, int pVCC)
{
	_Init(pin, pGND, pVCC);
}
DigitalState::DigitalState(int pin, int pGND)
{
	_Init(pin, pGND, -1);
}
DigitalState::DigitalState(int pin)
{
	_Init(pin, -1, -1);
}
DigitalState::DigitalState()
{
	_Init(-1, -1, -1);
}

void DigitalState::_Init(int pin, int pGND, int pVCC)
{
	_powerPin = pVCC;
	_gndPin = pGND;
	_pin = pin;
	enable(true);
	reset();
}

void DigitalState::enable(boolean ON_OFF)
{
	if(!ON_OFF)
	{
		if(_powerPin>-1)	pinMode(_powerPin, INPUT);
		if(_gndPin>-1)		pinMode(_gndPin, INPUT);
		if(_pin>-1)			pinMode(_pin, INPUT);
	}
	else
	{
		if(_powerPin>-1)	pinMode(_powerPin, OUTPUT);
		if(_gndPin>-1)		pinMode(_gndPin, OUTPUT);
		if(_pin>-1)			pinMode(_pin, OUTPUT);
	}
}

void DigitalState::power(boolean ON_OFF)
{
	if(_gndPin>-1)	digitalWrite(_gndPin, LOW);
	if(_powerPin>-1)
	{
		if(ON_OFF)	digitalWrite(_powerPin, HIGH);
		else		digitalWrite(_powerPin, LOW);
	}
}
const int DigitalState::getPin(char c)
{
	switch(c)
	{
		case 'd':
			return _pin;
			break;
		case 'p':
			return _powerPin;
			break;
		case 'g':
			return _gndPin;
			break;
		default:
			return _pin;
			break;
	}
}
boolean DigitalState::read(void)
{
	return _state;
}

void DigitalState::set(void)
{
	_state = true;
	if(_pin>-1)	digitalWrite(_pin, HIGH);
}

void DigitalState::reset(void)
{
	_state = false;
	if(_pin>-1)	digitalWrite(_pin, LOW);
}

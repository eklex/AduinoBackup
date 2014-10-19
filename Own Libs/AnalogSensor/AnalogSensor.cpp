#include "AnalogSensor.h"

AnalogSensor::AnalogSensor(int pData, float vScale, float min, float max, int pVCC, int pGND)
{
	_Init(pData, vScale, min, max, pVCC, pGND);
}
AnalogSensor::AnalogSensor(int pData, float vScale, float min, float max, int pVCC)
{
	_Init(pData, vScale, min, max, pVCC, -1);
}
AnalogSensor::AnalogSensor(int pData, float vScale, float min, float max)
{
	_Init(pData, vScale, min, max, -1, -1);
}
AnalogSensor::AnalogSensor(int pData, float vScale)
{
	_Init(pData, vScale, 0.0, 100.0, -1, -1);
}
AnalogSensor::AnalogSensor(int pData)
{
	_Init(pData, 1.0, 0.0, 100.0, -1, -1);
}

void AnalogSensor::_Init(int pData, float vScale, float min, float max, int pVCC, int pGND)
{
	_dataPin = pData;
	_powerPin = pVCC;
	_gndPin = pGND;
	_min = min(min,max);
	_max = max(max,min);
	scale = vScale;
	flag = false;

	enable(true);
	
	_index = 0;
	_acc = 0;
	for (int i = 0; i < BUFF_SIZE; i++)
	_buff[i] = 0;
	for (int i = 0; i < BUFF_SIZE; i++)
	{
		read();
	}
}

void AnalogSensor::enable(boolean ON_OFF)
{
	if(!ON_OFF)
	{
		if(_powerPin>-1)	pinMode(_powerPin, INPUT);
		if(_gndPin>-1)		pinMode(_gndPin, INPUT);
		if(_dataPin>-1)		pinMode(_dataPin, INPUT);
	}
	else
	{
		if(_powerPin>-1)	pinMode(_powerPin, OUTPUT);
		if(_gndPin>-1)		pinMode(_gndPin, OUTPUT);
		if(_dataPin>-1)		pinMode(_dataPin, OUTPUT);
	}
}

void AnalogSensor::power(boolean ON_OFF)
{
	if(_gndPin>-1)	digitalWrite(_gndPin, LOW);
	if(_powerPin>-1)
	{
		if(ON_OFF)	digitalWrite(_powerPin, HIGH);
		else		digitalWrite(_powerPin, LOW);
	}
}

float AnalogSensor::read(void)
{
	_acc = _acc - _buff[_index];
	_buff[_index] = analogRead(_dataPin);
	_acc = _acc + _buff[_index];
	_index ++;
	if (_index >= BUFF_SIZE)  _index = 0;
	value = (_acc/BUFF_SIZE) * scale;
	return value;
}

int AnalogSensor::getPin(char c)
{
	switch(c)
	{
		case 'd':
			return _dataPin;
			break;
		case 'p':
			return _powerPin;
			break;
		case 'g':
			return _gndPin;
			break;
		default:
			return _dataPin;
			break;
	}
}
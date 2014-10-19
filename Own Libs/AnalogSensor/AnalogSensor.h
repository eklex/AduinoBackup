#ifndef AnalogSensor_H_
#define AnalogSensor_H_

#include "Arduino.h"

#define BUFF_SIZE	5

class AnalogSensor
{		
	public:
		AnalogSensor(int, float, float, float, int, int);
		AnalogSensor(int, float, float, float, int);
		AnalogSensor(int, float, float, float);
		AnalogSensor(int, float);
		AnalogSensor(int);
		void enable(boolean);
		void power(boolean);
		float read(void);
		int getPin(char);
		float value;			//valeur réelle (après scale)
		float scale;			//coeff de mise à l'échelle
		boolean flag;
	
	private:
		int _dataPin;			//pin analogique utilisée
		int _powerPin;			//pin d'alimentation
		int _gndPin;				//pin d'alimentation
		float _min;
		float _max;
		int _index;				//index du buffer
		int _acc;				//somme des buffMax valeurs brutes
		int _buff[BUFF_SIZE];	//buffer de moyennage
		void _Init(int, float, float, float, int, int);
};

#endif
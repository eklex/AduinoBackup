#ifndef DigitalState_H_
#define DigitalState_H_

#include "Arduino.h"

class DigitalState
{		
	public:
		DigitalState(int, int, int);
		DigitalState(int, int);
		DigitalState(int);
		DigitalState();
		void enable(boolean);
		void power(boolean);
		const int getPin(char);
		boolean read(void);
		void set(void);
		void reset(void);
	
	private:
		int _pin;
		int _powerPin;				//pin d'alimentation
		int _gndPin;				//pin d'alimentation
		boolean _state;
		void _Init(int, int, int);
};

#endif
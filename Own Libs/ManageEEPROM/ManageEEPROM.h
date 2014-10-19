/*
	ManageEEPROM.h - ManageEEPROM Library v0.1
	<< Make EEPROM managment easier >>
	
	Created by Alexandre BONI, October 2011
	Last modification October 16th 2011
	All right reserved to Alexandre BONI
	
	Under license LGPL-3.0
	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 3.0 of the License, or (at your option) any later version.
*/

#ifndef ManageEEPROM_H_
#define ManageEEPROM_H_

#ifndef DebugModeEEPROM
#define DebugModeEEPROM true
#endif


#include <math.h>
#include "WString.h"
#include "WConstants.h"
#include <avr/eeprom.h>

#define firstCase 3

template <typename T>
class ManageEEPROM
{
	public :
		ManageEEPROM(unsigned int);		
		int saveIndex(unsigned int);
		int restoreIndex(void);
		int saveData(T);		
		T getData(unsigned int);
		String print(void);
		String printByNo(unsigned int);
		unsigned int reset(void);
		unsigned int number(void);
		unsigned int capacity(void);
	#if DebugModeEEPROM
		unsigned int capacity(int);
		String printDebug(unsigned int);
	#endif
	
	private :
		unsigned int _index;
		unsigned int _max;
		boolean _alreadyOnce;
		T _lastData;
		
		int nbBytes(T data);
		T powT(unsigned int,unsigned int);
		unsigned int indexByNo(unsigned int);
		byte read(int);
		void write(int, byte);
};

#include <ManageEEPROM.tpp>

#endif

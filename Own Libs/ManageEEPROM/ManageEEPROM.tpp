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

//####################################################################################//
//################################## P U B L I C #####################################//
//####################################################################################//

template <typename T>
ManageEEPROM<T>::ManageEEPROM(unsigned int max): _max(max)
{
	_index = restoreIndex();
	if(number()>0)	_lastData = getData(indexByNo(1));
}

template <typename T>
int ManageEEPROM<T>::saveIndex(unsigned int index)
{
	if(index<_max)
	{
		if(_alreadyOnce == false && _index > index)
		{
			_alreadyOnce = true;
			write(2, 1);
		}
		write(0, index);
		write(1, index>>8);
		_index = index;
		return 1;
	}
	return -1;
}

template <typename T>
int ManageEEPROM<T>::restoreIndex()
{
	if(read(2)==1)	_alreadyOnce = true;
	else _alreadyOnce = false;
	byte low = read(0);
	byte high = read(1);
	return int(high*256 + low);
}

template <typename T>
int ManageEEPROM<T>::saveData(T data)
{
	if(_lastData != data)
	{
		unsigned int index = _index;
		int nbB = nbBytes(data);
		
		if(_max - index <= nbB)	index = firstCase;
		
		for(int i=0; i<nbB; i++)  write(index++,data>>(8*i));
		write(index++,byte('\t'));
		
		if(index==_max)	index = firstCase;
		_lastData = data;
		
		return saveIndex(index);
		/*
		write(index++,data);
		write(index++,data>>8);
		write(index++,data>>16);
		write(index++,data>>24);
		*/
	}
}

template <typename T>
T ManageEEPROM<T>::getData(unsigned int index)
{
	unsigned long data = 0;
	int j=0;

 	while(read(index + j) != '\t' && index + j < _max)	
	{
		data += read(index + j)*powT(2,8*j);
		j++;
	}
	return data;
  /*
  unsigned int t1 = read(index);
  unsigned int t2 = read(index+1);
  unsigned int t3 = read(index+2);
  unsigned int t4 = read(index+3);
  data = t1 + t2*256 + t3*65536 + t4*16777216;
  */
	
}

template <typename T>
String ManageEEPROM<T>::print(void)
{
	String tmp;
	int j=1;
	unsigned int index = _index;
	if(number()>0)
	{
		if(index>firstCase)
		{
			do	{index--;}	while(read(index)!='\t' && index>firstCase);
			do
			{
				do	{index--;}	while(read(index)!='\t' && index>=firstCase);
				tmp += "Date " + String(j) + " : " + String(getData(index+1)) + "\n";
				j++;
			}
			while(index >= firstCase);
		}
		
		if(_alreadyOnce)
		{
			index = _max;
			do	{index--;}	while(index>_index && read(index)!='\t');
			if(index>_index)
			{
				do
				{
					do	{index--;}	while(read(index)!='\t' && index>=_index);
					tmp += "Date " + String(j) + " : " + String(getData(index+1)) + "\n";
					j++;
				}
				while(index >= _index);
			}
		}
	}
	else tmp="Aucune donnee !\n";
	
	return tmp;
}

template <typename T>
String ManageEEPROM<T>::printByNo(unsigned int noData)
{
	if(indexByNo(noData)==0)	return "Date inexistante\n";
	return "Date " + String(noData) + " : " + String(getData(indexByNo(noData))) + "\n";
}

template <typename T>
unsigned int ManageEEPROM<T>::reset(void)
{
	unsigned int nbDelete=0;
	for(int j=0; j<_max; j++)
        if(read(j)=='\t') 
		{
			write(j,0);
			nbDelete++;
		}
    saveIndex(firstCase);
	_alreadyOnce = false;
	write(2,0);
	return nbDelete;
}

template <typename T>
unsigned int ManageEEPROM<T>::number(void)
{
	unsigned int nbDate = 0;
    for(int j=0; j<_max; j++)
		if(read(j)=='\t')  nbDate++;
	return nbDate;
}

template <typename T>
unsigned int ManageEEPROM<T>::capacity(int nbBytes)
{
	return (_max - firstCase) / (nbBytes + 1);
}

template <typename T>
unsigned int ManageEEPROM<T>::capacity(void)
{
	return (_max - firstCase) / (sizeof(T) + 1);
}

#if DebugModeEEPROM

template <typename T>
String ManageEEPROM<T>::printDebug(unsigned int choice)
{
	String tmp;
	if(choice == 0)
	{
		tmp = "_index="+String(_index)+"\n";
		tmp += "_max="+String(_max)+"\n";
		tmp += "_lastData="+String(_lastData)+"\n";
		tmp += "tab="+String(int('\t'))+"\n";
	}
	else
	{
		#define nbValuesDisplayed 8
		unsigned int max = nbValuesDisplayed*choice;
		unsigned int min = max - nbValuesDisplayed;
		if(max > _max)	max = _max;
		if(min > _max || min > max)	return "END";
		for(int k=min; k<max; k++)
			tmp += "data " + String(k) + " : " + String(int(read(k))) + "\n";
	}
	return tmp;
}
#endif

//####################################################################################//
//################################ P R I V A T E #####################################//
//####################################################################################//

template <typename T>
int ManageEEPROM<T>::nbBytes(T data)
{
  int i = 1;
  while(data > pow(2,8*i))  i++;
  return i;
  //attention long limite un nombre à 4 octets
}

template <typename T>
T ManageEEPROM<T>::powT(unsigned int base, unsigned int expo)
{
	T mul = 1;
	int i=0;
	while(i!=expo)
	{
		mul *= base;
		i++;
	}
	return mul;
}

template <typename T>
unsigned int ManageEEPROM<T>::indexByNo(unsigned int noData)
{
	unsigned int index = _index, j=1;
	
	if(number()>=noData && noData>0)
	{
		if(index>firstCase)
		{
			do	{index--;}	while(read(index)!='\t' && index>firstCase);
			do
			{
				do	{index--;}	while(read(index)!='\t' && index>=firstCase);
				if(j == noData)	return index+1;
				j++;
			}
			while(index >= firstCase);
		}
		
		if(_alreadyOnce)
		{
			index = _max;
			do	{index--;}	while(read(index)!='\t' && index>_index);
			if(index>_index)
			{
				do
				{
					do	{index--;}	while(read(index)!='\t' && index>=_index);
					if(j == noData)	return index+1;
					j++;
				}
				while(index >= _index);
			}
		}
	}
	return 0;
}

template <typename T>
byte ManageEEPROM<T>::read(int address)
{
	return eeprom_read_byte((unsigned char *) address);
}

template <typename T>
void ManageEEPROM<T>::write(int address, byte value)
{
	eeprom_write_byte((unsigned char *) address, value);
}

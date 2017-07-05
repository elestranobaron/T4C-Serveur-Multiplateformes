//**********************************************************
// File: in64stuff.cpp
// Creation date: 02/19/2005
// Created by: Scotch for Dialsoft
// Purpose: E.T. License Key
//**********************************************************

#include "stdafx.h"
#include "int64stuff.h"

//calcule piussance
unsigned __int64 int64stuff::MyPow(unsigned __int64 val, unsigned __int64 pow)
{
	unsigned __int64 answer = 1;
	if (pow != 0)
	{
		for (; pow > 0; pow--)
			answer = answer*val;
	}

	return answer;
}

//calcule la taille
int int64stuff::GetLenght(unsigned __int64 value)
{
	int lenght = 0;
	do
	{
		lenght++;
		value = value/10;
	} while (value > 0);

	return lenght;
}
//**********************************************************
// File: keysgestionnar.cpp
// Creation date: 02/19/2005
// Created by: Scotch for Dialsoft
// Purpose: E.T. License Key
//**********************************************************

#include "stdafx.h"
#include "keysgestionnar.h"
#include <stdio.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//Constructeurs
Key::Key()
{

}

Key::Key(unsigned __int64 new_key, unsigned __int64 new_keymod)
{
	key = key;
	keymod = new_keymod;
}

//precision en bits d'une cle
int Key::getprecision()
{
	unsigned __int64 value;
	if (key > keymod)
		value = key;
	else
		value = keymod;
		
	unsigned __int64 precision = 0;
	do
		precision++;
	while (value > int64stuff::MyPow(2,precision));
	
	return (int)precision;
}


//initialise la clé
void Key::init()
{
	//key    = 914720495;
	//keymod = 2558690599;

   key    = 2047210115;
	keymod = 3589021649;
}


//copie d'une cle
Key& Key::operator=(const Key &oldkey)
 {
	key = oldkey.key;
 	keymod = oldkey.keymod;

 	return *this;
}

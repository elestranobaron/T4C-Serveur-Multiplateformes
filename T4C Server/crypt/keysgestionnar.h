//**********************************************************
// File: keysgestionnar.h
// Creation date: 02/19/2005
// Created by: Scotch for Dialsoft
// Purpose: E.T. License Key
//**********************************************************

#ifndef KEYGESTIONNAR_H
#define KEYGESTIONNAR_H

/*
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
*/

#include "int64stuff.h"

class Key
{
public:
	unsigned __int64 key;		//cle: e ou d
	unsigned __int64 keymod;	//cle n	
	
	//constructeur
	Key();
	Key(unsigned __int64, unsigned __int64);
	Key& operator=(const Key &oldkey);


	//fonctions
	//static Key loadkey( const CString&);	
	//static bool savekey(  const CString&, const Key&);
	int getprecision();
	void init();
};

#endif
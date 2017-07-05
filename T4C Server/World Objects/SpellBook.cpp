// SpellBook.cpp: implementation of the SpellBook class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SpellBook.h"
#include "..\Character.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SpellBook::SpellBook(unsigned short object_type)
{
	
}

SpellBook::~SpellBook()
{

}
/*********************************************************************************************/
void SpellBook::OnInitialise( UNIT_FUNC_PROTOTYPE )
{
    self->SetFlag(__FLAG_CANNOT_DISPELL, 1);
}

//////////////////////////////////////////////////////////////////////////////////////////
ObjectStructure *SpellBook::CreateObject( void ){
	return NULL;
}
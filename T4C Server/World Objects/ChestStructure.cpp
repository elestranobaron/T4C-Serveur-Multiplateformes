// ChestStructure.cpp: implementation of the ChestStructure class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ChestStructure.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ChestStructure::ChestStructure()
{

}

ChestStructure::~ChestStructure()
{

}

void ChestStructure::OnInitialise( UNIT_FUNC_PROTOTYPE )
{
	ObjectStructure::OnInitialise( UNIT_FUNC_PARAM );
}

void ChestStructure::OnUse( UNIT_FUNC_PROTOTYPE )
{
	Character *pl = (Character*)medium;

	if( pl != NULL ) {
		pl->ShowChest();
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
ObjectStructure *ChestStructure::CreateObject( void ){
	return new ChestStructure;
}

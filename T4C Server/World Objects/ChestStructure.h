// ChestStructure.h: interface for the ChestStructure class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHESTSTRUCTURE_H__71302979_E8E6_4222_A0AE_505FF3D47467__INCLUDED_)
#define AFX_CHESTSTRUCTURE_H__71302979_E8E6_4222_A0AE_505FF3D47467__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../ObjectStructure.h"

class ChestStructure : public ObjectStructure  
{
public:
	ChestStructure();
	virtual ~ChestStructure();

	void OnInitialise( UNIT_FUNC_PROTOTYPE );
	void OnUse( UNIT_FUNC_PROTOTYPE );

	static ObjectStructure *CreateObject( void );

};

#endif // !defined(AFX_CHESTSTRUCTURE_H__71302979_E8E6_4222_A0AE_505FF3D47467__INCLUDED_)

// BishopCrowbanner.h: interface for the BishopCrowbanner class.
//
//////////////////////////////////////////////////////////////////////

#include "NPCStructure.h"

#ifndef __BISHOPCROWBANNER_H
#define __BISHOPCROWBANNER_H

class BishopCrowbanner: public NPCstructure{
public:   
	BishopCrowbanner();
	~BishopCrowbanner();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnNPCDataExchange( UNIT_FUNC_PROTOTYPE );
};

#endif

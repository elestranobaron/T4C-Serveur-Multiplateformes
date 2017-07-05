#include "NPCStructure.h"

#ifndef __URIKTHIEF_H
#define __URIKTHIEF_H

class UrikThief : public NPCstructure{
public:
	UrikThief();
	~UrikThief();
	void Create( void );
	void OnPopup( UNIT_FUNC_PROTOTYPE );
	void OnDeath( UNIT_FUNC_PROTOTYPE );
	void OnDestroy( UNIT_FUNC_PROTOTYPE );
};

#endif 
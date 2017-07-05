#include "NPCStructure.h"

#ifndef __OLINHAADASSASSIN_H
#define __OLINHAADASSASSIN_H

class OlinHaadAssassin : public NPCstructure{
public:
	OlinHaadAssassin();
	~OlinHaadAssassin();
	void Create( void );
	void OnPopup( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnDeath( UNIT_FUNC_PROTOTYPE );
	void OnDestroy( UNIT_FUNC_PROTOTYPE );
};

#endif
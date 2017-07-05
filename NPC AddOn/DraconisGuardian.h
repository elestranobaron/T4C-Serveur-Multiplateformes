#include "NPCStructure.h"

#ifndef __DRACONISGUARDIAN_H
#define __DRACONISGUARDIAN_H

class DraconisGuardian : public NPCstructure{
public:
	DraconisGuardian();
	~DraconisGuardian();
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void Create( void );
	void OnPopup( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
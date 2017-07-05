#include <NPCStructure.h>

#ifndef __PORTALSPELLSUNKENWOODS_H
#define __PORTALSPELLSUNKENWOODS_H

class PortalSpellSunkenWoods : public NPCstructure{
public:   
  PortalSpellSunkenWoods();
  ~PortalSpellSunkenWoods();
	void Create( void );
	void OnPopup( UNIT_FUNC_PROTOTYPE );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

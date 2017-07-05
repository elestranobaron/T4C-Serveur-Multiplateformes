#include <NPCStructure.h>

#ifndef __PORTALSPELLSILVERSKY_H
#define __PORTALSPELLSILVERSKY_H

class PortalSpellSilversky : public NPCstructure{
public:   
  PortalSpellSilversky();
  ~PortalSpellSilversky();
	void Create( void );
	void OnPopup( UNIT_FUNC_PROTOTYPE );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

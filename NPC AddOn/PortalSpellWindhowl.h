#include <NPCStructure.h>

#ifndef __PORTALSPELLWINDHOWL_H
#define __PORTALSPELLWINDHOWL_H

class PortalSpellWindhowl : public NPCstructure{
public:   
  PortalSpellWindhowl();
  ~PortalSpellWindhowl();
	void Create( void );
	void OnPopup( UNIT_FUNC_PROTOTYPE );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

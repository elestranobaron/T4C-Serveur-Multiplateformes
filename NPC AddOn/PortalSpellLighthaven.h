#include <NPCStructure.h>

#ifndef __PORTALSPELLLIGHTHAVEN_H
#define __PORTALSPELLLIGHTHAVEN_H

class PortalSpellLighthaven : public NPCstructure{
public:   
  PortalSpellLighthaven();
  ~PortalSpellLighthaven();
	void Create( void );
	void OnPopup( UNIT_FUNC_PROTOTYPE );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

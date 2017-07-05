#include <NPCStructure.h>

#ifndef __PORTALSPELLSTONECREST_H
#define __PORTALSPELLSTONECREST_H

class PortalSpellStonecrest : public NPCstructure{
public:   
  PortalSpellStonecrest();
  ~PortalSpellStonecrest();
	void Create( void );
	void OnPopup( UNIT_FUNC_PROTOTYPE );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

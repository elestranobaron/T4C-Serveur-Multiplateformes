#include <NPCStructure.h>

#ifndef __PORTALSPELLDRUIDPOINT_H
#define __PORTALSPELLDRUIDPOINT_H

class PortalSpellDruidPoint : public NPCstructure{
public:   
  PortalSpellDruidPoint();
  ~PortalSpellDruidPoint();
	void Create( void );
	void OnPopup( UNIT_FUNC_PROTOTYPE );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

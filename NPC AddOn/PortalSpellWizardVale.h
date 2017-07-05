#include <NPCStructure.h>

#ifndef __PORTALSPELLWIZARDVALE_H
#define __PORTALSPELLWIZARDVALE_H

class PortalSpellWizardVale : public NPCstructure{
public:   
  PortalSpellWizardVale();
  ~PortalSpellWizardVale();
	void Create( void );
	void OnPopup( UNIT_FUNC_PROTOTYPE );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

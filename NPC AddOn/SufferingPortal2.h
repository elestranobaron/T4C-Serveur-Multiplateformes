#include <NPCStructure.h>

#ifndef __SUFFERINGPORTAL2_H
#define __SUFFERINGPORTAL2_H

class SufferingPortal2 : public NPCstructure{
public:   
  SufferingPortal2();
  ~SufferingPortal2();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

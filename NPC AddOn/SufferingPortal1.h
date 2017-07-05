#include <NPCStructure.h>

#ifndef __SUFFERINGPORTAL1_H
#define __SUFFERINGPORTAL1_H

class SufferingPortal1 : public NPCstructure{
public:   
  SufferingPortal1();
  ~SufferingPortal1();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif

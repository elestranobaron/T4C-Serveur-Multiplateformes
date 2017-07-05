#include <NPCStructure.h>

#ifndef __DEFILEMENTPORTAL2_H
#define __DEFILEMENTPORTAL2_H

class DefilementPortal2 : public NPCstructure{
public:   
  DefilementPortal2();
  ~DefilementPortal2();
	void Create( void );
	void OnTalk( UNIT_FUNC_PROTOTYPE );
	void OnAttacked( UNIT_FUNC_PROTOTYPE );
	void OnInitialise( UNIT_FUNC_PROTOTYPE );
};

#endif
